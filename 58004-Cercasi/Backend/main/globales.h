#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Separador.h> 
#include <String.h>


LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

int i=0, j=0;
Separador s;
unsigned long previo, actual, a, duracion;
unsigned long tiempo;
const byte rowsCount = 4;
const byte columsCount = 4;
String apikey = "";

byte rowPins[rowsCount] = { 36, 34, 32, 30 };
byte columnPins[columsCount] = { 28, 26, 24, 22 };

char keys[rowsCount][columsCount] = {
   { '1','2','3', '+' },
   { '4','5','6', 'B' },
   { '7','8','9', 'C' },
   { '*','0','#', 'D' }
};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);
