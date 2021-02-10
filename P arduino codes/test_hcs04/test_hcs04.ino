#include <NewPing.h>



float duration_RR,duration_R,duration_C,duration_L,duration_LL;
float distance_RR,distance_R,distance_C,distance_L,distance_LL;
float max_distance=400.0;

#define trigPin_RR 2 //Rightmost
#define echoPin_RR 3

#define trigPin_R 4//Right
#define echoPin_R 5

#define trigPin_C 6 //Center
#define echoPin_C 7

#define trigPin_L 8 //left
#define echoPin_L 9

#define trigPin_LL 10 //Leftmost
#define echoPin_LL 11

NewPing sonar5(trigPin_RR,echoPin_RR,max_distance);
NewPing sonar4(trigPin_R,echoPin_R,max_distance);
NewPing sonar3(trigPin_C,echoPin_C,max_distance);
NewPing sonar2(trigPin_L,echoPin_L,max_distance);
NewPing sonar1(trigPin_LL,echoPin_LL,max_distance);
int iteration=5;
void scan_all(int num)
{
  /*--RR--*/ 
  if (num==5)
  {/*
  digitalWrite(trigPin_RR, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_RR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_RR, LOW);*/
  
  // Measure the response from the HC-SR04 Echo Pin
  //duration_RR = pulseIn(echoPin_RR, HIGH);
 // duration_RR=sonar5.ping();
  // Determine distance from duration
  // Use 343 metres per second as speed of sound
  //distance_RR = (duration_RR / 2) * 0.0343;
   //distance_RR=sonar5.ping_cm();
      distance_RR=sonar5.ping_median(iteration);

  Serial3.println(distance_RR);
  

  }
  /*--R--*/
  else if (num==4)
  {/*
  digitalWrite(trigPin_R, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_R, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_R, LOW);*/

  //duration_R=sonar4.ping();
  //duration_R = pulseIn(echoPin_R, HIGH);
  //distance_R = (duration_R / 2) * 0.0343;
  //distance_R=sonar4.ping_cm();
  distance_R=sonar4.ping_median(iteration);


  Serial3.println(distance_R);
  }
   
  /*--C--*/ 
  else if (num==3)
  {/*
  digitalWrite(trigPin_C, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_C, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_C, LOW);
  */
  //duration_C=sonar3.ping();
  //duration_C = pulseIn(echoPin_C, HIGH);
 // distance_C = (duration_C / 2) * 0.0343;
 // distance_C=sonar3.ping_cm();
 distance_C=sonar3.ping_median(iteration);


  Serial3.println(distance_C);

  }

  /*--L--*/ 
  else if (num==2)
  {/*
  digitalWrite(trigPin_L, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_L, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_L, LOW);
  */
  // duration_L=sonar2.ping();
  //duration_L = pulseIn(echoPin_L, HIGH);
  //distance_L = (duration_L / 2) * 0.0343;
  //distance_L=sonar2.ping_cm();
   distance_L=sonar2.ping_median(iteration);


  Serial3.println(distance_L);

  }
  
  /*--LL--*/ 
  else if (num==1)
  {
    /*
  digitalWrite(trigPin_LL, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_LL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_LL, LOW);
  */
  //duration_LL=sonar1.ping();

  //duration_LL = pulseIn(echoPin_LL, HIGH);
  //distance_LL = (duration_LL / 2) * 0.0343;
  //distance_LL=sonar1.ping_cm();
  distance_LL=sonar1.ping_median(iteration);


  Serial3.println(distance_LL);
  }
  
  //gather all sencors values in one matrix
  
}

void setup() {
/*  
//ULTRA Sonic
pinMode(trigPin_RR, OUTPUT);
pinMode(echoPin_RR, INPUT);
pinMode(trigPin_R, OUTPUT);
pinMode(echoPin_R, INPUT);
pinMode(trigPin_C, OUTPUT);
pinMode(echoPin_C, INPUT);
pinMode(trigPin_L, OUTPUT);
pinMode(echoPin_L, INPUT);
pinMode(trigPin_LL, OUTPUT);
pinMode(echoPin_LL, INPUT);*/

//*****************
Serial3.begin(38400);
Serial.begin(38400);
}

int key=0
int cmd;
void loop() {

 //Serial.println("looping 1");
if(Serial3.available()>0)
{
  cmd = Serial3.read() - '0';
  Serial3.flush();
  key=1;
}
 
 if(key==1){
  //Serial.println("looping 2");
  Serial.println(cmd);
if (cmd==1)
{
  
  Serial.println("im doing action 1");
  Serial3.println("end");
  key2=0;
  key1=1;
}
if (cmd==2)
{
  
  Serial.println("im doing action 2");
  Serial3.println("end");
  key2=0;
  key1=1;
}
if (cmd==3)
{
  
  Serial.println("im doing action 3");
  Serial3.println("end");
  key2=0;
  key1=1;

}
if (cmd==5)
{
  
  Serial.println("im checking sensor data");
  Serial3.println(21);
    Serial3.println(22);
      Serial3.println(23);
        Serial3.println(24);
          Serial3.println(25);
    key2=0;
    key1=1;
}


}//end if key2
}//end loop

