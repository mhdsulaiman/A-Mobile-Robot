#define enA 22
#define enB 23
#define in1 24
#define in2 25
#define in3 26
#define in4 27

void left()
{ digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);}
void right()
{ digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);}

void forword(){
  digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);}
void back()
{ digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);}
  void STOP()
{ digitalWrite(enA,LOW);
  digitalWrite(enB,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);}
  
void setup() {
  // put your setup code here, to run once:
pinMode(enA,OUTPUT);
pinMode(enB,OUTPUT);
pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);
Serial3.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial3.available())
{int m=Serial3.read();
  if(m=='w'){
    forword();
    Serial3.println("i will go forward");}
    
    else if(m=='s'){
    back();
    Serial3.println("i will go backward");
  }
   else if(m=='a'){
    right();
    Serial3.println("i will go right");
}
  else if(m=='d'){
    left();
    Serial3.println("i will go left");
}
  else if(m=='z'){
    STOP();
    Serial3.println("i will go left");
}
}
}
