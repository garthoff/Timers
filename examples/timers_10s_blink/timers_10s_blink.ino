// ** Program mrugający diodą podłączoną do pinu 13 przez 10 sekund **

// Ładowanie biblioteki Timers
#include <Timers.h>

// Zmienna przechowująca numer timera mrugającego diodą
byte blinker;

void setup()
{
  pinMode(13, OUTPUT);

  // Wywoływanie funkcji "toggle" co 500 ms
  blinker = Timers.every(500, toggle);

  // Wywołanie funkcji "blinkOff" za 10 s
  Timers.after(10000, blinkOff);
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

// Funkcja wyłączająca mruganie
void blinkOff()
{
  // Usunięcie timera o numerze przechowywanym w zmiennej "blinker"
  Timers.clear(blinker);
}

