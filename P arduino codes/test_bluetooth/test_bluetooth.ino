int state =0;
int led =46;
void setup() {
  // put your setup code here, to run once:
pinMode(led,OUTPUT);
digitalWrite(led,LOW);
Serial3.begin(38400);
Serial.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial3.available()>0)
{
  state=Serial3.read() - '0';
  delay(100);
 // Serial.print(state);
  if(state == 0){
  digitalWrite(led,LOW);
  Serial3.println(0);
  state = 0;
}
else if(state == 1)
{
    digitalWrite(led,HIGH);
  Serial3.println(1);
  state=0;
}
  
}
}

