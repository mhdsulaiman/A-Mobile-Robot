int enA=22;
int enB=23;
int in1=24;
int in2=25;
int in3=26;
int in4=27;

void setup() {
  // put your setup code here, to run once:
pinMode(enA,OUTPUT);
pinMode(enB,OUTPUT);
pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
delay(3000);
digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(2100);
  digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}
