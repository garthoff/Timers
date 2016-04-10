// Mruga wbudowaną diodą świecącą przy pomocy biblioteki Timers
// Autor: Łukasz Tretyn - http://nettigo.pl

#include <Timers.h>

Timer ledBlinkTimer;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  ledBlinkTimer.begin(SECS(2));
}

void loop() {
  if (ledBlinkTimer.available())
  {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    ledBlinkTimer.restart();
  }
}
