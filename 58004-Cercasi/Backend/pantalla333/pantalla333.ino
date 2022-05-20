#include <LiquidCrystal.h>
#include <String.h>
unsigned long previo, actual, a, duracion;
//Crear el objeto LCD con los números correspondientes (rs, en, d4, d5, d6, d7)
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
#include <Keypad.h>
 
const byte rowsCount = 4;
const byte columsCount = 4;
 
char keys[rowsCount][columsCount] = {
   { '1','2','3', 'A' },
   { '4','5','6', 'B' },
   { '7','8','9', 'C' },
   { '*','0','#', 'D' }
};
 
byte rowPins[rowsCount] = { 36, 34, 32, 30 };
byte columnPins[columsCount] = { 28, 26, 24, 22 };
 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);

void setup() {
  Serial.begin(9600);
  // Inicializar el LCD con el número de  columnas y filas del LCD
  lcd.begin(16, 2);
  // Escribimos el Mensaje en el LCD.
  standby();
}


 
void loop() {
   char key = keypad.getKey();
 
   if (key) {
      if (key == '*'){
        Serial.println("ATA");
        timmer();
        }
      else{
        if (key == '#'){
        Serial.println("ATH");}
        else{Serial.println(key);}}
      
   }
}

void standby(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Bienvenido");
  lcd.setCursor(0, 1);
  lcd.print("Telefono Arduino");
  }


void timmer()
  {
  boolean a = true;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Llamada:");
  previo = millis()/1000;
  Serial.print( "Pase" );
  while (a){
    char key = keypad.getKey();
    lcd.setCursor(0, 1);
    lcd.print(String(millis()/1000 - previo) + " Segundos");
    delay(100);
    if (key == '#'){
        Serial.println("ATH");
        a = false;
        duracion = millis()/1000 - previo;
        lcd.clear();
        lcd.print("Fin de Llamada");
        lcd.setCursor(0, 1);
        lcd.print("Duracion: " + String(duracion) + " s.");
        delay(4500);
        standby();
        }
  }
}
