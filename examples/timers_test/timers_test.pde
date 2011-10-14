#include <Timers.h>
#include <Servo.h>

#define SERVO_PIN 2
#define LED_PIN 13

Servo servo;
LimitedTimerPool timer; // Deklaracja obiektu timera z 2 slotami

// * Obróć serwo o 1 stopień
void servoMove()
{
  static byte angle = 0;
  servo.write(angle);
  angle++;
}

// * Zmień stan diody na przeciwny
void ledChange()
{
  static byte ledState = LOW;
  digitalWrite(LED_PIN, ledState);
  ledState = ~ledState;
}

void setup()
{
  servo.attach(SERVO_PIN);
  pinMode(LED_PIN, OUTPUT);
  // Podłączenie funkcji wywoływanej co 0,02 s
  timer.connect(0, 20, servoMove);
  // Podłączenie funkcji wywoływanej co 0,5 s
  timer.connect(1, 500, ledChange);
}

void loop()
{
  // Aktualizacja stanu timera
  timer.update();
}
