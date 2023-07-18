const int pinEncoderA = 2;
const int pinEncoderB = 3;
volatile int counter = 0;
volatile int encoderB = 0;

void Interrupt() {
  encoderB = digitalRead(pinEncoderB);

  if (encoderB == LOW) 
  {
    counter++;
  }
  else if (encoderB == HIGH) 
  {
    counter--;
  }
  else
  {

  }
}

void setup() {
  Serial.begin(115200);

  pinMode(pinEncoderA, INPUT_PULLUP);
  pinMode(pinEncoderB, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinEncoderA), Interrupt, RISING);
}

void loop() 
{
  Serial.print("A: 1");
  Serial.print(" | B: ");
  Serial.print(encoderB);
  Serial.print(" | Counter: ");
  Serial.print(counter);
  Serial.println();
}
