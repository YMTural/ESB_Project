#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include <stdlib.h>
#include <string.h>
//For debbuging
#include "bootcamp/UART.h"
//
#include "bootcamp/circularBuffer.h"
#include "bootcamp/UART_interrupt.h"
#include "bootcamp/timeBasedScheduler.h"
#include "bootcamp/adc_temperature.h"
#include "bootcamp/priorityQueueHeap.h"
#include "bootcamp/sinusFunctions/sinusFunction.h"
#include "bootcamp/taskHandler.h"

/*

Commands:

    help – Help-Command, welches alle unterstützten Kommandos anzeigt.
    echo <string> – Echo eines übergebenen Strings.
    led <bit> – Schreibt den Status der LED.
    toggle – Invertiert den aktuellen Status der LED.
    flash <int> – Lässt LED eine konfigurierbare Anzahl hintereinander blinken.
    sine <int> – Lässt LED mithilfe von PWM in einer Sinuskurve und konfigurierbarer Periode an- und abschwellen. (Hierfür ergibt es u.U. Sinn, a. Fixed-Point-Arithmetik für die Taylor Reihe zu verwenden oder b. Werte der Sinusfunktion in einer Lookup-Tabelle vorauszuberechnen*)
    inc – Inkrementiert einen internen Zähler.
    counter – Liefert den aktuellen Wert des Zählers zurück.
    temp – Gibt die aktuelle Temperatur des internen Temperatursensors in °C aus.

    periodic <int8> <command>  < - Führt den Command für alle x Sekunden aus.
    kill <id> - Löscht den Task mit der zugehörigen ID
    list - Gibt alle Tasks aus die periodisch ausgeführt werden

*/

#define LF 10
#define STARTIMMEDIATELY 0
#define START_IN_MS(X) (X)
#define START_IN_M(X) (X*1000)
#define SINESTEPS 256
#define BASE10 10
#define BASE_PRIORITY_SINGLECMD 150
//Size of the Buffers
#define BUFFERSIZE 128

//
#define MAXTASKS 16

//Maximum supported length for one command
#define MAXCOMMANDLENGTH 128

#define LONGESTCOMMAND 9
#define NUMBEROFMULTICOMMANDS 6
#define NUMBEROFSINGLECOMMANDS 6
#define NUMBEROFCOMMANDS 12

uint16_t currentTime = 0;
uint8_t sineCounter = 0;
uint8_t commandLength = 0;

uint8_t user_counter = 0;

uint8_t errorCode = 1;

const char const multiCommands[NUMBEROFMULTICOMMANDS][LONGESTCOMMAND] = {"echo", "led", "flash", "sine", "periodic", "kill"};
const char const singleCommands[NUMBEROFSINGLECOMMANDS][LONGESTCOMMAND] = {"help", "toggle", "inc", "counter", "temp", "list"};                                             

const char greetingMessage[128] PROGMEM = {"ESB - Arduino Command-Line Interface - Willkommen!\nGeben Sie help ein um alle verfuegbaren Commands zu sehen.\n"};
const char helpMessage[128] PROGMEM = {"Commands: help, echo <string>, led <bit>, flash <uint8>, sine <uint8>, inc, counter, temp, periodic, kill <uint8>, list \n"};
const char counterMessage[32] PROGMEM = {"Der Counter liegt aktuell bei: "};
const char temperatureMessage[64] PROGMEM = {"Die aktuelle Temperatur des Chips betraegt: "};
const char listMessage[64] PROGMEM = {"Folgende IDs sind aktuell vergeben: "};
const char error_unknownCommand[48] PROGMEM = {"ERROR - Dieser Befehl ist ungueltig!\n"};
const char error_queueFull[32] PROGMEM = {"ERROR - Taskqueue ist voll!\n"};
const char error_noFreeMemAvailable[48] PROGMEM = {"ERROR - Kein freier Speicher mehr verfügbar!\n"};
const char error_wrongParameter[96] PROGMEM = {"ERROR - Der eingegebene Parameter entspricht nicht dem richtigen Typ!\n"};
const char error_notSupportedAction[96] PROGMEM = {"ERROR - Diese Funktionalitaet wird nicht unterstuetzt!\n"};
const char newlineString[8] PROGMEM = {"\n"};
const char celsiusNewLine[8] PROGMEM = {"C\n"};
//https://www.daycounter.com/Calculators/Sine-Generator-Calculator.phtml ; 256,255,16
const uint8_t sineWave[256] PROGMEM = {
0x80,0x83,0x86,0x89,0x8c,0x8f,0x92,0x95,0x98,0x9b,0x9e,0xa2,0xa5,0xa7,0xaa,0xad,
0xb0,0xb3,0xb6,0xb9,0xbc,0xbe,0xc1,0xc4,0xc6,0xc9,0xcb,0xce,0xd0,0xd3,0xd5,0xd7,
0xda,0xdc,0xde,0xe0,0xe2,0xe4,0xe6,0xe8,0xea,0xeb,0xed,0xee,0xf0,0xf1,0xf3,0xf4,
0xf5,0xf6,0xf8,0xf9,0xfa,0xfa,0xfb,0xfc,0xfd,0xfd,0xfe,0xfe,0xfe,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xfe,0xfe,0xfe,0xfd,0xfd,0xfc,0xfb,0xfa,0xfa,0xf9,0xf8,0xf6,
0xf5,0xf4,0xf3,0xf1,0xf0,0xee,0xed,0xeb,0xea,0xe8,0xe6,0xe4,0xe2,0xe0,0xde,0xdc,
0xda,0xd7,0xd5,0xd3,0xd0,0xce,0xcb,0xc9,0xc6,0xc4,0xc1,0xbe,0xbc,0xb9,0xb6,0xb3,
0xb0,0xad,0xaa,0xa7,0xa5,0xa2,0x9e,0x9b,0x98,0x95,0x92,0x8f,0x8c,0x89,0x86,0x83,
0x80,0x7c,0x79,0x76,0x73,0x70,0x6d,0x6a,0x67,0x64,0x61,0x5d,0x5a,0x58,0x55,0x52,
0x4f,0x4c,0x49,0x46,0x43,0x41,0x3e,0x3b,0x39,0x36,0x34,0x31,0x2f,0x2c,0x2a,0x28,
0x25,0x23,0x21,0x1f,0x1d,0x1b,0x19,0x17,0x15,0x14,0x12,0x11,0xf,0xe,0xc,0xb,
0xa,0x9,0x7,0x6,0x5,0x5,0x4,0x3,0x2,0x2,0x1,0x1,0x1,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x2,0x2,0x3,0x4,0x5,0x5,0x6,0x7,0x9,
0xa,0xb,0xc,0xe,0xf,0x11,0x12,0x14,0x15,0x17,0x19,0x1b,0x1d,0x1f,0x21,0x23,
0x25,0x28,0x2a,0x2c,0x2f,0x31,0x34,0x36,0x39,0x3b,0x3e,0x41,0x43,0x46,0x49,0x4c,
0x4f,0x52,0x55,0x58,0x5a,0x5d,0x61,0x64,0x67,0x6a,0x6d,0x70,0x73,0x76,0x79,0x7c};

enum errorCodes {UNKNOWNCOMMAND, QUEUEFULL, NOFREEMEM, WRONGPARAM, NOTSUPPORTED};

uint8_t* transBuffer;
uint8_t* recBuffer;

circularBuffer_t cTransmitbuffer;
circularBuffer_t cReceivebuffer;

priorityQueueHeap_t pQueue;

UART_interrupt_t uBuf;

timeBasedScheduler_t tBScheduler;
task* taskArray;
taskHandler_t tHandler;

void freeRam () {
  extern int __heap_start, *__brkval;
  int v;
  int z = (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
  char m[16];
  sprintf(m,"%d",z);
  sendMessage(m);
}

//Declare here for determine task
void receive(void);
void prepareTemp(void);
void sendError(void);
void toggleLed(void);
void returnCounter(void);
void sendTemperature(void);
void incrementCounter(void);
void task_help(void);
void listTasks(void);
void raiseError(uint8_t eCode);
void led(char *param);
void flash(char *param);
void echo(char *param);
void sineInit(char *param);
void sineFade(char *param);
void kill(char *param);
void periodic(char *param);
void sendMessage(char *param);
void sendMessage_P(const char *param, int length);
           
void (*singleCommandList[])(void) = {task_help, toggleLed, incrementCounter, returnCounter, prepareTemp, listTasks};
void (*multiCommandList[])(char*) = {echo, led, flash, sineInit, periodic, kill}; 

//help func
void clearLastCommand(uint8_t length){
  uint8_t dump;
  for (uint8_t i = 0; i < commandLength; i++)
  {
    circularBuffer_read(cReceivebuffer, 0);  
  }
}

void raiseError(uint8_t eCode){

  errorCode = eCode;
  timeBasedScheduler_addTask(tBScheduler, &sendError, 255, STARTIMMEDIATELY);
  clearLastCommand(commandLength);
  commandLength = 0;
}

//MultiCommands
void echo(char * param){
  
  sendMessage(param);
  sendMessage_P(newlineString, 1);
}

void led(char *param){

  if(param[0] != 0x30){
    PORTB |= _BV(5);
  }
  else{
    PORTB &= ~_BV(5);
  }
}

void flash(char *param){

  char **ptr;
  uint8_t num = strtol(param, ptr, BASE10);
  //freeRam();
  if(num != 0){
    timeBasedScheduler_addTask(tBScheduler, &toggleLed, 25, STARTIMMEDIATELY);
    timeBasedScheduler_addTask(tBScheduler, &toggleLed, 25, START_IN_MS(100));
    num--;
    char* number = malloc(sizeof(char)*3);
    if(number == 0){
      errorCode = NOFREEMEM;
      timeBasedScheduler_addTask(tBScheduler, &sendError, 255, STARTIMMEDIATELY);
    }else{
      sprintf(number, "%i", num);
      timeBasedScheduler_addTaskWithParam(tBScheduler, &flash, 165, START_IN_MS(200), number);
    }
  }
}

void sineInit(char *param){

  char **ptr;
  uint8_t num = strtol(param, ptr, BASE10);

  if(num != 0){
    arduinoArch_PWMTimerinit();
    char* newParams = malloc(sizeof(uint8_t)*3);

    if(newParams == 0){

      errorCode = NOFREEMEM;
      timeBasedScheduler_addTask(tBScheduler, &sendError, 255, STARTIMMEDIATELY);
    }else{
    
      newParams[0] = num;
      newParams[1] = 0;
      newParams[2] = ((PORTB >> 5) & 1) ^ 1;
      timeBasedScheduler_addTaskWithParam(tBScheduler, &sineFade, 125, STARTIMMEDIATELY, newParams);
    }
  }
}

void sineFade(char *param){

  if((uint8_t)param[1] < 255){

    //Start at 0 or 1 depending on led status
    uint8_t shiftedIndex = (uint8_t) param[1] + 64 + (uint8_t) param[2] * 128;
    OCR1B = pgm_read_byte_near(sineWave + shiftedIndex);
    char* newParams = malloc(sizeof(uint8_t)*3);

    if(newParams == 0){
      errorCode = NOFREEMEM;
      timeBasedScheduler_addTask(tBScheduler, &sendError, 255, STARTIMMEDIATELY);
    }else{ 
    
      newParams[0] = param[0];
      newParams[1] = param[1] + 1;
      newParams[2] = param[2];
      timeBasedScheduler_addTaskWithParam(tBScheduler, &sineFade, 125, START_IN_M(newParams[0])/SINESTEPS, newParams);
    }
  }else{
    
    arduinoArch_PWMTimerStop();
    //Restore old led status
    PORTB ^= (-(param[2]^1) ^ PORTB) & (1 << 5);
  }
}


void kill(char *param){

  char **ptr;
  uint8_t num = strtol(param, ptr, BASE10);

  if(num > 31){
    errorCode = WRONGPARAM;
    timeBasedScheduler_addTask(tBScheduler, &sendError, 255, STARTIMMEDIATELY);
  }

  timeBasedScheduler_deleteTask(tBScheduler,num);
}

void periodic(char *param){

}

//SingleCommands
void task_help(void){

  sendMessage_P(helpMessage, strlen(helpMessage));
}

void toggleLed(void){

  PORTB ^= _BV(5);
}

void incrementCounter(){

  user_counter++;
}

void returnCounter(void){

  char message[3];
  sprintf(message, "%d", user_counter);
  sendMessage_P(counterMessage, strlen(counterMessage));
  sendMessage(message);
  sendMessage_P(newlineString, 1);
}

void listTasks(void){

  uint32_t idInt= timeBasedScheduler_getUsedIDsInt(tBScheduler);
  bool none = true;
  char noneMsg[] = " none";
  
  for(uint8_t i = 0; i < strlen(listMessage); i++){
    circularBuffer_overwrite(cTransmitbuffer, pgm_read_byte_near(listMessage + i));
  }
  UART_interrupt_transmitFromBufferInit(uBuf, strlen(listMessage));

  task *iTask;

  for (uint8_t i = 0; i < 32; i++)
  {
     if( (  (idInt >> i) & 1)){
      //UART_transmit(0xEA);
      //UART_transmit(i);
      //Push i as ASCII
      circularBuffer_push(cTransmitbuffer, i/10 + 0x30);
      circularBuffer_push(cTransmitbuffer, i + 0x30);
      //ASCII of ":"
      circularBuffer_push(cTransmitbuffer, 0x3A);
      //ASCII of Space
      circularBuffer_push(cTransmitbuffer, 0x20);
      UART_interrupt_transmitFromBufferInit(uBuf, 4);
      for (uint8_t u = 0; u < priorityQueueHeap_size(pQueue); u++)
      {
        iTask = priorityQueueHeap_peekAt(pQueue, u);
        if(iTask -> id == i){

          if(iTask -> param == 0){
            for (uint8_t v = 0; v < NUMBEROFSINGLECOMMANDS; v++)
            {
              if(iTask -> functions.voidfunction = singleCommandList[v]){
                for (uint8_t j = 0; j < strlen(singleCommands[v]); j++)
                {
                  circularBuffer_push(cTransmitbuffer, singleCommands[v][j]);
                }
              }
            }
          }else{
            for (uint8_t v = 0; v < NUMBEROFMULTICOMMANDS; v++)
            {
              if(iTask -> functions.charfunction = multiCommandList[v]){
                for (uint8_t j = 0; j < strlen(multiCommands[v]); j++)
                {
                  circularBuffer_push(cTransmitbuffer, multiCommands[v][j]);
                }
              }
            }              
          }
        }else{
          //DEBUG-ERROR
          raiseError(NOFREEMEM);
        }
      }
    }
  }
}

void determineTask(void){

  char receivedCommand[commandLength];
  char firstPart[8] = {0,0,0,0,0,0,0,0};
  char secondPart[commandLength];

  bool singleType = true;

  uint8_t lengthFirstPart = 0;

  
  //Determine first part
  for (uint8_t i = 0; i < commandLength; i++)
  {
    circularBuffer_read(cReceivebuffer, &receivedCommand[i]);
    lengthFirstPart++;
    //Search for space
    if(receivedCommand[i] == ' '){
      singleType = false;
      break;
    } 
  }

  uint8_t commandNumber = 255;
  strncpy(firstPart, receivedCommand, lengthFirstPart-1);
   //Must set end character manually
  firstPart[lengthFirstPart-1] = '\0';

  //Queue ist voll
  if(priorityQueueHeap_size(pQueue) > MAXTASKS - 4){
    raiseError(QUEUEFULL);
    return;
  }

  if(singleType){

    for (uint8_t i = 0; i < NUMBEROFSINGLECOMMANDS; i++)
    {
      if(strcmp(firstPart, singleCommands[i]) == 0){
        commandNumber = i;
        timeBasedScheduler_addTask(tBScheduler, singleCommandList[i], 150 + 5 * i, STARTIMMEDIATELY);
        break;
      }
    }
    if(commandNumber == 255) raiseError(UNKNOWNCOMMAND);
  }
  else{

    for (uint8_t i = 0; i < NUMBEROFMULTICOMMANDS; i++)
    {
      if(strcmp(firstPart, multiCommands[i]) == 0){
        commandNumber = i;
        break;
      }
    }    

    if(lengthFirstPart == commandLength - 1){
      raiseError(WRONGPARAM);
      return;
    }

    for (uint8_t i = lengthFirstPart; i < commandLength; i++)
    {
        circularBuffer_read(cReceivebuffer, &secondPart[i-lengthFirstPart]);
    }
    char *param = malloc(sizeof(char) * (commandLength - lengthFirstPart));
    if(param == NULL){
      raiseError(NOFREEMEM);
      return;
    }
    strncpy(param, secondPart, (commandLength - lengthFirstPart) - 1);
    param[(commandLength - lengthFirstPart) - 1] = '\0';

    switch (commandNumber)
    {
    //echo
    case 0:
      timeBasedScheduler_addTaskWithParam(tBScheduler, &echo, 185, STARTIMMEDIATELY, param);
      break;
    //led
    case 1:
      if(strlen(param) > 1){
        raiseError(WRONGPARAM);
      }else{
        timeBasedScheduler_addTaskWithParam(tBScheduler, &led, 120, STARTIMMEDIATELY, param);
      }
      break;
    //flash
    case 2:
      timeBasedScheduler_addTaskWithParam(tBScheduler, &flash, 125, STARTIMMEDIATELY, param);
      break;
    //sine
    case 3: 
      timeBasedScheduler_addTaskWithParam(tBScheduler, &sineInit, 130, STARTIMMEDIATELY, param);
      break;    

    //periodic
    case 4:
      lengthFirstPart = 0;
      memset(firstPart, 0, sizeof(char)*8);
      singleType = true;
      char *ptrToCmdStart;
      uint8_t num = strtol(param, &ptrToCmdStart, 10);
      if(num == 0){

        raiseError(WRONGPARAM);
        break;
      }

      for (uint8_t i = 1; i < strlen(ptrToCmdStart); i++)
      {
        firstPart[i-1] = ptrToCmdStart[i];
        lengthFirstPart++;
        //Search for space
        if(ptrToCmdStart[i] == 32){
          singleType = false;
          break;
        } 
      }
      uint8_t commandNumber = 255;
      //Delete Space
      //firstPart[lengthFirstPart] = "\0";

      if(singleType){

        for (uint8_t i = 0; i < NUMBEROFSINGLECOMMANDS; i++)
        {
          if(strcmp(firstPart, singleCommands[i]) == 0){
            commandNumber = i;
            break;
          }
        }
        if(commandNumber == 255){
          raiseError(UNKNOWNCOMMAND);
          break;
        }
        timeBasedScheduler_addPeriodicTaskID(tBScheduler, singleCommandList[commandNumber], commandNumber*15, num*1000, STARTIMMEDIATELY, timeBasedScheduler_getOverflowBit(tBScheduler), timeBasedScheduler_findNextAvailableId(tBScheduler));
      }else{

        firstPart[lengthFirstPart - 1] = 0;
        for (uint8_t i = 0; i < NUMBEROFMULTICOMMANDS; i++)
        {
          if(strcmp(firstPart, multiCommands[i]) == 0){
            commandNumber = i;
            break;
          }
        }
        if(commandNumber == 255){
          raiseError(UNKNOWNCOMMAND);
          break;
        }
        if(commandNumber > 4){
          raiseError(NOTSUPPORTED);
          break;
        }

        char *param2 = malloc(sizeof(char)* (strlen(ptrToCmdStart) - lengthFirstPart));

        strncpy(param2, ptrToCmdStart + lengthFirstPart + 1, strlen(ptrToCmdStart) - lengthFirstPart);
        param2[strlen(ptrToCmdStart) - lengthFirstPart] = '\0';
        timeBasedScheduler_addPeriodicTaskWithParam(tBScheduler, multiCommandList[commandNumber], commandNumber*15, num*1000, STARTIMMEDIATELY, timeBasedScheduler_getOverflowBit(tBScheduler), param2, timeBasedScheduler_findNextAvailableId(tBScheduler));

        }
      free(param);
      break;

    case 5:
      timeBasedScheduler_addTaskWithParam(tBScheduler, &kill, 255, STARTIMMEDIATELY, param);
      break;
    default:
      errorCode = UNKNOWNCOMMAND;
      timeBasedScheduler_addTask(tBScheduler, &sendError, 255, STARTIMMEDIATELY);
      break;
    }
  }
  //clearLastCommand(commandLength);
  commandLength = 0;
}




void awaitNextCommand(void){

  UART_interrupt_receiveToBufferInit(uBuf,MAXCOMMANDLENGTH);
}

void receive(void){

  UART_interrupt_receiveToBuffer(uBuf, PUSH);
  //Check if last send ASCII was new line (LF)
  if(circularBuffer_mostRecentElement(cReceivebuffer) == LF && commandLength != 0){

    timeBasedScheduler_addTask(tBScheduler, &determineTask, 255, STARTIMMEDIATELY);
    timeBasedScheduler_addTask(tBScheduler, &awaitNextCommand, 128, STARTIMMEDIATELY);
  }
}

void transmit(void){

  UART_interrupt_transmitFromBuffer(uBuf);
}

void prepareTemp(void){

  adc_temperature_fetchTemperature();
}

void sendTemperature(void){
  
  char tempStr[3];
  uint8_t temp = adc_temperature_getTemperature();
  UART_transmit(0xEF);
  UART_transmit(temp);
  sprintf(tempStr, "%d", temp);
  sendMessage_P(temperatureMessage, strlen(temperatureMessage));
  sendMessage(tempStr);
  sendMessage_P(celsiusNewLine, strlen(celsiusNewLine));
}

void sendMessage(char *msg){

    for(uint8_t i = 0; i < strlen(msg); i++){
      circularBuffer_overwrite(cTransmitbuffer, msg[i]);
    }
    UART_interrupt_transmitFromBufferInit(uBuf, strlen(msg));
}

//Must handle flash mem pointer differently
void sendMessage_P(const char *pointerToMsg, int length){

    char message[length];
    strcpy_P(message, pointerToMsg);
    for(uint8_t i = 0; i < length; i++){
      circularBuffer_overwrite(cTransmitbuffer, message[i]);
    }
    UART_interrupt_transmitFromBufferInit(uBuf, length);
}

void sendError(void){

  switch (errorCode)
  {
  case UNKNOWNCOMMAND:
    sendMessage_P(error_unknownCommand, strlen(error_unknownCommand));
    break;
  case QUEUEFULL:
    sendMessage_P(error_queueFull, strlen(error_queueFull));
    break;
  case NOFREEMEM:
    sendMessage_P(error_noFreeMemAvailable, strlen(error_noFreeMemAvailable));
    break;
  case WRONGPARAM:
    sendMessage_P(error_wrongParameter, strlen(error_wrongParameter));
    break;
  case NOTSUPPORTED:
    sendMessage_P(error_notSupportedAction, strlen(error_notSupportedAction));
  }  
}

void sendWelcomeMessage(void){

  sendMessage_P(greetingMessage, strlen(greetingMessage));
}  

int main() {

  taskArray = malloc(sizeof(task)*MAXTASKS);

  transBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
  recBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
  
  pQueue = priorityQueueHeap_init(MAXTASKS, taskArray);
  cTransmitbuffer = circularBuffer_init(transBuffer, BUFFERSIZE);
    
  cReceivebuffer = circularBuffer_init(recBuffer, BUFFERSIZE);

  tBScheduler = timeBasedScheduler_init(&currentTime, pQueue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

  uBuf = UART_interrupt_init(cReceivebuffer, cTransmitbuffer, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);
  tHandler = taskHandler_init(singleCommands, multiCommands);

  DDRB = 0xFF;
  PORTB ^= _BV(5);
  sei();
  adc_temperature_init();

  //Blinking
  //timeBasedScheduler_addPeriodicTask(tBScheduler, &toggleLed, 0x33, 1000, currentTime, 0);

  //Await first command
  timeBasedScheduler_addTask(tBScheduler, &awaitNextCommand, 128, STARTIMMEDIATELY);

  //Welcome Message
  timeBasedScheduler_addTask(tBScheduler, &sendWelcomeMessage, 127, STARTIMMEDIATELY);

  timeBasedScheduler_addPeriodicTask(tBScheduler, &freeRam, 250, 1000, STARTIMMEDIATELY, 0);

  while(true){

    timeBasedScheduler_schedule(tBScheduler);
  }


  return 0;
}

ISR(USART_UDRE_vect){
  cli();
  UART_interrupt_setTransmitFlag(uBuf, true);
  UART_disableTransmitInterrupt();
  //Schedule next transmit
  timeBasedScheduler_addTask(tBScheduler, &transmit, 240, STARTIMMEDIATELY);
  sei();
}

ISR(USART_TX_vect){
  cli();
  if(UART_interrupt_isTransmitComplete(uBuf)){

    UART_disableTransmitCompleteInterrupt();
  }
  else{

    UART_enableTransmitInterrupt();
  }
  sei();
}

ISR(USART_RX_vect){
  cli();
  commandLength++;
  UART_disableReceiveInterrupt();
  UART_interrupt_setReceiveFlag(uBuf, true);
  //Schedule receive with highest priority
  timeBasedScheduler_addTask(tBScheduler, &receive, 255, STARTIMMEDIATELY);
  sei();
}

ISR(TIMER0_COMPA_vect){
  cli();
  //keeps track of the number of ms passed
  timeBasedScheduler_incrementTimer(tBScheduler);
  //iterates over tasks in queue and checks
  //if their starttime <= currentTime
  timeBasedScheduler_markIfReady(tBScheduler);
  sei();
  }
  
ISR(ADC_vect){
    cli();
    timeBasedScheduler_addTask(tBScheduler, &sendTemperature, 155, STARTIMMEDIATELY);
    sei();
}

ISR(TIMER1_COMPA_vect){
    PORTB |= _BV(5);
}

ISR(TIMER1_COMPB_vect){
    PORTB &= ~_BV(5);
}
//Interrupt ISR end