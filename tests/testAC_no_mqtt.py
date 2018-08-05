#!/usr/bin/env python3
# -*- coding: utf-8 -*-
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
result=mbclient.write_register(0, 20, unit=4)
print(result)