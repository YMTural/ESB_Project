import paho.mqtt.client as mqtt
import serial
import io
import threading
import time
import re
ser = serial.Serial('/dev/ttyACM0')
time.sleep(2)
client = mqtt.Client(client_id="yusuf",userdata="yusuf")
thermostatOn = 0
maxTemp = 25
averageTemps = {}
ledStatus = 1
tempString = "Die aktuelle Temperatur des Chips betraegt: "
# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("yusuf/commands",0)
    client.subscribe("enableThermostat",0)
    client.subscribe("+/temp")
    client.subscribe("averageTemps")


def on_enableThermostat(client, userdata, msg):
    param = int(msg.payload.decode('UTF-8'))
    global thermostatOn
    if thermostatOn != param:
        if param == 1:
            sendToArduino("periodic 2 temp")
            thermostatOn = 1
        else:
            sendToArduino("kill 0")
            thermostatOn = 0


def on_temp(client, userdata, msg):
    global averageTemps
    #averageTemps["dummy"] = 24
    averageTemps[msg.topic] = int(msg.payload.decode('UTF-8'))
    average = sum(list(averageTemps.values()))/float(len(averageTemps))
    print(averageTemps)
    client.publish("averageTemps",str(average))


def on_averageTemps(client, userdata, msg):
    global ledStatus
    temp = float(msg.payload.decode('UTF-8'))
    if(temp >= maxTemp):
        if(ledStatus == 1):
            sendToArduino("led 0")
            ledStatus = 0
    else:
        if(ledStatus == 0):
            sendToArduino("led 1")
            ledStatus = 1


# The callback for when a PUBLISH message is received from the server and passed all filters above.
def on_message(client, userdata, msg):
    print("Received Message:" + msg.payload.decode('UTF-8'))
    sendToArduino(msg.payload.decode('UTF-8'))


def receiveFromArduino():
    while True:
        message = ser.readline().decode('UTF-8')
        print("Arduino Output:" + message)
        if(message != ""):
            if(len(re.findall(r'(?<=Die aktuelle Temperatur des Chips betraegt: )\d+(?=C$)', message)) != 0 and thermostatOn == 1):
                #Only matches to my temperature message and extracts the temperature
                client.publish("yusuf/temp", re.findall(r'(?<=Die aktuelle Temperatur des Chips betraegt: )\d+(?=C$)', message)[0])

            client.publish("yusuf/output", message)


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


client.on_connect = on_connect
client.on_message = on_message

client.message_callback_add("enableThermostat", on_enableThermostat)
client.message_callback_add("+/temp", on_temp)
client.message_callback_add("averageTemps", on_averageTemps)
client.connect("134.91.79.29", 1883, 60)
client.loop_start()  
time.sleep(4)
client.publish("enableThermostat","1")
while True:    
    
    time.sleep(4)
    
    #time.sleep(6)
    #client.publish("/enableThermostat","0")
    #time.sleep(6)
    #sendToArduino(input())
