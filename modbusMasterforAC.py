#import serial
import time
#import pymodbus
#from pymodbus.pdu import ModbusRequest
from pymodbus.client.sync import ModbusSerialClient as ModbusClient 
#from pymodbus.transaction import ModbusRtuFramer
#import sys
import paho.mqtt.client as mqtt



mbclient= ModbusClient(method = "rtu", timeout=1, port='/dev/ttyACM0',stopbits = 1, bytesize = 8, parity = 'N', baudrate = 19200)
connection = mbclient.connect()
print(connection)
time.sleep(2)

def send_cmd(x):
    result=mbclient.write_register(0, x, unit=4)
    print(result)

def on_message(client, userdata, message):
    msg=str(message.payload.decode("utf-8"))
    print("message received " ,msg)
    print("message topic=",message.topic)
    print("message qos=",message.qos)
    print("message retain flag=",message.retain)
    try:msg=int(msg)
    except: return
    send_cmd(msg)
    

broker_address="localhost"
print("creating new instance")
client = mqtt.Client("P1") #create new instance
client.on_message=on_message #attach function to callback
print("connecting to broker")
client.connect(broker_address) #connect to broker
#client.loop_start() #start the loop
print("Subscribing to topic","actuate/modbus/ac")
client.subscribe("actuate/modbus/ac")
#time.sleep(1) # wait
client.loop_forever() #stop the loop
#mbclient.close()
