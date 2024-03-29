
////////////////////////// sonar ////////////////////////
#include <NewPing.h>

#define SONAR_NUM 3      // Number of sensors.
#define MAX_DISTANCE 150 // Maximum distance (in cm) to ping.

#define Front 0
#define Left  1
#define Right 2

#define TRIG1 2  // 초음파 센서 1번 Trig 핀 번호
#define ECHO1 3  // 초음파 센서 1번 Echo 핀 번호

#define TRIG2 4  // 초음파 센서 2번 Trig 핀 번호 왼쪽
#define ECHO2 5  // 초음파 센서 2번 Echo 핀 번호

#define TRIG3 6  // 초음파 센서 3번 Trig 핀 번호 오른쪽
#define ECHO3 7  // 초음파 센서 3번 Echo 핀 번호

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(TRIG1, ECHO1, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(TRIG2, ECHO2, MAX_DISTANCE),
  NewPing(TRIG3, ECHO3, MAX_DISTANCE)
};

  float front_sonar   = 0.0;
  float left_sonar    = 0.0;
  float right_sonar   = 0.0;


///////////////////////// Maze Status ////////////////////
int maze_status = 0;

void setup() 
{
 Serial.begin(115200); // 통신속도를 115200으로 정의함 
}


void check_maze_status(void)
{
   if( (left_sonar >= 0) && (left_sonar <= 200) && (front_sonar >= 0) && (front_sonar <= 200) && (right_sonar >= 0) && (right_sonar <= 200) )
 {
     maze_status = 4;
     Serial.println("maze_status = 4");
 }
  else if( (left_sonar >= 0) && (left_sonar <= 200) && (right_sonar >= 0) && (right_sonar <= 200) )
 {
     maze_status = 1;
     Serial.println("maze_status = 1");
 }
  else  if( (left_sonar >= 0) && (left_sonar <= 200) && (front_sonar >= 0) && (front_sonar <= 200) )
 {
     maze_status = 2;
     Serial.println("maze_status = 2");
 }
  else  if( (right_sonar >= 0) && (right_sonar <= 200) && (front_sonar >= 0) && (front_sonar <= 200) )
 {
     maze_status = 3;
     Serial.println("maze_status = 3");
 }
  else
 {
    maze_status = 0;
    Serial.println("maze_status = 0");
 }

}


void loop()
{
  //put your main code here, to run repeatedly:

 
  front_sonar = sonar[Front].ping_cm()*10;       // 전방 센서 측정
  left_sonar  = sonar[Left].ping_cm()*10;        // 좌측 센서 측정
  right_sonar = sonar[Right].ping_cm()*10;       // 우측 센서 츨측정
  if(front_sonar == 0.0) front_sonar = MAX_DISTANCE;        // 0.0 출력이 최대값이므로
  if(left_sonar  == 0.0)  left_sonar  = MAX_DISTANCE;
  if(right_sonar == 0.0) right_sonar = MAX_DISTANCE;

  Serial.print("L:");Serial.print(left_sonar);    Serial.print("  ");
  Serial.print("F:");Serial.print(front_sonar);   Serial.print("  ");
  Serial.print("R:");Serial.println(right_sonar);    

  check_maze_status();
  delay(500);
}
  
