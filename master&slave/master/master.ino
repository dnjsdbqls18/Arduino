/*
// 마스터에서 슬레이브에 1이라는 데이터를 송신하는 코드
#include <Wire.h>

void setup()
{
  Serial.begin(115200);
  Wire.begin();
}

void loop()
{
  Wire.beginTransmission(1); // 1이라는 주소를 가진 슬레이브에 데이터 송신을 시작
  Wire.write(1);
  Wire.write(2);
  Wire.write(3);
  Wire.endTransmission(); // 슬레이브에 1,2,3이라는 데이터 송신
  delay(250);
}
*/

#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(115200); 
}

byte x = 0;

void loop() {
  Wire.beginTransmission(1);                
  Wire.write("f ");       
  Wire.write(x);             
  Wire.endTransmission();    
     
  delay(500);
  
  Wire.requestFrom(1, 4); //슬레이브(1)에 4byte 요청
  while (Wire.available()) {
    char c = Wire.read(); 
    Serial.print(c);        
  }    
  x++;
  if(x==6)x=0;  
}
