#include <Servo.h>

#define RC_SERVO_PIN          8
#define NEURAL_ANGLE         90
#define NEURAL_ANGLE_offset   0 

Servo Steeringservo;

union UNION
{
    int angle_offset;
    byte mbyte[2];
};

union UNION u;

void setup()
{
    Serial.begin(115200); 
    Steeringservo.attach(RC_SERVO_PIN);
}

int steering_control()
{
  Steeringservo.write(u.angle_offset + NEURAL_ANGLE + NEURAL_ANGLE_offset);
}

void loop() 
{   
  steering_control();

  int i = 0;

  Serial.print("mbyte[0]의 값을 입력하세요 : ");
  while (!Serial.available()) 
  {
      ; 
  }
  u.mbyte[0] = Serial.parseInt();
  Serial.println(u.mbyte[0]);
  Serial.read();

  Serial.print("mbyte[1]의 값을 입력하세요 : ");
  while (!Serial.available()) 
  {
      ; 
  }
  u.mbyte[1] = Serial.parseInt();
  Serial.println(u.mbyte[1]);
  Serial.read();

  Serial.print("angle_offset: ");
  Serial.println(u.angle_offset);

  Serial.print("angle: ");
  Serial.println(NEURAL_ANGLE + u.angle_offset);
  Serial.println("");
}
