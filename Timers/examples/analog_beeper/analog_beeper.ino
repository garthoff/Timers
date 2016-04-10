// Głośnik podłączony do pinu 3 genetuje przerywane sygnały dźwiękowe
// Sygnały są tym częstsze, im wyższe jest napięcie na wejściu analogowym A0
// Autor: Łukasz Tretyn - http://nettigo.pl

#include <Timers.h>

// config
const byte SPEAKER_PIN = 3;
const byte ANALOG_IN_PIN = 0;
const unsigned long MAX_BEEP_CYCLE = SECS(1);

Timer beeperTimer;

void beeperSetup() {
  beeperTimer.begin(STOP);
}

void beeperUpdate() {
  word analogData = analogRead(ANALOG_IN_PIN);
  unsigned long beepTime = map(analogData, 0, 1023, 0, MAX_BEEP_CYCLE);
  beeperTimer.time(beepTime);
  if (beeperTimer.available()) {
    beeperTimer.restart();
    tone(SPEAKER_PIN, 500, beepTime / 2);
  }
}

void setup() {
  beeperSetup();
}

void loop() {
  beeperUpdate();
}
