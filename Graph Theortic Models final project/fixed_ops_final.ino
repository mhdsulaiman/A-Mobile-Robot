int mats=40;
/*================================================================================================*/
int index=0;
int bluetooth_data[41];
int coo_arr[41];

/*..................................................................*/

void make_coordinate( int BA[],int size1)
{ int mul,sum;
  for (int i=0 ;i<size1;i=i+2){
    
    mul=(BA[i])*10;
    sum=(BA[i+1])+mul;
    coo_arr[index]=sum;
    index=index+1;
    sum=0;
    mul=0;}
    index=0;}
/*================================================================================================*/



/*================================================================================================*/
#define trigPin 6
#define echoPin 7
float duration, distance;
/*................................................................*/
void scan()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Measure the response from the HC-SR04 Echo Pin
  duration = pulseIn(echoPin, HIGH);

  // Determine distance from duration
  // Use 343 metres per second as speed of sound
  distance = (duration / 2) * 0.0343;
}
/*================================================================================================*/





/*================================================================================================*/

bool problem=false;
/*........................................................*/

void obj_ahead(float prob_dist)
{ scan();
  if ((distance>=400) ||  (distance<=2))
    problem=false;
  else if (distance<=prob_dist)
    problem=true;
  }

/*================================================================================================*/



/*================================================================================================*/

#define enA 0
#define enB 1
#define in1 24
#define in2 25
#define in3 26
#define in4 27
/*.......................................................................................................*/

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
  delay(200);}
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
  delay(200);}
void left()
{ analogWrite(enA,250);
  analogWrite(enB,245);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(2000);
  analogWrite(enA,0);
  analogWrite(enB,0);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay(100);}
void right()
{ analogWrite(enA,250);
  analogWrite(enB,245);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(2000);
  analogWrite(enA,0);
  analogWrite(enB,0);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay(100);}

void forword(){
  analogWrite(enA,250);
  analogWrite(enB,250);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(5625);
  analogWrite(enA,0);
  analogWrite(enB,0);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);}

/*================================================================================================*/
/*================================================================================================*/

  
/*
           10
          NORTH

 1 WEST          EAST -1 
        
         SOUTH
          -10
*/

/*================================================================================================*/

String face="south";
int cmd_n1=-1;
int cmd_p1=1;
int cmd_p10=10;
int cmd_n10=-10;
/*................................................................*/

void make_a_move(int cmd){
  
  if (cmd ==cmd_n1){
    Serial.println("cmdn1");
    if (face=="south"){
      left();
      face="east";
       }
    else if (face=="north"){
      right();
      face="east";
       }
    else if (face=="west"){
      left();
      left();
      face="east";
       }
     else if (face=="east"){
       }}//end if
  
  if (cmd==cmd_n10){
    Serial.println("cmdn10");
    if (face=="south"){
       }
    else if (face=="north"){
      left();
      left();
      face="south";
       }
    else if (face=="west"){
      left();
      face="south";
       }
    else if (face=="east"){
      right();
      face="south";
       }}//end if

      if (cmd==cmd_p1){
        Serial.println("cmdp1");
    if (face=="south"){
      right();
      face="west";
       }
    else if (face=="north"){
      left();
      face="west";
       }
    else if (face=="west"){
       }
    else if (face=="east"){
      left();
      left();
      face="west";
       }}//end if

      
    if (cmd==cmd_p10){
      Serial.println("cmdp10");
    if (face=="south"){
      left();
      left();
      face="north";
       }
    else if (face=="north"){
       }
    else if (face=="west"){
      right();
      face="north";
       }
    else if (face=="east"){
      left();
      face="north";
       }}//end if
     else{}//do nthing
  }
/*================================================================================================*/







/*================================================================================================*/
void setup() {
//MOTORS
pinMode(enA,OUTPUT);
pinMode(enB,OUTPUT);
pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);
/*****************/
//ULTRA Sonic
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
//*****************
Serial3.begin(38400);
Serial.begin(38400);
}//end void setup()
/*================================================================================================*/


/*================================================================================================*/

int key1=0;
int key2=0;
int key3=0;
int first;
int second;
int command;
/*.................................................................*/

void loop() {
 if(Serial3.available()>0) 
{ Serial.println(".:phase 1 recieving:.");
  for (int n =0; n<mats; n=n+1)
  { 
    bluetooth_data[n] = Serial3.read() - '0'; // convert data received from BT to integer 
    delay(100);
    //Serial.println(bluetooth_data[n]);
  }//end for
    key1=1;
   Serial.println(".:end phase 1:."); 
}//end if

/*================================================================================================*/

if (key1==1)
{Serial3.flush();
 
Serial.println(".:phase 2 make coordinates:.");
  make_coordinate(bluetooth_data,mats);
  key1=0;
  key2=1;
  Serial.println(".:end phase 2 :.");
 }
/*================================================================================================*/
 
if(key2==1){
  
  Serial.println(".:phase 3 :.");
 bool val=true;
 for (int i=0 ; i<mats;i++){
  
  first=coo_arr[i];
  second=coo_arr[i+1];
  command=first-second;
  Serial.print("the step num");
  Serial.print(i);
  Serial.println(":");
  
  Serial.print(first);
  Serial.print(",");
  Serial.println(second);
  Serial.println(command);
  make_a_move(command);
  obj_ahead(50.0);
  
 
  if (problem==true)
    { 
      
      Serial3.println(second);
      problem=false;
      val=false;
      break;
      //endif
    }
  else if (command==10 || command==-10 || command==1 || command==-1){
    Serial.println("forwording");
    forword();
    }
 }//end for
 if (val==true)
 
 {
  Serial3.println("end");
  
  }
  
  Serial.println(".:end phase 3 :.");
  key2=0;
  memset(bluetooth_data, 0, sizeof(bluetooth_data));
  memset(coo_arr, 0, sizeof(bluetooth_data));
  }// end ifkey
  }//end void loop()
/*================================================================================================*/
/*================================  THE       END  =========================================*/


  

  

