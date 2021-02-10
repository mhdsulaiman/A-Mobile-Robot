# -*- coding: utf-8 -*-
"""
Created on Fri May 18 13:21:01 2018

@author: Suliman
"""
import numpy as np
import scipy as sc 
import random
import serial
from time import sleep
import json

ser=serial.Serial('COM6',38400,timeout=2)
def send_to_arduino(action):
    ser.open()
    sleep(1)
    ser.write(action.encode('utf-8'))
    sleep(1)
    ser.flushInput()
    ser.close()

def recieve_from_arduino():
  ser.open()
  p1=[]
  while (ser.isOpen()):
    while (ser.inWaiting()>0):
      p1.append(ser.readline().decode('utf-8'))
      sleep(1)
    ser.flushOutput()
    ser.close()
    return p1 
#----------------------------------------------------------------------------#
class state_sensor(object):
#we have to put default values for k1 k2 k3 k4 in case the sens_val all are zeros or ones
    def __init__(self,sens_val,L_dist=2,R_dist=2,L_sector=3,R_sector=3):
        self.sens_val=sens_val
        self.k1=L_dist #left distance
        self.k2=R_dist #right distance
        self.k3=L_sector #left sector
        self.k4=R_sector #right sector

#sens_val: list of sensors value received from arduino ex: [13, 23.5, 12.2, 53, 56]
    def sensor_zones(self):     
	#find left side sensor values of vehicle
       x=min(self.sens_val[0:3])
       if (x>40 and x<70):
        k1=1 #zone1
       elif(x<40):
        k1=0  #zone0
       elif(x>70):
        k1=2 #zone1
	
	#find right side sensor values of vehicle
       x=min(self.sens_val[2:])
       if (x>40 and x<70):
        k2=1 #zone1
       elif(x<40):
        k2=0  #zone0
       elif(x>70):
        k2=2 #zone1
        return k1,k2
   
    def sectors(self):
       bin_sens_val=[]	
       for i in range(len(self.sens_val)):
         if (self.sens_val[i]<100):
          bin_sens_val.append(1)
         else:
          bin_sens_val.append(0)
         print(bin_sens_val)
	
	#the left sector of the vehicle
       if ((bin_sens_val[1]==1 or bin_sens_val[2]==1) and bin_sens_val[0]==0):
          k3=0
		
       elif ((bin_sens_val[0]==1 and bin_sens_val[1]==1) and bin_sens_val[2]==0):
          k3=1
		
       elif (bin_sens_val[0]==0 and bin_sens_val[1]==0 and bin_sens_val[2]==1):
          k3=2
	
       elif ((bin_sens_val[1]==0 and bin_sens_val[2]==0) and bin_sens_val[0]==1):
          k3=3
		
	#the right sector of the vehicle
       if ((bin_sens_val[3]==1 or bin_sens_val[2]==1) and bin_sens_val[4]==0):
          k4=0
		
       elif ((bin_sens_val[4]==1 and bin_sens_val[3]==1) and bin_sens_val[2]==0):
          k4=1
		
       elif (bin_sens_val[4]==0 and bin_sens_val[3]==0 and bin_sens_val[2]==1):
          k4=2
       elif ((bin_sens_val[3]==0 and bin_sens_val[2]==0) and bin_sens_val[4]==1):
          k4=3
      
       return k3,k4
   
    def check_crash(self,crash_dist):
      for i in self.sens_val:
       if i<=crash_dist:
        return True
       else:
        return False
    
   
    def __str__(self):
      return str(self.state_sensor.k1)+" "+str(self.state_sensor.k2)+" "+str(self.sectors.k3)+" "+str(self.sectors.k4)
   
#----------------------------------------------------------------------------#       
class action_choosing_alg(object):
    def __init__(self,Q,state,action,epsilon,T):
        self.q=Q
        self.s=state
        self.a=action
        self.ep=epsilon
        self.t=T
        
    def epsilon_greedy_exploration(self,q,state,a,ep):
      if ((random.randrange(100)/100) > ep):
        a=max(q[state])
      else:
        a=random.randrange(0,3)
      return a
    
    
    def soft_max_selection(self,q,state,a,t):
 #    n_actions=len(actions)
     q=np.array(q[state])
     p=(sc.exp(q/t))/(sum(sc.exp(q)/t))
     rand=random.random()
  
     if (rand<p[0]):
       a=1
     elif(rand>=p[0] and rand<sum(p[1:3])):
       a=2
     elif(rand>=sum(p[1:3])):
       a=3 
     return a
#----------------------------------------------------------------------------#
class Qtable(object):
    
  def __init__ (self,state,action,reward,Q,next_state,alpha,gamma):
    self.s=state
    self.a=action
    self.r=reward
    self.q=Q
    self.n_s=next_state
    self.alpha=alpha
    self.gamma=gamma
    
  def qtable_generator(self):
  # Initialize a Q-table with zeros
    qtable={}
    for k1 in range(0,3):
      for k2 in range(0,3):
        for k3 in range(0,4):
          for k4 in range(0,4):
            kall=str(k1)+" "+str(k2)+" "+str(k3)+" "+str(k4)
            qtable[kall]=[0,0,0]
            self.q=qtable
            # return qtable
    
  def qtable_updater(self,s,a,r,n_s,alpha,gamma):
  # Update values in the Q-table
    qn=self.q
    qn[s][a]=qn[s][a]+ alpha*(r + gamma * max(qn[n_s])-qn[s][a])
    self.q=qn
 
  def getQtable(self):
    return self.q
  


  def qtable_retriver(self,txtfile):
    try:
      with open(txtfile, 'r') as f:
        a=json.load(f)
      return a
    except NameError:
      print('you forgot to import json!!')
    except :
      print('the file is empty!')
      
  
  def qtable_saver(self,txtfile):
    print("this will erase the contents of the file selected..")
    q=input("do you want to continue [y/n] :")
    if (q=='y'):
      try:
        with open(txtfile, 'w') as f:
          f.flush
          json.dump(getQtable(), f)
      except NameError:
        print('you forgot to import json!!')
#----------------------------------------------------------------------------#
def get_reward(action,prev_action,prev_sensor,sensor,crash):
  a=action
  terminate=False
  if a==0:
    r1=0.2
  elif a==1:
    r1=-0.1
  elif a==2:
    r1=-0.1
    
  if (sum(sensor)-sum(prev_sensor)) >=0 :
    r2= 0.2
  else:
    r2=-0.2
    
  if(prev_action==1 and a==2):
    r3=-0.8
  elif(prev_action==2 and a==1):
    r3=-0.8
   
  reward= r1 + r2 + r3
  if (crash==True):
    terminate=True
    reward=-100
  
  return (reward,terminate)
#----------------------------------------------------------------------------#  
    
if __name__ == '__main__':   
 max_trials = 10000     # Max Trials
 max_steps = 600        # Max steps
 alpha1  = 0.5          # Learning rate
 alpha2  = 0.03
 gamma   = 0.9          # Discount factor
 epsilon = 0.95         # Chance for random action
 T1 = 24                # The Paramater of the explore function with blotzmanns distribution
 crash_dist=5
 prev_a=0
 total_reward=0
 actions=[0,1,2] # 0-->forward  1-->left 2-->right 
 
  #------- observe initial state-------
 for i in range(max_trials):
  # get sensor values
  sensors=recieve_from_arduino()
  crash=state_sensor.check_crash(sensors)
  
  #------Discretization of the sensor values 
  state=state_sensor(sensors)
  
  #Keep sensor values from previous iteration
  prev_sensor = sensors
  
  #Select action with the exploration function
#  a = action_choosing_alg.epsilon_greedy_exploration(q, state, action_list, epsilon);
  a = action_choosing_alg.soft_max_selection(Qtable.getQtable(),state,actions,T1);
  
  #send the action to the robot to do it
  send_to_arduino(a)
  
  for i in range(max_steps):
    #read the sensors again
    sensor=recieve_from_arduino()
    #------Discretization of the sensor values 
    next_state=state_sensor(sensor)
    crash=state_sensor.check_crash(sensor)
    
    #get rewards
    (reward,terminate)= get_reward(a,prev_a,prev_sensor,sensor,crash)
    total_reward+=reward
    
    #update q table
    q=Qtable.qtable_updater(state,a,reward,Qtable.getQtable(),next_state,alpha1,gamma)
    #keep the last action change state to next_state
    prev_a=a
    state=next_state  