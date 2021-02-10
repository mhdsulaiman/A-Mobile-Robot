
int enA=22;
int enB=23;
int in1=24;
int in2=25;
int in3=26;
int in4=27;

int state=0;
int index=0;
char input_data[40];
char coo_arr[20];

int key1=0;
int key2=0;
int key3=0;
char first;
char second;
char command;
String face="south";
char cmd_n1=-1;
char cmd_p1=1;
char cmd_p10=10;
char cmd_n10=-10;
char zero=240;

void make_coordinate( char a[],int size1)
{ char mul,sum;
  for (int i=0 ;i<size1;i=i+2){
    mul=(a[i]-48)*10;
    sum=(a[i+1]-48)+mul;
    coo_arr[index]=sum;
    index++;
    sum=0;
    mul=0;}}




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
  delay(100);}
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
  delay(100);}

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
  delay(200);}
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
  delay(200);}

  
/*
           10
          NORTH

 1 WEST          EAST -1 
        
         SOUTH
          -10

*/

void make_a_move(char cmd){
  if (cmd ==cmd_n1){
    if (face=="south"){
      left();
      face="east";
      forword();}
    else if (face=="north"){
      right();
      face="east";
      forword();}
    else if (face=="west"){
      right();
      right();
      face="east";
      forword();}
     else if (face=="east"){
      forword();}}//end if
  
  if (cmd==cmd_n10){
    if (face=="south"){
      forword();}
    else if (face=="north"){
      right();
      right();
      face="south";
      forword();}
    else if (face=="west"){
      left();
      face="south";
      forword();}
    else if (face=="east"){
      right();
      face="south";
      forword();}}//end if

      if (cmd==cmd_p1){
    if (face=="south"){
      right();
      face="west";
      forword();}
    else if (face=="north"){
      left();
      face="west";
      forword();}
    else if (face=="west"){
      forword();}
    else if (face=="east"){
      right();
      right();
      face="west";
      forword();}}//end if

      
    if (cmd==cmd_p10){
    if (face=="south"){
      right();
      right();
      face="north";
      forword();}
    else if (face=="north"){
      forword();}
    else if (face=="west"){
      right();
      face="north";
      forword();}
    else if (face=="east"){
      left();
      face="north";
      forword();}}//end if
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
  char input_data[40];
 if(Serial3.available()>0) 
{ 
    Serial3.readBytes(input_data,40);
    key1=1;
    }

if (key1==1){
    
      make_coordinate(input_data,40);
      
    
    key1=0;
    key2=1;}
    
if(key2==1){
 delay(5000);
 for (int i=0 ; i<20;i++){
  if (i==19)
    break;
    
  first=coo_arr[i];
  second=coo_arr[i+1];
  command=first-second;
  //Serial.println(command,DEC);
  make_a_move(command);
}
  
  key2=0;
  key3=1;}
/*if (key3==1){
 
  for (int i=0;i<40;i++)
  {input_data[i]=0;}
  key3=0;
}*/
  delay(100);}

  

  

