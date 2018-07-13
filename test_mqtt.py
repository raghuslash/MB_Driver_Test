#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import time
import paho.mqtt.client as paho
broker="broker.hivemq.com"
broker="iot.eclipse.org"
broker="localhost"
#define callback
def on_message(client, userdata, message):
    time.sleep(1)
    print("received message =",str(message.payload.decode("utf-8")))

client= paho.Client("client-001") #create client object client1.on_publish = on_publish #assign function to callback client1.connect(broker,port) #establish connection client1.publish("house/bulb1","on")
######Bind function to callback
client.on_message=on_message
#####
print("connecting to broker ",broker)
client.connect(broker)#connect
client.loop_start() #start loop to process received messages
print("subscribing ")
client.subscribe("modbus")#subscribe
time.sleep(3)
#print("publishing ")
#client.publish("house/bulb1","on")#publish
#client.disconnect() #disconnect
client.loop_forever() #stop loop