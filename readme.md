# Timers - program Arduino sterowany czasem

Wersja: 16.4.1

Autor: Łukasz Tretyn, [Nettigo.pl](http://nettigo.pl)

Biblioteka umożliwia:

- Budowanie programów robiących wiele rzeczy na raz
- Uruchamiane różnych części programu o różnym czasie
- Timeout - określanie czasu na wykonanie zadania
- Timestamp - sterowanie algorytmem przez upływający czas
- Miałczenie jak kot

Biblioteka nie blokuje programu, tak jak funkcje `delay()` i `delayMicrosoconds()`.  

## Instalacja biblioteki

Bibliotekę należy pobrać i umieścić w katalogu libraries, który znajduje się w folderze ze szicami Arduino.

[Strona projektu biblioteki Timers na Github](https://github.com/nettigo/Timers)

## Referencja biblioteki

### Dodawanie biblioteki do programu

```Arduino
#include <Timers.h>
```

Tę linię należy dodać na początku programu by skorzystać z bilioteki Timers.

### Klasa i tworzenie obiektu

```Arduino
Timer timer;
```

Główna klasa biblioteki nazwya się `Timer`.
W przykładzie utworzyłem z niej obiekt o nazwie `timer`.
Jeśli potrzebujesz więcej timerów, możesz stworzyć kilka obiektów o różnych nazwach albo ich tablicę.

### Metody

#### begin

```Arduino
timer.begin(300);
```

`begin` rozpoczyna odliczanie timera od nowa, z nowym czasem do odliczenia.

Argument przyjmuje wartości w milisekundach.

W przykładzie obiekt `timer` będzie odliczał czas 300 milisekund od chwili wywołania metody `begin`.

#### available

```Arduino
bool isTimeEnd = timer.available();
```

`available` zwraca wartość `true` jeśli upłynął już czas, lub `false` jeśli nie upłynął.

Wartość jest typu `bool`.

W przykładzie metoda `available` obiektu `timer` zapisuje czy upłynął już czas, do zmiennej `isTimeEnd`.

#### restart

```Arduino
timer.restart();
```

`restart` rozpoczyna odliczanie czasu od nowa.

#### time

```Arduino
timer.time(600);
```

`time` ustawia nowy czas do odliczania, bez rozpoczynania odliczania od nowa.

Ardument przyjmuje wartości w milisekundach.

W przykładzie czas do odliczenia został zmieniony na 600 milisekund.

#### time

```Arduino
unsigned long timeToEnd = timer.time();
```

`time` (bez argumentów) podaje ile jeszcze zostało czasu do końca odliczania.

Czas jest zwracany w milisekundach.

W przykładzie pozostały czas pracy `timer` został zapisany w zmiennej `timeToEnd`.

### Elementy pomocnicze

#### SECS

```Arduino
unsigned long timeoutTime = SECS(40);
```

`SECS` zamienia czas w sekundach na milisekundy.

#### MINS

```Arduino
unsigned long timeoutTime = MINS(20);
```

`MINS` zamienia czas w minutach na milisekundy.

#### HOURS

```Arduino
unsigned long timeoutTime = HOURS(2);
```

`HOURS` zamienia czas w godzinach na milisekundy.

#### STOP

```Arduino
timer.time(STOP);
```

`STOP` zatrzymuje działanie timera.

## Przykład:

Nieodzowny przykład migania diodą:

```Arduino
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
```

Program miga wbudowaną w arduino diodą świecącą "L".

- Na początku za pomocą `include` ładowana jest biblioteka Timers
- Potem tworzony jest obiekt `ledBlinkTimer`
- W funkcji `setup` ustawiane jest odliczanie 2 sekund za pomocą `begin` i `SECS`
- W funkcji `loop` warunek `if` sprawdza czy upłynął już czas. Obwieści to metoda `available`
- Gdy warunek się spełni dioda zmieni swój stan na przeciwny, a timer zostanie zresetowany za pomocą metody `restart`, żeby odliczał czas od nowa.
