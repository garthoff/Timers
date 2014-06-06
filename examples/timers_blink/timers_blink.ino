// ** Program mrugający diodą podłączoną do pinu 13 **

// Ładowanie biblioteki Timers
#include <Timers.h>

void setup()
{
  pinMode(13, OUTPUT);
  // Wywoływanie funkcji "toggle" co 500 ms
  Timers.every(500, toggle);
}

void loop()
{
  // Obliczanie czasu
  Timers.process();
}

// Funkcja mrugająca diodą
void toggle()
{
  digitalWrite(13, !digitalRead(13));
}
