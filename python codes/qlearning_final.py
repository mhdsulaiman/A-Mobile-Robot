# -*- coding: utf-8 -*-
"""
Created on Fri May 18 12:36:38 2018

@authors: Nazeeh Saifi - M.suliman tanbari
"""
import json
import scipy as sc 
import numpy as np 
import random
import serial 
from time import sleep


#"""======= initilizing the serial port  =========="""
ser=serial.Serial()
ser.port='COM6'
ser.baudrate=38400
ser.timeout=2
#"""================================================"""
#"""========== communicating with arduino fuctions ================"""

def send_to_arduino(a):
    ser.write(a.encode('utf-8'))
    ser.flushInput()
    

def recieve_from_arduino():
    p1=[]
    while (ser.isOpen()):
      p=ser.readline().decode('utf-8')
      if (p=='\r\n') or (p==''):
        pass
      else:
        p1.append(int(p.rstrip('\r\n')))
        if len(p1)==5 :
          ser.flushOutput()
          break
    return p1 

def recieve_from_arduino_using_read():
    p1=[]
    while (ser.isOpen()):
      p=ser.read(ser.inWaiting()).decode('utf-8')
      if len(p)==0 or len(p)==1:
        pass
      else:
        a=p.split('\r\n')
        a.pop(-1)
        p1=[int(a) for a in a]
        ser.flushOutput()
        break
    return p1 
#"""================================================"""

  
#"""------- Q-table functions ---------"""
def qtable_updater(state,action,reward,Q,next_state,alpha,gamma):
  # Update values in the Q-table
  Q[state][action-1]=Q[state][action-1]+ alpha*(reward + gamma * max(Q[next_state])-Q[state][action-1])
#  return Q
  
def qtable_generator():
  # Initialize a Q-table with zeros
  qtable={}
  for k1 in range(0,4):
    for k2 in range(0,4):
      for k3 in range(0,4):
        for k4 in range(0,4):
          kall=str(k1)+" "+str(k2)+" "+str(k3)+" "+str(k4)
          qtable[kall]=[0,0,0]
  return qtable
def qtable_retriver(txtfile):
  try:
    with open(txtfile, 'r') as f:
      a=json.load(f)
    f.close
    return a
  except NameError:
    print('you forgot to import json!!')
  except :
    print('the file is empty!')
      
  
def qtable_saver(txtfile,qtable):
    try:
      with open(txtfile, 'w') as f:
          f.flush
          json.dump(qtable, f)
      f.close
    except NameError:
      print('you forgot to import json!!')
#      """========================="""

#"""--------choosing action fuctions -----------"""
def get_best_action(q,state,action):
  status=False
  if sum(q[state])==0:
    status=True
  
  if status==True:
    a= random.randrange(0,3)
  else:
    a= q[state].index(max(q[state]))
  return a+1
 
def epsilon_greedy_exploration(Q,state,action,epsilon):
  if (random.random() > epsilon):
    a=get_best_action(q,state,action)
  else:
    a=random.randrange(1,4)
  return a
    
    
def soft_max_selection(q,state,t):
#  n_action=len(action)
  q=np.array(q[state])
  n=(sc.exp(q/t))
  m=(sum(sc.exp(q/t)))
  p=n/m
  rand=random.random()

  if (rand<p[0]):
    a=1
  elif(rand>=p[0] and rand<sum(p[0:2])):
    a=2
  elif(rand>=sum(p[0:2])):
    a=3 
  return a
#"""================================================"""


def check_crash(sens_val,crash_dist):
  crash=False
  for i in range(len(sens_val)):
    if sens_val[i]<=crash_dist:
      crash=crash or True
  return crash 
    
    
def get_reward(action,prev_action,prev_sensor,sensor,crash):
  a=action
  r1 = 0
  r2 = 0
  r3 = 0
  reward = 0
  if a==1:
    r1=0.2
  elif a==2:
    r1=-0.1
  elif a==3:
    r1=-0.1
    
  if (sum(sensor)-sum(prev_sensor)) >=0 :
    r2= 0.2
  else:
    r2=-0.2
    
  if(prev_action==2 and a==3):
    r3=-0.8
  elif(prev_action==3 and a==2):
    r3=-0.8
   
  reward= r1 + r2 + r3
  if (crash==True):
    reward=-100
  
  return reward

def state_sensor(sens_val):
#we have to put default values for k1 k2 k3 k4 in case the sens_val all are zeros or ones
  k1=3
  k2=3
  k3=3
  k4=3
	#find left side sensor values of vehicle
  x=min(sens_val[0:3])
  if (x>20 and x<=40):
      k1=1 #zone1
  elif(x<=20):
      k1=0  #zone0
  elif(x>40 and x<=60):
      k1=2 #zone1
  elif (x>60):
      k1=3
	#find right side sensor values of vehicle
  x=min(sens_val[2:])
  if (x>20 and x<=40):
      k2=1 #zone1
  elif(x<=20):
      k2=0  #zone0
  elif(x>40 and x<=60):
      k2=2 #zone1
  elif (x>60):
      k2=3
      
  np_sens_val=np.array(sens_val)	
  bin_sens_val=np_sens_val<100
#  
#  """===========================BAD US======================="""
#  #the left sector of the vehicle
#  if ((bin_sens_val[1]==1 or bin_sens_val[2]==1) and bin_sens_val[0]==0):
#      k3=0
#		
#  elif ((bin_sens_val[0]==1 and bin_sens_val[1]==1) and bin_sens_val[2]==0):
#      k3=1
#		
#  elif (bin_sens_val[0]==0 and bin_sens_val[1]==0 and bin_sens_val[2]==1):
#      k3=2
#	
#  elif ((bin_sens_val[1]==0 and bin_sens_val[2]==0) and bin_sens_val[0]==1):
#      k3=3
		
#	#the right sector of the vehicle
#  if ((bin_sens_val[3]==1 or bin_sens_val[2]==1) and bin_sens_val[4]==0):
#      k4=0
#		
#  elif ((bin_sens_val[4]==1 and bin_sens_val[3]==1) and bin_sens_val[2]==0):
#      k4=1
#		
#  elif (bin_sens_val[4]==0 and bin_sens_val[3]==0 and bin_sens_val[2]==1):
#      k4=2
#  elif ((bin_sens_val[3]==0 and bin_sens_val[2]==0) and bin_sens_val[4]==1):
#      k4=3
#  """========================THEM================================="""
#  if ((bin_sens_val[1]==1 or bin_sens_val[2]==1) and bin_sens_val[0]==0):
#      k3=0
#		
#  elif ((sum(bin_sens_val[0:2])==2 or bin_sens_val[0]==1) and bin_sens_val[2]==0):
#      k3=1
#		
#  elif (sum(bin_sens_val[0:3])==3) :
#      k3=2
#	
# 
#	#the right sector of the vehicle
#  if ((bin_sens_val[3]==1 or bin_sens_val[2]==1) and bin_sens_val[4]==0):
#      k4=0
#		
#  elif ((sum(bin_sens_val[3:5])==2 or bin_sens_val[4]==1) and bin_sens_val[2]==0):
#      k4=1
#
#  elif (sum( bin_sens_val[2:5])==3):
#      k4=2
  
  """========================US Final=Them - 010 sector2 ================================="""
  if (bin_sens_val[0]==0 and bin_sens_val[1]==1 and bin_sens_val[2]==1) \
    or (bin_sens_val[0]==0 and bin_sens_val[1]==0 and bin_sens_val[2]==1):
      k3=0
		
  elif (sum(bin_sens_val[0:2])==2 and bin_sens_val[2]==0):
      k3=1
		
  elif (sum(bin_sens_val[0:3])==3) or (bin_sens_val[0]==0 and bin_sens_val[1]==1 and bin_sens_val[2]==0) :
      k3=2
	
 
	#the right sector of the vehicle
  if ((bin_sens_val[2]==1 and bin_sens_val[3]==1 and bin_sens_val[4]==0) \
      or (bin_sens_val[2]==1 and bin_sens_val[3]==0 and bin_sens_val[4]==0)) :
      k4=0
		
  elif (sum(bin_sens_val[3:5])==2  and bin_sens_val[2]==0):
      k4=1
      
  elif (sum( bin_sens_val[2:5])==3) or (bin_sens_val[2]==0 and bin_sens_val[3]==1 and bin_sens_val[4]==0):
      k4=2
  return ""+str(k1)+" "+str(k2)+" "+str(k3)+" "+str(k4)+""

        
#"""test states"""

#for i in range(99,101):
#    for j in range(99,101):
#        for k in range(99,101):
#           for m in range(99,101):
#             for h in range(99,101):
#                    q.append([i,j,k,m,h])
#res=[state_sensor(k) for k in q]
# for i in range(32):
#    print(res[i],"=",q[i])      
#                    
def table_trials(q,alpha,gamma,t,max_staps):
  print(q)
  print(t)
  prev_a=0
  total_reward=0
  crash_alert=False

 
#  """------- observe initial state-------"""
  
  send_to_arduino('5')
  sleep(0.2)
  sensor_data=recieve_from_arduino()
  print("sensor_data:",sensor_data)
  crash=check_crash(sensor_data,10)
  if crash==True:
    print("there is a crash!!")
#------Discretization of the sensor values 
  state=state_sensor(sensor_data)
  print("=====================================================")
  for i in range(max_steps):
      print("step num:",i)
      print("i am in state :",state)
      
      #Keep sensor values from previous iteration
      prev_sensor = sensor_data
      
      #Select action with the exploration function
      a=soft_max_selection(q,state,t)
      """a = epsilon_greedy_exploration(q,state,action_list,epsilon);"""
      print("action is :",a)
      
      #send the action to arduino to do it
      send_to_arduino(str(a))
      sleep(1)
      #read the sensors again
      send_to_arduino('5')
      sleep(0.2)
      sensor_data=recieve_from_arduino()
      print("sensor_data:",sensor_data)
      
      #------Discretization of the sensor values 
      next_state=state_sensor(sensor_data)
      print("i am in state :",next_state)
      crash=check_crash(sensor_data,7)
      
      #get rewards
      reward= get_reward(a,prev_a,prev_sensor,sensor_data,crash)
      total_reward+=reward
      print("reward is:",reward)

      #update q table
      qtable_updater(state,a,reward,q,next_state,alpha,gamma)
      if crash==True:
        crash_alert=True
        break
#      if (i % 500==0):
#        qpause=input("do you want to stop the trials??")
#        if qpause='y':
#          break
      #keep the last action change state to next_state
      prev_a=a
      state=next_state
      print("=====================================================")
  return(q,i,total_reward,crash_alert)
 
 
  
  
if __name__=='__main__':
  ser.open()
  max_trials = 10000     # Max Trials
  max_steps = 600       # Max steps
  alpha1  = 0.5          # Learning rate
  alpha3  = 0.03
  alpha2=0.25
  gamma   = 0.9          # Discount factor
  epsilon =0.95       # Chance for random action
  
  # T1 = 24                # The Paramater of the explore function with blotzmanns distribution
  # q=qtable_generator()   #retrive the last qtable from txt file
  # rot=[]
  # sot=[]
  # num_trial=0
  # num_crash=0
  # cot=[]

  q=qtable_retriver("qsoft.txt")    #retrive the last qtable from txt file
  rot=qtable_retriver("r_for_trial.txt")
  sot=qtable_retriver("s_for_trial.txt")
  num_trial=qtable_retriver("numtrials.txt")
  T1=qtable_retriver("last1.txt")
  cot=qtable_retriver("crash_for_trial.txt")
  for k in range(max_trials):
    try:
      print("please return the robot to the first position !")
      quest=input("do you want to continuew with the next trial? [y/n]:")
      if quest=='y':
        print("==========  Trial num",k,"============")
        (q,i,tot_r,crash)=table_trials(q,alpha1,gamma,T1,max_steps)
        print(q)
        rot.append(tot_r)
        sot.append(i+1)
        if crash==True:
          cot.append(1)
        else:
          cot.append(0)
        if T1>0.001:
          T1*=0.95
          
      elif quest=='n':
        question1=input("do you want to save the variables [y/n]:")
        if question1=='y':
          num_trial+=k
          qtable_saver("qsoft.txt",q)
          qtable_saver("s_for_trial.txt",sot)
          qtable_saver("r_for_trial.txt",rot)
          qtable_saver("numtrials.txt",num_trial)
          qtable_saver("last1.txt",T1)
          qtable_saver("crash_for_trial.txt",cot)
          ser.close()
          break
        elif question1=='n':
          ser.close()
          break
        
    except KeyboardInterrupt:
      question2=input("do you want to save the variables [y/n]:")
      if question2=='y':
        num_trial+=k
        qtable_saver("qsoft.txt",q)
        qtable_saver("s_for_trial.txt",sot)
        qtable_saver("r_for_trial.txt",rot)
        qtable_saver("numtrials.txt",num_trial)
        qtable_saver("last1.txt",T1)
        qtable_saver("crash_for_trial.txt",cot)
        ser.close()
        break
      elif question2=='n':
        ser.close()
        break
    
