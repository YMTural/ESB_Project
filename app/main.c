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

    periodic <command> <int8> < - Führt den Command für alle x Sekunden aus.
    kill <id> - Löscht den Task mit der zugehörigen ID
    list - Gibt alle Tasks aus die periodisch ausgeführt werden

*/

#define LF 10

//Size of the Buffers
#define BUFFERSIZE 128

//Maximum supported length for one command
#define MAXCOMMANDLENGTH 128

#define LONGESTCOMMAND 8
#define NUMBEROFMULTICOMMANDS 6
#define NUMBEROFSINGLECOMMANDS 6
#define NUMBEROFCOMMANDS 12

volatile uint16_t currentTime = 0;
volatile uint8_t commandLength = 0;

volatile uint8_t user_counter = 0;

volatile uint8_t errorCode = 0;

//Switch to enumeration after implementing MQTT Client
volatile const char multiCommands[NUMBEROFMULTICOMMANDS][LONGESTCOMMAND] = {"echo", "led", "flash", "sine", "periodic", "kill"};
volatile const char singleCommands[NUMBEROFSINGLECOMMANDS][LONGESTCOMMAND] = {"help", "toggle", "inc", "counter", "temp", "list"};                                             

const char helpMessage[128] PROGMEM = {"Commands: help, echo <string>, led <bit>, flash <int>, sine <int>, inc, counter, temp, periodic, kill <id>, list \n"};
const char counterMessage[32] PROGMEM = {"Der Counter liegt aktuell bei: "};
const char temperatureMessage[64] PROGMEM = {"Die aktuelle Temperatur des Chips betraegt: "};
const char error_unknownCommand[32] PROGMEM = {"Dieser Befehl ist ungueltig!\n"};


volatile uint8_t* transBuffer;
volatile uint8_t* recBuffer;

volatile circularBuffer_t cTransmitbuffer;
volatile circularBuffer_t cReceivebuffer;

volatile priorityQueueHeap_t pQueue;

volatile UART_interrupt_t uBuf;

volatile timeBasedScheduler_t tBScheduler;

enum errorCodes {UNKNOWNCOMMAND};
//Declare here for determine task
void receive(void);
void prepareTemp(void);
void sendError(void);
//SingleCommands
void task_help(void){
  for (uint8_t i = 0; i < strlen(helpMessage); i++)
  {
    circularBuffer_overwrite(cTransmitbuffer, pgm_read_byte_near(helpMessage + i)); 
  }

  UART_interrupt_transmitFromBufferInit(uBuf, strlen(helpMessage));
}

void toggleLed(void){

  PORTB ^= _BV(5);
}

void incrementCounter(){

  user_counter++;
}

void returnCounter(){

  char message[3];
  for(uint8_t i = 0; i < strlen(counterMessage); i++){
    circularBuffer_overwrite(cTransmitbuffer, pgm_read_byte_near(counterMessage + i));
  }

  sprintf(message, "%d", user_counter);

  for(uint8_t i = 0; i < strlen(message); i++){
    circularBuffer_overwrite(cTransmitbuffer, message[i]);
  }
  //Zeilenumbruch
  circularBuffer_overwrite(cTransmitbuffer, 0x0A);

  UART_interrupt_transmitFromBufferInit(uBuf, strlen(counterMessage) + strlen(message) + 1);
}

void determineTask(void){

  char receivedCommand[commandLength];
  char firstPart[8] = {0,0,0,0,0,0,0,0};
  char secondPart[8];
  char thirdPart[8];

  bool singleType = true;

  uint8_t lengthFirstPart = 0;
  uint8_t lengthSecondPart = 0;
  uint8_t lengthThirdPart = 0;

  //Determine first part
  for (uint8_t i = 0; i < commandLength; i++)
  {
    circularBuffer_read(cReceivebuffer, &receivedCommand[i]);
    lengthFirstPart++;
    //Search for space
    if(receivedCommand[i] == 32){
      singleType = false;
      break;
    } 
  }
  if(singleType){

    uint8_t commandNumber = 255;
    strncpy(firstPart, receivedCommand, commandLength-1);

    //Must set end character manually
    firstPart[commandLength-1] = '\0';

    for (uint8_t i = 0; i < NUMBEROFSINGLECOMMANDS; i++)
    {
      if(strcmp(firstPart, singleCommands[i]) == 0){
        commandNumber = i;
        break;
      }
    }
    switch (commandNumber)
    {
    //help  
    case 0:
      timeBasedScheduler_addTask(tBScheduler, &task_help, 175, currentTime);
      break;
    //toggle:  
    case 1:
      timeBasedScheduler_addTask(tBScheduler, &toggleLed, 25, currentTime);
      break;
    //inc  
    case 2:
      timeBasedScheduler_addTask(tBScheduler, &incrementCounter, 25, currentTime);
      break;
    //counter
    case 3:
      timeBasedScheduler_addTask(tBScheduler, &returnCounter, 170, currentTime);
      break;    
    case 4:
      timeBasedScheduler_addTask(tBScheduler, &prepareTemp, 210, currentTime);
      break;
    case 5:
      UART_transmit(commandNumber);
      break;          
    default:
      errorCode = UNKNOWNCOMMAND;
      timeBasedScheduler_addTask(tBScheduler, &sendError, 255, currentTime);
      break;
    }

  }

  commandLength = 0;
}

void awaitNextCommand(void){

  UART_interrupt_receiveToBufferInit(uBuf,MAXCOMMANDLENGTH);
}

void receive(void){
  UART_interrupt_receiveToBuffer(uBuf, PUSH);
  //Check if last send ASCII was new line (LF)
  if(circularBuffer_mostRecentElement(cReceivebuffer) == LF && commandLength != 0){

    timeBasedScheduler_addTask(tBScheduler, &determineTask, 255, currentTime);
    timeBasedScheduler_addTask(tBScheduler, &awaitNextCommand, 128, currentTime);
  }
}

void transmit(void){
  UART_interrupt_transmitFromBuffer(uBuf);
}

void prepareTemp(void){

  adc_temperature_fetchTemperature();
}

void sendTemperature(void){
  char message[3];
  uint8_t temp = adc_temperature_getTemperature();

  for(uint8_t i = 0; i < strlen(temperatureMessage); i++){
    circularBuffer_overwrite(cTransmitbuffer, pgm_read_byte_near(temperatureMessage + i));
  }

  sprintf(message, "%d", temp);

  for(uint8_t i = 0; i < strlen(message); i++){
    circularBuffer_overwrite(cTransmitbuffer, message[i]);
  }
  circularBuffer_overwrite(cTransmitbuffer, 'C');
  circularBuffer_overwrite(cTransmitbuffer, 0x0A);

  UART_interrupt_transmitFromBufferInit(uBuf, strlen(temperatureMessage) + strlen(message) + 2);

}

void sendError(void){

  for(uint8_t i = 0; i < strlen(error_unknownCommand); i++){
    circularBuffer_overwrite(cTransmitbuffer, pgm_read_byte_near(error_unknownCommand + i));
  }
  UART_interrupt_transmitFromBufferInit(uBuf, strlen(error_unknownCommand));
}

int main() {

  sei();
  
  DDRB = _BV(5);
  PORTB ^= _BV(5);

  pQueue = priorityQueueHeap_init(24);

  transBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
  recBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
  
  cTransmitbuffer = circularBuffer_init(transBuffer, BUFFERSIZE);
  cReceivebuffer = circularBuffer_init(recBuffer, BUFFERSIZE);

  tBScheduler = timeBasedScheduler_init(24, pQueue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

  uBuf = UART_interrupt_init(cReceivebuffer, cTransmitbuffer, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);

  adc_temperature_init();
  //Blinking
  //timeBasedScheduler_addPeriodicTask(tBScheduler, &toggleLed, 155, 100, currentTime, 0);

  //Receive next item 1ms
  //timeBasedScheduler_addPeriodicTask(tBScheduler, &receive, 250, 0, currentTime + 50, 0);

  //Transmit next item on Buffer 2ms
  //timeBasedScheduler_addPeriodicTask(tBScheduler, &transmit,254 ,10 , currentTime + 50, 0);

  //Await first command
  timeBasedScheduler_addTask(tBScheduler, &awaitNextCommand, 128, currentTime);


  while(true){

    timeBasedScheduler_schedule(tBScheduler, &currentTime);
  }


  return 0;
}

ISR(USART_UDRE_vect){

  cli();
  UART_interrupt_setTransmitFlag(uBuf, true);
  UART_disableTransmitInterrupt();
  //Schedule next transmit
  timeBasedScheduler_addTask(tBScheduler, &transmit, 200, currentTime);
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
  //Schedule receive asap
  timeBasedScheduler_addTask(tBScheduler, &receive, 255, currentTime);
  sei();
}

ISR(TIMER0_COMPA_vect){

  cli();
  //keeps track of the number of ms passed
  timeBasedScheduler_incrementTimer(tBScheduler, &currentTime);
  //iterates over tasks in queue and checks  timeBasedScheduler_addPeriodicTask(tBScheduler, &transmit,200 ,1 , currentTime + 50, 0);

  //if their starttime <= currentTime
  timeBasedScheduler_markIfReady(tBScheduler,currentTime);
  sei();
  }

ISR(ADC_vect){

    cli();
    timeBasedScheduler_addTask(tBScheduler, &sendTemperature, 155, currentTime);
    sei();
}
//Interrupt ISR end