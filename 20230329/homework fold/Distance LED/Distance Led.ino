////////////////////////// sonar ////////////////////////
#include <NewPing.h>

#define SONAR_NUM 3      // Number of sensors.
#define MAX_DISTANCE 150 // Maximum distance (in cm) to ping.

#define Front 0
#define Left  1
#define Right 2

#define TRIG1 2  // 초음파 센서 1번 Trig 핀 번호
#define ECHO1 3  // 초음파 센서 1번 Echo 핀 번호

#define TRIG2 4  // 초음파 센서 2번 Trig 핀 번호
#define ECHO2 5  // 초음파 센서 2번 Echo 핀 번호

#define TRIG3 6  // 초음파 센서 3번 Trig 핀 번호
#define ECHO3 7  // 초음파 센서 3번 Echo 핀 번호

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(TRIG1, ECHO1, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(TRIG2, ECHO2, MAX_DISTANCE),
  NewPing(TRIG3, ECHO3, MAX_DISTANCE)
};

///////////////////////// L298N //////////////////////////
#define ENA 8
#define IN1 9
#define IN2 10
#define IN3 11
#define IN4 12
#define ENB 13



void setup() 
{
  //put your setup code here, to run once:
 /*
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);
  pinMode(TRIG3, OUTPUT);
  pinMode(ECHO3, INPUT);
*/
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
 
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  

  Serial.begin(115200); // 통신속도를 115200으로 정의함 
}

long sonar_front(void)  //초음파 센서 1번 측정 함수
{
  long duration1, distance1; 
  digitalWrite(TRIG1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG1, LOW);
  duration1 = pulseIn(ECHO1, HIGH);
  distance1 = ( (float) (340*duration1)/1000)/2;
  return distance1;
}



void loop()
{
  //put your main code here, to run repeatedly:
  float front_sonar   = 0.0;

 
  front_sonar = sonar[Front].ping_cm()*10;
  if(front_sonar == 0.0) front_sonar = MAX_DISTANCE;
  Serial.print("Distance 1:");
  Serial.println(front_sonar);

  if((front_sonar > 0) && (front_sonar <= 200.0 ))
  
  {digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);   // wait for a second
  }
   else
   {
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second

  }
}
