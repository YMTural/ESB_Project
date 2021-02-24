import serial
import io
import time

print("\nIntegration Test for UART.c\n")


ser = serial.Serial('/dev/ttyACM0')
timeStart = time.time()
successfull = 0
failed = 0

error = False
print("Test UART_transmit: Expecting numbers from 0 to 255")


    print("Test Successfull: Received Numbers from 0 to 255\n")




error = False
print("Test UART_receive: Expecting incremented echo for numbers from 0 to 255")

timeEnd = time.time()
timeDelta = round((timeEnd - timeStart), 3)
print("Summary:\n\tSuccessful Tests:" + str(successfull) +"\n\tFailed Tests: " + str(failed) +"\n\tDuration: " + str(timeDelta) + "s")