union UNION
{
    float test;
    byte mbyte[4];
};

void setup() 
{
    Serial.begin(115200); // 시리얼 통신 시작

    union UNION u;
    u.test = 123.456; // 테스트할 float 값 설정

    for (int i = 0; i < 4; i++)
    {
        Serial.print("mbyte[");
        Serial.print(i);
        Serial.print("] = ");
        Serial.println(u.mbyte[i]);
    }
    Serial.println(); // 개행

    Serial.println(u.test); // 변환된 float 값 출력
}

void loop() 
{

}
