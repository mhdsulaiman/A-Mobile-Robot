
int enA=22;
int enB=23;
int in1=24;
int in2=25;
int in3=26;
int in4=27;

int state=0;
void Fright()
{
  digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(1100);
  digitalWrite(enA,LOW);
  digitalWrite(enB,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay(200);
}
void Fleft()
{
  digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(1100);
  digitalWrite(enA,LOW);
  digitalWrite(enB,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay(200);
}























void left()
{
  digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(2200);
  digitalWrite(enA,LOW);
  digitalWrite(enB,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay(200);
}
void right()
{
  digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(2200);
  digitalWrite(enA,LOW);
  digitalWrite(enB,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay(200);
  }

void forword(){
  digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);

  delay(4500);
  digitalWrite(enA,LOW);
  digitalWrite(enB,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay(200);
  }
void back()
{
  digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);

  delay(4500);
  digitalWrite(enA,LOW);
  digitalWrite(enB,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay(200);
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


Serial.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
 
  if(Serial.available()>0)
  {state=Serial.read();  
  
  if(state=='3')
  {Serial.println("Forward");
    forword();}
 

  else if(state== '0')
  {Serial.println("Backword");
    back();}
  
  else if(state=='5')
  {Serial.println("Right");
    right();}
  
else if(state=='4')
{ Serial.println("left");
   Fright(); }
else if(state=='2')
{ Serial.println("left");
   Fleft(); }

else if(state=='1')
{ Serial.println("left");
   left(); }



   
  }
}
