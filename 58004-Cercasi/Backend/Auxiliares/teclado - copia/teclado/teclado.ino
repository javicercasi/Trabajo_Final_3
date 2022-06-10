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
   Serial.begin(115200);
}
 
void loop() {
   char key = keypad.getKey();
 
   if (key) {
      if (key == '*'){
        Serial.println("ATA");}
      else{
        if (key == '#'){
        Serial.println("ATH");}
        else{Serial.println(key);}}
      
   }
}
