union UNION 
{
    int angle;
    byte mbyte[2];
};

union UNION u;

void setup() 
{
    Serial.begin(115200);
}

void loop() 
{
    int i = 0;

    Serial.print("mbyte[0]의 값을 입력하세요 : ");
    while (!Serial.available()) 
    {
        ; 
    }
    u.mbyte[0] = Serial.parseInt();
    Serial.read();

    Serial.print("mbyte[1]의 값을 입력하세요 : ");
    while (!Serial.available())
    {
        ; 
    }
    u.mbyte[1] = Serial.parseInt();
    Serial.read();

    Serial.print("angle: ");
    Serial.println(u.angle);
}
