#include <MsTimer2.h>

int LedPin = 13;
int LedFlash = LOW;

void setup() {
  pinMode(LedPin, OUTPUT);
  MsTimer2::set(100, timerISR);
  MsTimer2::start();
}

void loop() {
}

void timerISR() {
  if (LedFlash == LOW) LedFlash = HIGH;
  else LedFlash = LOW;
  digitalWrite(LedPin, LedFlash);
}
