# Timers - program sterowany czasem

Timers jest to biblioteka dla Arduino do wywoływania funkcji programu wokreślonym czasie.


### Przykład 1: Program mrugający diodą podłączoną do pinu 13

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


### Przykład 2: Program mrugający diodą podłączoną do pinu 13 przez 10 sekund

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



### Referencje

`Timers.every(czas, nazwa_funkcji);` - ustawia wywoływanie fukcji cykliczne co określony czas.

- czas - czas co jaki będzie wywoływana funkcja w milisekundach.
- nazwa_funkcji - nazwa funkcji, ktora ma być cyklicznie wywoływana

Funkcja zwraca unikatowy numer identyfikacyjny potrzebny do zarządzania czasem dla tej funkcji przez metody `Timers.clear`, `Timers.reset` i `Timers.update`.
Jeśli zwrócowa wartość wynosi 0 to zadanie się nie powiodło (zabrakło pamięci RAM, albo przekroczyło 255 dodanych funkji)


`Timers.after(czas, nazwa_funkcji);` - wywołuje funkcje raz po ustalonym w argumencie czasie.

- czas - czas po jakim zostanie wywołana funkcja w milisekundach.
- nazwa_funkcji - nazwa funkcji, która ma być wywołana po czasie

Funkcja zwraca unikatory numer identyfikacyjny potrzebny do zarządzania czasem dla tej funkcji przez metody `Timers.clear`, `Timers.reset` i `Timers.update`.
Jeśli zwrócowa wartość wynosi 0 to zadanie się nie powiodło (zabrakło pamięci RAM, albo przekroczyło 255 dodanych funkji)


`Timers.clear(id);` - wyłącza wywoływanie funkcji rozpoczęte przez `Timers.every` i `Timers.after`.

- id - numer identyfikkacyjny wywoływanej funkcji zwracany przez `Timers.every` i `Timers.after`.

Funkcja zwraca wartość typu `bool`. Zwraca `true` jeśli operacja się powiodła. Wartość `false` zwraca jeśli nie ma timera o takim numerze `id`.


`Timers.reset(id, czas);` - funkcja zmienia czas wywoływania funkcji. Czas jest ofliczany od chwili jego przestawienia.

- id - numer identyfikkacyjny wywoływanej funkcji zwracany przez `Timers.every` i `Timers.after`.
- czas - czas po jakim zostanie wywołana funkcja w milisekundach.

Funkcja zwraca wartość typu `bool`. Zwraca `true` jeśli operacja się powiodła. Wartość `false` zwraca jeśli nie ma timera o takim numerze `id`.


`Timers.update(id, czas);` - funkcja zmienia czas wywoływania funkcji. Czas jest odliczany od ostatniego wywołania funkcji lub jej zarejestrowania przez `Timers.every` i `Timers.after`.

- id - numer identyfikkacyjny wywoływanej funkcji zwracany przez `Timers.every` i `Timers.after`.
- czas - czas po jakim zostanie wywołana funkcja w milisekundach.

Funkcja zwraca wartość typu `bool`. Zwraca `true` jeśli operacja się powiodła. Wartość `false` zwraca jeśli nie ma timera o takim numerze `id`.


`Timers.length();` - odczytuje ile jest zarejestrowanych funkcji w timerze.

Funkcja zwraca wartośc typu byte z ilością zarejestrowanych funkcji do wywołania.


`Timers.process();` - funkcja zajmuje się obliczaniem czasu potrzebnego do wywołania zarejestrowanych funkcji. Powina być wywoływana możliwie często, najlepiej w funkcji `loop`.

