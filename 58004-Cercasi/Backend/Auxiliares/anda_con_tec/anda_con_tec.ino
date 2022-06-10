 #include <Keypad.h>
 #include <Separador.h> 
 Separador s;
 
const byte rowsCount = 4;
const byte columsCount = 4;
 
char keys[rowsCount][columsCount] = {
   { '1','2','3', 'A' },
   { '4','5','6', 'B' },
   { '7','8','9', 'C' },
   { '*','0','#', 'D' }
};

byte rowPins[rowsCount] = { 22, 24, 26, 28 };
byte columnPins[columsCount] = { 30, 32, 34, 36 };
 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);

 void setup(){
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial.println("Start!...");
  Serial1.println("AT");

 }

  void loop(){  

    if (Serial1.available())
     Serial.write(Serial1.read());    
    if(Serial.available()) 
    Serial1.write(Serial.read());
   char key = keypad.getKey();
 
   if (key) {
      if (key == 'A'){
        Serial1.println("ATA");}
      if (key == 'B'){
        Serial1.println("ATH");}
      if (key == 'C'){
              Serial.println("Modo Registro");
              String num = "", posicion = "";
              Serial.println("Ingrese el numero de Telefono: ");

              
              for(int i = 1; i<3; i++){
              if (i == 2){Serial.println();
                          Serial.println("Ingrese la posicion a guardarse: ");}
              char tecla = keypad.getKey();
              while (tecla != '#'){
                tecla = keypad.getKey();
                if ((tecla != NO_KEY) && (tecla != '#')) {
                  if (i == 1){num.concat(tecla);}
                  if (i == 2){posicion.concat(tecla);}
                  Serial.write(tecla);
                  //lcd.print(keyPressed);
                  }   
                }}
 
            String comando =  "\tAT+CPBW="+String(posicion)+",\""+String(num)+"\",129,\"Javi\"";
            Serial1.println(comando);
        }
            if (key == 'D'){
              Serial.println("Modo Llamada");
              Serial.println("Ingrese la posicion a Leerse: ");
              String num = "";
              char tecla = keypad.getKey();
              while (tecla != '#'){
                tecla = keypad.getKey();
                if ((tecla != NO_KEY) && (tecla != '#')) {
                  num.concat(tecla);
                  Serial.write(tecla);
                  Serial.println();
                  //lcd.print(keyPressed);
                  }   
                }
              Serial.println("LLamando a Numero "+num);
              Serial1.println("ATD>"+num+";");
            }
        
        }}
