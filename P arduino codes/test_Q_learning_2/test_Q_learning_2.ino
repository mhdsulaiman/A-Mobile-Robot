long distances[5];

long distance1,distance2,distance3,distance4,distance5;
long duration1,duration2,duration3,duration4,duration5;

#define trigPin1 2 
#define echoPin1 3

#define trigPin2 4 
#define echoPin2 5

#define trigPin3 6
#define echoPin3 7

#define trigPin4 8
#define echoPin4 9

#define trigPin5 10
#define echoPin5 11


void scan_all()
{
  /*--RR--*/ 
  delay(60);
  // Determine distance from duration
  digitalWrite(trigPin1, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1/2) / 29.1;
  //Serial3.println(distance1);

  
  /*--R--*/
  delay(60); 
  digitalWrite(trigPin2, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2/2) / 29.1;
  //Serial3.println(distance2);
  /*--C--*/
  delay(60); 
  digitalWrite(trigPin3, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = (duration3/2) / 29.1;
 // Serial3.println(distance3);
  
  /*--L--*/
  delay(60);
  digitalWrite(trigPin4, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin4, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin4, LOW);
  duration4 = pulseIn(echoPin4, HIGH);
  distance4 = (duration4/2) / 29.1;
  //Serial3.println(distance4);
  
  /*--LL--*/ 
  delay(60);
  digitalWrite(trigPin5, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin5, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin5, LOW);
  duration5 = pulseIn(echoPin5, HIGH);
  distance5 = (duration5/2) / 29.1;
  //Serial3.println(distance5);
  
  //gather all sencors values in one matrix
 distances[0]=distance1;
 distances[1]=distance2;
 distances[2]=distance3;
 distances[3]=distance4;
 distances[4]=distance5;  
}

/*================================================================================================*/
#define enA 22
#define enB 23
#define in1 24
#define in2 25
#define in3 26
#define in4 27

void Fright()
{ digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(800);
  digitalWrite(enA,LOW);
  digitalWrite(enB,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  //delay(200);
  }
  
void Fleft()
{ digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(800);
  digitalWrite(enA,LOW);
  digitalWrite(enB,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  //delay(200);
  }
  
  void forword(){
  digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  //delay(2450);
  delay(1000);
  digitalWrite(enA,LOW);
  digitalWrite(enB,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  //delay(200);
  }

void setup() {
//*****************
pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
pinMode(trigPin3, OUTPUT);
pinMode(echoPin3, INPUT);
pinMode(trigPin4, OUTPUT);
pinMode(echoPin4, INPUT);
pinMode(trigPin5, OUTPUT);
pinMode(echoPin5, INPUT);
//*****************
//MOTORS
pinMode(enA,OUTPUT);
pinMode(enB,OUTPUT);
pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);
//*****************
Serial3.begin(38400);
Serial.begin(38400);
scan_all();
}

int recived_data;//start and action
void loop() {


//sending 5 sensord value

if(Serial3.available()>0)
recived_data=Serial3.read()-'0';
/*================================================================================================*/
 //motors
 if(recived_data!=0){
  if(recived_data==1){ 
    forword();
    scan_all();}
   if(recived_data==2){
    Fright();
    scan_all();}
   if(recived_data==3){
    Fleft();
    scan_all();}
    if(recived_data==5){
    {delay(1000);
    for(int i=0;i<5;i++)
    Serial3.println(distances[i]);
    memset(distances,0,sizeof(distances));}
    recived_data=0;}
 }//end if
  }//end loop
