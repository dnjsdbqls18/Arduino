#include <Wire.h>
#include <Servo.h>
#define SLAVE_ADDRESS 9 

#define RC_SERVO_PIN          8
#define NEURAL_ANGLE         90

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
    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
    Steeringservo.attach(RC_SERVO_PIN);
}

void receiveEvent(int numBytes) 
{
    if (numBytes == 2) 
    {
        u.mbyte[0] = Wire.read();
        u.mbyte[1] = Wire.read();
        
        Serial.print("Received mbyte[0]: ");
        Serial.println(u.mbyte[0]);
        Serial.print("Received mbyte[1]: ");
        Serial.println(u.mbyte[1]);
        
        Serial.print("angle_offset: ");
        Serial.println(u.angle_offset);
        
        Serial.print("angle: ");
        Serial.println(NEURAL_ANGLE + u.angle_offset);
        Serial.println("");
       
        Steeringservo.write(NEURAL_ANGLE + u.angle_offset);
    }
}

void requestEvent()
{ 
  Wire.write("recieve!\n");   
}

void loop() 
{
    // 추가 작업이 필요 없을 때는 루프를 비워둡니다.
}
