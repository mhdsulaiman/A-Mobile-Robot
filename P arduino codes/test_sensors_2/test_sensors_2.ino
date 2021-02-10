long duration_rr,duration_r,duration_c,duration_l,duration_ll;
long distance_rr,distance_r,distance_c,distance_l,distance_ll;


int echoPin_RR =11; //Rightmost
int trigPin_RR =10;

int echoPin_R=9; //Right
int trigPin_R=8;

int echoPin_C=7; //Center
int trigPin_C=6;

int echoPin_L=5; //left
int trigPin_L=4;

int echoPin_LL=3; //Leftmost
int trigPin_LL=2;
/*............................................................
/*................................................................*/
void scan_all(int a)
{
  if(a==1){
   if (distance_rr >= 500 || distance_rr <= 0){Serial3.println(1);}//do nothing
   else{
   delay(500); 
  digitalWrite(trigPin_RR, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_RR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_RR, LOW);
  // Measure the response from the HC-SR04 Echo Pin
  duration_rr = pulseIn(echoPin_RR, HIGH);

  // Determine distance from duration
  // Use 343 metres per second as speed of sound
  distance_rr = (duration_rr / 2) / 29.1;
   Serial3.println(distance_rr);
    duration_rr,distance_rr=0;}}
    
  else if(a==2){
    if (distance_r >= 500 || distance_r <= 0){Serial3.println(2);}
    else{
    delay(500); 
  digitalWrite(trigPin_R, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_R, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_R, LOW);
  // Measure the response from the HC-SR04 Echo Pin
  duration_r = pulseIn(echoPin_R, HIGH);

  // Determine distance from duration
  // Use 343 metres per second as speed of sound
  distance_r = (duration_r / 2) * 0.0343;
   Serial3.println(distance_r);
   duration_r,distance_r=0;}}

  else if(a==3){
     if (distance_c >= 500 || distance_c <= 0){Serial3.println(3);}
     else{
     delay(500);
  digitalWrite(trigPin_C, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_C, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_C, LOW);
  // Measure the response from the HC-SR04 Echo Pin
  duration_c = pulseIn(echoPin_C, HIGH);

  // Determine distance from duration
  // Use 343 metres per second as speed of sound
  distance_c = (duration_c / 2) * 0.0343;
   Serial3.println(distance_c);
    duration_c,distance_c=0;}}

  else if(a==4){
     if (distance_l >= 500 || distance_l <= 0){Serial3.println(4);}
    else{
    delay(500); 
  digitalWrite(trigPin_L, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_L, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_L, LOW);
  // Measure the response from the HC-SR04 Echo Pin
  duration_l = pulseIn(echoPin_L, HIGH);

  // Determine distance from duration
  // Use 343 metres per second as speed of sound
  distance_l = (duration_l / 2) * 0.0343;
   Serial3.println(distance_l);
    duration_l,distance_l=0;}}

  else if(a==5){
     if (distance_ll >= 500 || distance_ll <= 0){Serial3.println(5);}
     else{
    delay(500); 
  digitalWrite(trigPin_LL, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_LL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_LL, LOW);
  // Measure the response from the HC-SR04 Echo Pin
  duration_rr = pulseIn(echoPin_LL, HIGH);

  // Determine distance from duration
  // Use 343 metres per second as speed of sound
  distance_ll = (duration_ll / 2) * 0.0343;
  Serial3.println(distance_ll);
   duration_ll,distance_ll=0;}}
}



void setup() {
  // put your setup code here, to run once:
pinMode(trigPin_RR, OUTPUT);
pinMode(echoPin_RR, INPUT);
pinMode(trigPin_R, OUTPUT);
pinMode(echoPin_R, INPUT);
pinMode(trigPin_C, OUTPUT);
pinMode(echoPin_C, INPUT);
pinMode(trigPin_L, OUTPUT);
pinMode(echoPin_L, INPUT);
pinMode(trigPin_LL, OUTPUT);
pinMode(echoPin_LL, INPUT);

Serial3.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial3.available()>0)
{
  int a=Serial3.read()-'0';
  scan_all(a);}
}

