#include <NewPing.h>

int distances[5];

#define maxdistance 400

float distance_RR,distance_R,distance_C,distance_L,distance_LL;

#define echoPin_RR 11 //Rightmost
#define trigPin_RR 10

#define echoPin_R 9//Right
#define trigPin_R 8

#define echoPin_C 7 //Center
#define trigPin_C 6

#define echoPin_L 5 //left
#define trigPin_L 4

#define echoPin_LL 3 //Leftmost
#define trigPin_LL 2

NewPing sonar1(trigPin_RR,echoPin_RR,maxdistance);
NewPing sonar2(trigPin_R,echoPin_R,maxdistance);
NewPing sonar3(trigPin_C,echoPin_C,maxdistance);
NewPing sonar4(trigPin_L,echoPin_L,maxdistance);
NewPing sonar5(trigPin_LL,echoPin_LL,maxdistance);

void scan_all(int a)
{
  delay(50);
  /*--RR--*/ 
  // Determine distance from duration
  if(a==1){
  distance_RR = sonar1.ping_cm();
  Serial.print("Rightmost sensor: ");
  Serial3.println(distance_RR);}
  
  /*--R--*/ 
  else if(a==2){
 distance_R = sonar2.ping_cm();
  Serial.print("Right sensor: ");
  Serial3.println(distance_R);}
  
  /*--C--*/ 
  else if(a==3){
distance_C = sonar3.ping_cm();
  Serial.print("Center sensor: ");
  Serial3.println(distance_C);}
  
  /*--L--*/
  else if(a==4){
  distance_L =sonar3.ping_cm();
  Serial.print("Left sensor: ");
  Serial3.println(distance_L);}
  
  /*--LL--*/ 
  else if(a==5){
  distance_LL =sonar4.ping_cm();
  Serial.print("Leftmost sensor: ");
  Serial3.println(distance_LL);}
  
  //gather all sencors values in one matrix
  distances[0]=distance_LL;
  distances[1]=distance_L;
  distances[2]=distance_C;
  distances[3]=distance_R;
  distances[4]=distance_RR;  
}
void setup() {
 Serial3.begin(38400);
Serial.begin(38400);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial3.available()>0)
{
  int a=Serial3.read()-'0';
  scan_all(a);}
}

