// Płynnie zapala i gasi diodę świecącą podłączoną do pinu PWM 3
// Autor: Łukasz Tretyn - http://nettigo.pl

#include <Timers.h>

const byte PWM_LED = 3;
const unsigned long FADE_IN_TIME = SECS(2.25);
const unsigned long FADE_OUT_TIME = SECS(1.8);
const unsigned long CYCLE_DELAY_TIME = SECS(0.75);

Timer timer;

enum class BlinkState : byte {
  DELAY,
  FADE_IN,
  FADE_OUT
} state;

void blinkSetup() {
  pinMode(PWM_LED, OUTPUT);
  timer.begin(CYCLE_DELAY_TIME);
}

void blinkUpdate() {
  byte brightness;
  
  switch (state) {
    case BlinkState::DELAY:
    if (timer.available()) {
      state = BlinkState::FADE_IN;
      timer.begin(FADE_IN_TIME);
    }
    break;

    case BlinkState::FADE_IN:
    if (timer.available()) {
      state = BlinkState::FADE_OUT;
      timer.begin(FADE_OUT_TIME);
    }
    brightness = map(timer.time(), FADE_IN_TIME, 0, 0, 255);
    break;

    case BlinkState::FADE_OUT:
    if (timer.available()) {
      state = BlinkState::DELAY;
      timer.begin(CYCLE_DELAY_TIME);
    }
    brightness = map(timer.time(), FADE_OUT_TIME, 0, 255, 0);
    break;
  }

  analogWrite(PWM_LED, brightness);
}

void setup() {
  blinkSetup();
}

void loop() {
  blinkUpdate();
}

