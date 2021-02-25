import serial
import io
import time
import threading


ser = serial.Serial('/dev/ttyACM0')
time.sleep(2)

def receiveFromArduino():
    while True:
        message = ser.read().decode('ASCII')
        print("Arduino Output:" + message)

def sendToArduino(msg):
    if(msg != ""):
        print("Input String:" + msg +";")
        message = ser.write(msg.encode('UTF-8'))
        ser.write(b'\n')

try:
    thread_receiveFromArduino = threading.Thread(target = receiveFromArduino)
    thread_receiveFromArduino.start()
    
except Exception as e:
    print("Something went wrong: " +str(e) )
"""
#sendToArduino('periodic 2 temp')
time.sleep(3)
for x in range(256):
    time.sleep(0.05)
    sendToArduino('led 0')
    time.sleep(0.05)
    sendToArduino('led 1')
#sendToArduino('counter')
"""
"""
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/power.h>

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
timeBasedScheduler_t tBScheduler;
volatile uint16_t time = 0;
bool isSleepTime = false;
int main(void)
{
  UART_init(MYUBRR);
  sei();
  power_adc_enable();
  power_timer2_enable();
  power_timer1_enable();
  power_usart0_enable();
  sleep_enable();
  set_sleep_mode(SLEEP_MODE_IDLE);
  tBScheduler = timeBasedScheduler_init(&time, 0,0,0,0,0,0,0);
  while (true)
  {

    sleep_mode();
    UART_transmit(time);
  }
  

  DDRB = _BV(5);
  PORTB ^= _BV(5);
}

ISR(TIMER2_COMPA_vect){
  cli();
  //keeps track of the number of ms passed
  timeBasedScheduler_incrementTimer(tBScheduler);
  sei();
  }
"""