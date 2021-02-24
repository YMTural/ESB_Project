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

for x in range(0,256):
    received = int.from_bytes(ser.read(1), "little")
    if(x != received):
        error = True
        failed += 1
        print("Error! Expected ", str(x), " Was ", str(received))
if error == False:
    successfull += 1
    print("Test Successfull: Received Numbers from 0 to 255\n")




error = False
print("Test UART_receive: Expecting incremented echo for numbers from 0 to 255")

for x in range(0,256):
    ser.write(x.to_bytes(1,"little"))
    received = int.from_bytes(ser.read(1), "little")
    if(((x + 1) % 256) != received):
        error = True
        failed += 1
        print("Error! Expected ", str((x + 1) % 256), " Was ", str(received))

if error == False:
    successfull += 1
    print("Test Successfull: Echo received as expected\n")
timeEnd = time.time()
timeDelta = round((timeEnd - timeStart), 3)
print("Summary:\n\tSuccessful Tests:" + str(successfull) +"\n\tFailed Tests: " + str(failed) +"\n\tDuration: " + str(timeDelta) + "s")