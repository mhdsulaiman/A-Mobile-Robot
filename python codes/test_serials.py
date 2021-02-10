# -*- coding: utf-8 -*-
"""
Created on Sun May 27 14:32:52 2018

@author: Suliman
"""
import serial
from time import sleep
ser=serial.Serial('COM6',38400,timeout=2)
def send_to_arduino(action):
    print("i am sending to arduino")
    ser.open()
    sleep(1)
    ser.write(action.encode('utf-8'))
    sleep(1)
    ser.flushInput()
    ser.close()

def recieve_from_arduino():
  print("iam reciving from arduino")
  p1=[]
  while True:
      re=ser.readline().decode('utf-8')
      re=int(re)
      p1.append(re)
      sleep(1)
      if(len(p1)==5):
          break
  ser.flushOutput()
  ser.close()
  print(p1)
  return p1 
if __name__ == '__main__': 
 recieve_from_arduino()
 a=input("put your action? ")
 send_to_arduino(a)
    