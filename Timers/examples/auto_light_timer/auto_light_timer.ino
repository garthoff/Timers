// Automatyczny wyłącznik światła
// 5 niezależnych kanałów
// Świeci przez 1 minutę od wciśniecia przycisku
// Wejścia z rezystorem podciągającym dla przycisków/czujników podczerwieni
// na pinach cyfrowych 2, 3, 4, 5, 6
// Cyfrowe wyjścia dla tranzystorów MOSFET/Przekaźników
// na pinach cyfrowych 7, 8, 9, 10, 11
// Autor: Łukasz Tretyn - http://nettigo.pl

#include <Timers.h>

// Config
const byte LIGHTS_NUM = 5;
const byte switchPins[LIGHTS_NUM] = {2, 3, 4, 5, 6};
const byte lightPins[LIGHTS_NUM] = {7, 8, 9, 10, 11};
const unsigned long LIGHTS_ON_TIME = MINS(1);
const byte LIGHT_ON_STATE = HIGH;
const byte SWITCH_ON_STATE = LOW;

Timer lightTimers[LIGHTS_NUM];

void lightSetup() {
  for (byte i=0; i<LIGHTS_NUM; i++) {
    lightTimers[i].begin(STOP);
    pinMode(switchPins[i], INPUT_PULLUP);
    pinMode(lightPins[i], OUTPUT);
  }
}

void lightUpdate() {
  for (byte i=0; i<LIGHTS_NUM; i++) {
    byte pinState = digitalRead(switchPins[i]);
    if (pinState == SWITCH_ON_STATE) {
      lightTimers[i].begin(LIGHTS_ON_TIME);
      digitalWrite(lightPins[i], LIGHT_ON_STATE);
    }

    if (lightTimers[i].available()) {
      lightTimers[i].time(STOP);
      digitalWrite(lightPins[i], !LIGHT_ON_STATE);
    }
  }
}

void setup() {
  lightSetup();
}

void loop() {
  lightUpdate();
}
