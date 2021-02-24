import serial
import io
import time
import random
print("\nIntegration Test for UART_buffer.c\n")


ser = serial.Serial('/dev/ttyACM0')
timeStart = time.time()
successfull = 0
failed = 0

BUFFERSIZE = int(255)


error = False
print("Test UART_buffer_transmitMultipleFromBuffer: Expecting numbers from 0 to " +str(BUFFERSIZE - 1))
for x in range(0, BUFFERSIZE):
    received = int.from_bytes(ser.read(1), "little")
    #print(received)
    if(x != received):
        error = True
        print("Error! Expected ", str(x), " Was ", str(received))
if error == False:
    successfull += 1
    print("Test Successfull: Received Numbers from 0 to  " +str(BUFFERSIZE - 1)+ "\n")
else:
    failed += 1




error = False
print("Test UART_buffer_receive: Expecting echo of random input")
inputList = []
for x in range(0, BUFFERSIZE):
    randInt8 = random.randint(0,255)   
    inputList.append(randInt8)
    #print(randInt8)
    ser.write(randInt8.to_bytes(1,"little")) 
for x in range(0, BUFFERSIZE):
    received = int.from_bytes(ser.read(1), "little")
    #print(received)
    if(received != inputList[x]):
        error = True
        print("Error! Expected ", str(inputList[x]), " Was ", str(received))
if error == False:
    successfull += 1
    print("Test Successfull: Received correct Echo\n")
else:
    failed += 1

error = False
print("Test Simple Echo")

for x in range(0, 1024):
    randInt8 = random.randint(0,255)   
    ser.write(randInt8.to_bytes(1,"little")) 
    received = int.from_bytes(ser.read(1), "little")
    if(received != randInt8):
        error = True
        print("Error! Expected ", str(randInt8), " Was ", str(received))
    else:
        #print("Sent: " + str(randInt8) + ", Received: " + str(received))
        pass
if error == False:
    successfull += 1
    print("Test Successfull: Received correct Echo\n")
else:
    failed += 1

timeEnd = time.time()
timeDelta = round((timeEnd - timeStart), 3)

print("Summary:\n\tSuccessful Tests:" + str(successfull) +"\n\tFailed Tests: " + str(failed) +"\n\tDuration: " + str(timeDelta) + "s")