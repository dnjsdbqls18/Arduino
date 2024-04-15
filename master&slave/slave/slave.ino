/*
// 슬레이브에서 마스터가 송신한 데이터를 수신하는 코드

#include <Wire.h>

void setup()
{
  Serial.begin(115200);  
  Wire.begin(1); // 슬레이브 자신을 1이라는 주소로 지정 마스터에서 1이라는 주소 사용
  Wire.onReceive(receiveEvent); // 데이터를 수신했을 시 receieceEvent라는 함수 실행
}

void receiveEvent(int parameter)
{
  while(Wire.available() > 0)
  {
    char a = Wire.read(); //버퍼에 찬 데이터 read
    Serial.print(a);
    Serial.print(" ");
  } // 시리얼 모니터에 1,2,3이 출력됨
}

void loop()
{

}
*/

#include <Wire.h>

void setup() {
  Wire.begin(1); //슬레이브 주소                
  Wire.onRequest(requestEvent); //요청시 requestEvent함수 호출
  Wire.onReceive(receiveEvent); //데이터 전송 받을 때 receiveEvent함수 호출

  Serial.begin(115200);           
}

void loop() {
  delay(500);
}

void receiveEvent(int howMany) { //전송 데이터 읽기
  while (Wire.available()>1) { 
    char ch = Wire.read(); 
    Serial.print(ch);         
  }
  int x = Wire.read();   
  Serial.println("값 확인"); 
  Serial.println(x); 
  Serial.println("확인");     
}
void requestEvent() { //요청 시 수행 함수
  Wire.write("ok!\n");   
}
