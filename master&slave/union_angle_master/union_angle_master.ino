#include <Wire.h>

#define SLAVE_ADDRESS 9

union UNION
{
    int angle_offset;
    byte mbyte[2];
};

union UNION u;

void setup() 
{
    Serial.begin(115200);
    Wire.begin();
}

void loop() 
{
    Serial.print("mbyte[0] 입력: ");
    while (!Serial.available()) 
    {
        ; 
    }
    u.mbyte[0] = Serial.parseInt();
    Serial.println(u.mbyte[0]);
    Serial.read();

    Serial.print("mbyte[1] 입력: ");
    while (!Serial.available()) 
    {
        ; 
    }
    u.mbyte[1] = Serial.parseInt();
    Serial.println(u.mbyte[1]);
    Serial.read();
    
    Serial.print("angle_offset: ");
    Serial.println(u.angle_offset);
    Serial.println("");

    Wire.beginTransmission(SLAVE_ADDRESS);
    Wire.write(u.mbyte[0]);
    Wire.write(u.mbyte[1]);
    Wire.endTransmission();
}
