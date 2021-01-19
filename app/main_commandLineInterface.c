#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

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

//Switch to enumeration after implementing MQTT Client
volatile static const char multiCommands[NUMBEROFMULTICOMMANDS][LONGESTCOMMAND] = {"echo", "led", "flash", "sine", "periodic", "kill"};
volatile static const char singleCommands[NUMBEROFSINGLECOMMANDS][LONGESTCOMMAND] = {"help", "toggle", "inc", "counter", "temp", "list"};                                             

volatile static const char helpMessage[] = "Folgende Befehle sind verfügbar: help, echo <string>, led <bit>, flash <int>, sine <int>, inc, counter, temp, periodic, kill <id>, list";

volatile uint8_t* transBuffer;
volatile uint8_t* recBuffer;

volatile circularBuffer_t cTransmitbuffer;
volatile circularBuffer_t cReceivebuffer;

volatile priorityQueueHeap_t pQueue;

volatile UART_interrupt_t uBuf;

volatile timeBasedScheduler_t tBScheduler;
//Declare here for determine task
void receive(void);

//SingleCommands
void task_help(void){


  for (uint8_t i = 0; i < strlen(helpMessage); i++)
  {
    circularBuffer_push(cTransmitbuffer, helpMessage[i]); 
  }
  UART_interrupt_transmitFromBufferInit(uBuf, strlen(helpMessage));
}





void awaitNextCommand(void){

  UART_interrupt_receiveToBufferInit(uBuf,MAXCOMMANDLENGTH);
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
      timeBasedScheduler_addTask(tBScheduler, &task_help, 150, currentTime);
      break;
    
    default:
      break;
    }

  }
  


/*
  for (uint8_t i = 0; i < lengthFirstPart; i++)
  {
    circularBuffer_push(cTransmitbuffer, receivedCommand[i]);
  }

  for (uint8_t i = 0; i < NUMBEROFCOMMANDS; i++)
  {
  }
  UART_interrupt_transmitFromBufferInit(uBuf, commandLength-1);*/
  commandLength = 0;
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


void toggleLed(void){

  PORTB ^= _BV(5);
}

int main() {

  sei();
  
  DDRB = _BV(5);
  PORTB ^= _BV(5);

  pQueue = priorityQueueHeap_init(128);

  transBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
  recBuffer = malloc(sizeof(uint8_t)*BUFFERSIZE);
  
  cTransmitbuffer = circularBuffer_init(transBuffer, BUFFERSIZE);
  cReceivebuffer = circularBuffer_init(recBuffer, BUFFERSIZE);

  tBScheduler = timeBasedScheduler_init(16, pQueue,priorityQueueHeap_size, priorityQueueHeap_capacity, priorityQueueHeap_add, priorityQueueHeap_peekAt, priorityQueueHeap_getNextReady, priorityQueueHeap_deleteItem);

  uBuf = UART_interrupt_init(cReceivebuffer, cTransmitbuffer, circularBuffer_overwrite, circularBuffer_push, circularBuffer_read);

  
  //Blinking
  //timeBasedScheduler_addPeriodicTask(tBScheduler, &toggleLed, 155, 100, currentTime, 0);

  //Receive next item 1ms
  timeBasedScheduler_addPeriodicTask(tBScheduler, &receive, 250, 0, currentTime + 50, 0);

  //Transmit next item on Buffer 2ms
  timeBasedScheduler_addPeriodicTask(tBScheduler, &transmit,200 ,1 , currentTime + 50, 0);

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
  sei();
}

ISR(TIMER0_COMPA_vect){

  cli();
  //keeps track of the number of ms passed
  timeBasedScheduler_incrementTimer(tBScheduler, &currentTime);
  //iterates over tasks in queue and checks
  //if their starttime <= currentTime
  timeBasedScheduler_markIfReady(tBScheduler,currentTime);
  sei();
  }

ISR(ADC_vect){

    cli();
    adc_temperature_temperatureReady = 1;
    sei();
}
//Interrupt ISR end