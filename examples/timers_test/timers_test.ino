// Ilość elementow timera
// musi byc podane przed include
#define TIMER_ITEMS 2

#include <Timers.h>
#include <Servo.h>

#define SERVO_PIN 2
#define LED_PIN 13

Servo servo;

Timers timer; // ** Deklaracja obiektu timera z 2 slotami

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
  timer.attach(0, 20, servoMove);
  
  // Podłączenie funkcji wywoływanej co 0,5 s
  timer.attach(1, 500, ledChange);
}

void loop()
{
  // Aktualizacja stanu timera
  timer.process();
}
