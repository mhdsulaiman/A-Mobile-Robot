#include "NewPing.h"

int enA=22;
int enB=23;
int in1=24;
int in2=25;
int in3=26;
int in4=27;


int index=0;
int bluetooth_data[40];
int coo_arr[40];//0 1 11 21

int key1=0;
int key2=0;
int key3=0;
int first;
int second;
int command;
String face="south";
int cmd_n1=-1;
int cmd_p1=1;
int cmd_p10=10;
int cmd_n10=-10;



#define TRIGGER_PIN  2
#define ECHO_PIN     3
#define MAX_DISTANCE 400
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
float distance;
float problem_distance=20;
int problem=0;


//make sure is there an object that detected by sensors
void obj_ahead(){
distance = sonar.ping_cm();
if (distance >= 400 || distance <= 2){}
  
  else if(distance>problem_distance && distance<400){ 
  forword();
  Serial.println("Ending the step");
  delay(100);
  }//move forword when there is no object detected   
  
  else if (distance <= problem_distance)
   problem=1;
    
  
}

//convert the path into points(x,y)
void make_coordinate( int a[],int size1)
{ int mul,sum;
  for (int k=0 ;k<size1;k=k+2)
  {
    mul=(a[k])*10;
    sum=(a[k+1])+mul;
    
    coo_arr[index]=sum;
    index++;
    sum=0;
    mul=0;
    }//end for
    index=0;
    }//end coordinate



//to operate the Dc motors
void Fright()
{ digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(1000);
  digitalWrite(enA,LOW);
  digitalWrite(enB,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay(200);}//end Fright
  
void Fleft()
{ digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(1000);
  digitalWrite(enA,LOW);
  digitalWrite(enB,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay(200);}//end Fleft

void left()
{ digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(2000);
  digitalWrite(enA,LOW);
  digitalWrite(enB,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay(100);}//end left
  
void right()
{ digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(2000);
  digitalWrite(enA,LOW);
  digitalWrite(enB,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay(100);}//end right 

void forword(){
  digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(4600);
  digitalWrite(enA,LOW);
  digitalWrite(enB,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay(200);}//end forword
  
void back()
{ digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(4600);
  digitalWrite(enA,LOW);
  digitalWrite(enB,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay(200);}//end back

  
/*
           10
          NORTH

 1 WEST          EAST -1 
        
         SOUTH
          -10

*/

//
void make_a_move(int cmd){
  
  if (cmd ==cmd_n1){
    Serial.println("cmdn1");
    
    if (face=="south"){
      left();
      face="east";
      obj_ahead();}
       //======function===
      //check sensore
      //if sensore true
      //send problem to python
      //break
      //=======end function
    else if (face=="north"){
      right();
      face="east";
    obj_ahead();}
    
    else if (face=="west"){
      right();
      right();
      face="east";
      obj_ahead();}
    
     else if (face=="east"){
     obj_ahead();}}
  
  if (cmd==cmd_n10){
   Serial.println("cmdn10");
   
    if (face=="south"){
     obj_ahead();}
     
    else if (face=="north"){
      right();
      right();
      face="south";
      obj_ahead();}
      
    else if (face=="west"){
      left();
      face="south";
      obj_ahead();}
      
    else if (face=="east"){
      right();
      face="south";
      obj_ahead();}}//end if

      if (cmd==cmd_p1){
       Serial.println("cmdp1");
    
    if (face=="south"){
      right();
      face="west";
      obj_ahead();}
    
    else if (face=="north"){
      left();
      face="west";
      obj_ahead();}
    
    else if (face=="west"){
      obj_ahead();}
    
    else if (face=="east"){
      right();
      right();
      face="west";
      obj_ahead();}}//end if

      
    if (cmd==cmd_p10){
     Serial.println("cmdp10");
     
    if (face=="south"){
      right();
      right();
      face="north";
      obj_ahead();}
    
    else if (face=="north"){
      obj_ahead();}
    
    else if (face=="west"){
      right();
      face="north";
      obj_ahead();}
    
    else if (face=="east"){
      left();
      face="north";
      obj_ahead();}}//end if
     else{}//do nthing
  }
  




void setup() {
// put your setup code here, to run once:
pinMode(enA,OUTPUT);
pinMode(enB,OUTPUT);
pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);
// making sure that those pins are low
//initializing 
digitalWrite(enA,LOW);
digitalWrite(enB,LOW);
digitalWrite(in1,LOW);
digitalWrite(in2,LOW);
digitalWrite(in3,LOW);
digitalWrite(in4,LOW);



Serial3.begin(38400);
Serial.begin(38400);
    
}

void loop() {
 /*Serial.println(cmd_n1);//byte :255 
  Serial.println(cmd_p1);//byte :1
  Serial.println(cmd_n10);//byte :246
  Serial.println(cmd_p10);//byte :10*/ 
 if(Serial3.available()>0) 
{ /*Serial3.println(String(5));
  Serial3.write('5');
  Serial3.write(5 - '0');*/
 //Serial3.println(String(second));

  Serial.println("waiting for data:");
  for (int n =0; n<40; n=n+1){  // should read 10 Tags 
        bluetooth_data[n] = Serial3.read() - '0'; // convert data received from BT to integer 
        delay(100);
        
}//end for
key1=1;
Serial3.end();
 
  
    Serial.println("finish reciving data.."); 

//keys for controlling the procedures
if (key1==1)
{
     Serial.println("making coordinates");
      make_coordinate(bluetooth_data,40);
      
    
      key1=0;//the following procedure
      key2=1;
    
}//finish making coordinates
    
if(key2==1)
{
 Serial.println("entring for loop");
 delay(1000);
 
 for (int i=0 ;i<20;i++)
 {
  first=coo_arr[i];
  second=coo_arr[i+1];
  command=first-second;
 /* Serial.print("the step num");
  Serial.print(i);
  Serial.println(":");
  
  Serial.print(first);
  Serial.print(",");
  Serial.println(second);
  Serial.println(command);*/

 make_a_move(command); 
 if(problem==1){//break for loop if there is object making problem
 Serial3.begin(38400);
 Serial3.print(second);
 Serial.println("point:"+String(second)+" have a problem");
 break;}//end if
 
}//end for
Serial.println("exiting for loop");
  if(problem==0){
  Serial3.begin(38400);
  Serial3.print("END");
  }
  
  key2=0;
  problem=0;
 
}//end if key2
}//end Serial3.available
} //end void loop 

 
  

  

