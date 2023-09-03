#include <MsTimer2.h>

const int pulsePin = 18;

void Pulse()
{
  static boolean pulseState = LOW;
  digitalWrite(pulsePin, pulseState);
  pulseState = !pulseState;
}

void setup()
{
  pinMode(pulsePin, OUTPUT);
  MsTimer2::set(2, Pulse);
  MsTimer2::start();
}

void loop()
{

}
