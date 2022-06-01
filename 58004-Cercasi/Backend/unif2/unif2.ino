#include <Keypad.h>
#include <Separador.h> 
#include <String.h>
int i=0, j=0;
Separador s;
unsigned long previo, actual, a;
unsigned long tiempo;
const byte rowsCount = 4;
const byte columsCount = 4;
String apikey = "";

unsigned long tiempo_previo = 0, transcurrido = 0;
const long intervalo = 3000;

char keys[rowsCount][columsCount] = {
   { '1','2','3', 'A' },
   { '4','5','6', 'B' },
   { '7','8','9', 'C' },
   { '*','0','#', 'D' }
};

byte rowPins[rowsCount] = { 36, 34, 32, 30 };
byte columnPins[columsCount] = { 28, 26, 24, 22 };
 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);

 void setup(){
  Serial1.begin(9600);               
  Serial.begin(9600);                
  Serial.println("Start!...");
  comando("AT", 2000);
  Configuracion();
  delay(2000);
 }

void ShowSerialData(){
  
  while (Serial1.available()){ // if serial 1, which is Gsm, is sending information,
    Serial.write(Serial1.read());} // then write those information to serial monitor
  if (Serial.available()){ // if something is sent using serial monitor
    Serial1.write(Serial.read());}  // then write it to Serial 1 which is GSM
 
}
void comando(String at, int unsigned tiempo){
  Serial1.println(at);  //Identificador de llamda activado
  delay(tiempo);
  ShowSerialData();
}
void Configuracion(){
  
  comando("AT+CLIP=1", 500);    //Identificador de llamda activado
  comando("AT+IFC=1,1", 500);   //Retorno de datos por Soft
  //comando("AT+CMIC=0,7", 500);  //Ganancia microfono 0-15
  //comando("AT+CALS=4", 500);    //Tono seleccionado 0-19
  //comando("AT+CLVL=80", 500);   //Volumen parlante 0-100
  //comando("AT+CRSL=1", 500);    //Volumen Llamada 0-4
}


void encendido(){
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  delay(5000);
  }

void llamado(String posicion){
  #define DEBUG(a) Serial.println(a);
  String data = "";
  Serial1.println("AT+CPBR="+posicion);
  delay(2000);
      while (Serial1.available())
   {
      char character = Serial1.read();
      if (character != '\n')
      {
         data.concat(character);
      }
   }
   String numero = s.separa(data, '"', 1);
   Serial.println("LLamando a "+numero);

   comando("ATD"+numero+";", 500);
}


void oyente(){

  #define DEBUG(a) Serial.println(a);
  String data = "";
  Serial1.println("AT+CPAS");
  delay(1300);
  //Serial.println("Entreeeeee");
    while (Serial1.available())
   {
      char character = Serial1.read();
      if (character != '\n')
      {
         data.concat(character);
      }
   }

  teclado();

   String numero = s.separa(data, ':', 1);
   byte prevPos = numero.indexOf('O');                       // Buscar la posición de la primera coma en la cadena
   String first = numero.substring(0, prevPos);
   String numero2 = s.separa(data, '"', 1);
   //Serial.println("Estado: "+first+" i="+i+" j="+j+" Numero: "+numero2+" leng: "+(String(numero2)).length());
   
   if (numero2.length() == 0){
      i = 0;
      j = 0;
      numero2 = "";}
      
   if (numero2.length() == 13 && i == 0){
      char tecla = keypad.getKey();
      i++;    //Aca debo detectar el ata
      Serial.println("Llamada de: "+numero2);
      while (tecla != '*' && tecla != '#'){
                tecla = keypad.getKey();
                if (tecla == '*') {
                  Serial1.println("ATA");}
                  
                 if (tecla == '#') {
                  Serial1.println("ATH");}}
      }

   if (i == 1){
    i = 0;
    char tecla = keypad.getKey();
    Serial.println("Llamada en curso");
    while (tecla != '#'){
                tecla = keypad.getKey();
                if (tecla == '#') {
                  Serial1.println("ATH");}}}
                          
  }


//AT+CPAS, SI ES 3, ESTA SONANDO
//AT+CMGD=1,4 eLIMINAR MENSAJES
//AT+CPBS? VER PORCENTAJE DE AGENDA OCUPADA
//AT+CPBF VER TODOS LOS CONTACTOS

   void loop(){
    teclado();
    transcurrido = millis();

    if (transcurrido - tiempo_previo >= intervalo) {
        tiempo_previo = transcurrido;
        oyente();}
        
              }

void teclado(){

    char key = keypad.getKey();
    
    if (key) {

    if (key == '0'){
              Serial.println("Nube:");
              Serial.println("Ingrese al apikey Vista en el Servidor");
              //String apikey = "";
              boolean a = true;
              char tecla = keypad.getKey();
              while (tecla != '#'){
                tecla = keypad.getKey();
                if ((tecla != NO_KEY) && (tecla != '#') && (tecla != '*')) {
                  apikey.concat(tecla);
                  Serial.println();
                  Serial.write(tecla);
                  }}
              int b = apikey.length();
              Serial.println("Numero: "+ apikey +"    Extension teclas: "+ String(b));
              if (b > 0){
              Serial.println();
              Serial.println("Su apikey es: "+apikey);}
      }
    
    if (key == '*'){
        Serial.println("Encendido de Modulo");
        encendido();}

    if (key == '#'){
        Serial.println("Fin llamada");}

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
                if ((tecla != NO_KEY) && (tecla != '#') && (tecla != '*') && (tecla != 'A') && (tecla != 'B') && (tecla != 'C') && (tecla != 'D')) {
                  if (i == 1){num.concat(tecla);}
                  if (i == 2){posicion.concat(tecla);}
                  Serial.write(tecla);
                  //lcd.print(keyPressed);
                  }   
                }}
 
            String comando =  "\tAT+CPBW="+String(posicion)+",\""+String(num)+"\",129,\"Contacto\"";
            //Serial1.println(comando);
            Serial.println("Comando:  "+comando);
        }
            if (key == 'D'){
              Serial.println("Modo Llamada");
              Serial.println("Ingrese la posicion a Leerse: ");
              String num = "";
              boolean a = true;
              char tecla = keypad.getKey();
              while (tecla != '#'){
                tecla = keypad.getKey();
                if ((tecla != NO_KEY) && (tecla != '#') && (tecla != '*') && (tecla != 'A') && (tecla != 'B') && (tecla != 'C') && (tecla != 'D')) {
                  num.concat(tecla);
                  Serial.println();
                  Serial.write(tecla);
                  }}
              int b = num.length();
              Serial.println("Numero: "+ num +"    Extension teclas: "+ String(b));
              if (b > 0){
              Serial.println();
              
              Serial.println("LLamando funcion");
              llamado(num);}
            }
        
        } 
  }
