void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int sensorValue = analogRead(A0);

  // 아날로그 값을 전압 (0 - 5V)으로 변환
  float Vout = sensorValue * (5.0 / 1023.0);

  // 첫 번째 저항의 저항 값 R1을 설정
  float R1 = 15.0;

  // 두 번째 저항 R2을 계산
  float R2 = (Vout * R1) / (5.0 - Vout);

  // Vout
  Serial.print("출력 전압 (Vout): ");
  Serial.print(Vout, 2); // 소수점 둘째 자리까지 출력
  Serial.println(" V");

  // R2값
  Serial.print("두 번째 저항 R2 값: ");
  Serial.print(R2, 2); // 소수점 둘째 자리까지 출력
  Serial.println(" 옴");

  delay(1000);
}
