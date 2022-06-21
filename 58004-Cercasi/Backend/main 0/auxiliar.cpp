
#include "Arduino.h"
#include "globales.h"


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
  //comando("AT+CPBF", 4000); 
  //comando("AT+CMIC=0,7", 500);  //Ganancia microfono 0-15
  //comando("AT+CALS=4", 500);    //Tono seleccionado 0-19
  //comando("AT+CLVL=80", 500);   //Volumen parlante 0-100
  //comando("AT+CRSL=1", 500);    //Volumen Llamada 0-4
}


void standby(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Bienvenido");
  lcd.setCursor(0, 1);
  lcd.print("Telefono Arduino");
  }


void inicio (){
  
  Serial1.begin(9600);               
  Serial.begin(9600);                
  Serial.println("Start!...");
  lcd.begin(16, 2);
  comando("AT", 2000);
  Configuracion();
  delay(2000);
  standby();
  }



void (* reset) (void) = 0;


void encendido(){
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  delay(5000);
  }


  void envio_trama(String posicion, String duracion){

   Serial.println("La posicion es: "+ String(posicion.toInt()));

  if (posicion.toInt() > 7){
    posicion = "8";}

  comando("AT+CIPSTATUS", 2000);
  comando("AT+CIPMUX=0", 2000);
  comando("AT+CSTT=\"datos.personal.com\",\"datos\",\"datos\"", 1000);
  comando("AT+CIICR", 3000);
  comando("AT+CIFSR", 2000);
  comando("AT+CIPSPRT=0", 3000);
  comando("AT+CIPSTART=\"TCP\",\"184.106.153.149\",\"80\"", 6000);
  comando("AT+CIPSEND", 4000);
  String datos="GET https://184.106.153.149/update?api_key=96MTTXG33GMWMI2Q&field"+ posicion + "="+ duracion;
  comando(datos, 4000);
  Serial1.println((char)26);
  delay(5000);
  comando("",500);
  comando("AT+CIPSHUT",4000);
  }


void timmer(String posicion)
  {

  #define DEBUG(a) Serial.println(a);
  String data = "";
  boolean b = true, c = true;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Llamada:");
  previo = millis()/1000;
  Serial.print( "Pase" );
  while (b){

    char key = keypad.getKey();
    lcd.setCursor(0, 1);
    lcd.print(String(millis()/1000 - previo) + " Segundos");
    delay(100);
    
    if (key == '#' || c == false){
        Serial1.println("ATH");
        b = false;
        duracion = millis()/1000 - previo;
        lcd.clear();
        lcd.print("Fin de Llamada");
        lcd.setCursor(0, 1);
        lcd.print("Duracion: " + String(duracion) + " s.");
        delay(4500);
        standby();
        //envio_trama(posicion, String(duracion));
        }
  }
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
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("   Llamando a:  ");
   lcd.setCursor(0, 1);
   lcd.print(" "+numero+"   ");
   Serial.println("LLamando a "+numero);
   comando("ATD"+numero+";", 500);
   delay(6000);
   timmer(posicion);
}

  void mensaje(String num, String posicion){

      #define DEBUG(a) Serial.println(a);
      String data = "", texto = "";
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
  
      switch (num.toInt()) {
      case (1):
        texto = "Hola";
        break;
      case (2):
        texto = "Estoy bien";
        break;
      case (3):
        texto = "Llamame";
        break;
      case (4):
        texto = "Ven a Verme";
        break;
      default:
       texto = "Hola";
       break;}

      String comandoat = "AT+CMGS=\"" + numero + "\"\r\n";
      comando(comandoat, 1000);
      Serial.println(comandoat);
      comando(texto,1000);
      Serial1.println((char)26); 
      delay(1000);
      lcd.clear();
      lcd.print("Mensaje Enviado:");
      lcd.setCursor(0, 1);
      lcd.print(texto);
      Serial.println("Mensaje enviado");
      delay(3000);
      standby();

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
    
    if (key == 'B'){
        lcd.clear();
        lcd.print("Modulo Encendido");
        delay(3000);
        Serial.println("Encendido de Modulo");
        encendido();
        standby();}
    
    if (key == '#'){
        lcd.clear();
        lcd.print("Reset de Modulo");
        delay(3000);
        Serial.println("Reseteado del Modulo");
        reset();
        standby();}

    if (key == '#'){
        Serial.println("Fin llamada");}

     if (key == 'D'){
              lcd.clear();
              lcd.print("  Modo Registro: ");
              delay(4000);
              lcd.setCursor(0, 0);
              lcd.print("Ingrese numero: ");
              lcd.setCursor(0, 1);
              Serial.println("Modo Registro");
              String num = "", posicion = "";
              Serial.println("Ingrese el numero de Telefono: ");

              for(int i = 1; i<3; i++){
              if (i == 2){Serial.println();
                          lcd.clear();
                          lcd.print("Ingrese Posicion");
                          lcd.setCursor(0, 1);
                          lcd.print("a Guardar: ");
                          Serial.println("Ingrese la posicion a guardarse: ");}
              char tecla = keypad.getKey();
              while (tecla != 'D'){
                tecla = keypad.getKey();
                if ((tecla != NO_KEY) && (tecla != '#') && (tecla != '*') && (tecla != 'A') && (tecla != 'B') && (tecla != 'C') && (tecla != 'D')) {
                  if (i == 1){num.concat(tecla);}
                  if (i == 2){posicion.concat(tecla);}
                  Serial.write(tecla);
                  lcd.print(tecla);
                  }   
                }}
 
            String comandoat =  "\tAT+CPBW="+String(posicion)+",\""+String(num)+"\",129,\""+posicion+"\"";
            //Serial1.println(comando);
            lcd.clear();
            comando(comandoat, 1000);
            Serial.println("Comando:  "+comandoat);
            lcd.print("Numero Guardado");
            delay(3000);
            standby();
        }
            if (key == 'C'){
              lcd.clear();
              lcd.print("  Modo Llamada  ");
              delay(4000);
              lcd.setCursor(0, 0);
              lcd.print("Ingrese Contacto");
              lcd.setCursor(0, 1);
              lcd.print("a Llamar: ");
              Serial.println("Modo Llamada");
              Serial.println("Ingrese la posicion a Leerse: ");
              String num = "";
              boolean a = true;
              char tecla = keypad.getKey();
              while (tecla != '*'){
                tecla = keypad.getKey();
                if ((tecla != NO_KEY) && (tecla != '#') && (tecla != '*') && (tecla != 'A') && (tecla != 'B') && (tecla != 'C') && (tecla != 'D')) {
                  num.concat(tecla);
                  Serial.println();
                  Serial.write(tecla);
                  lcd.print(tecla);
;
                  }}
              int b = num.length();
              Serial.println("Numero: "+ num +"    Extension teclas: "+ String(b));
              if (b > 0){
              Serial.println();
              
              Serial.println("LLamando funcion");
              llamado(num);}
            }


        if (key == '+'){
            lcd.clear();
            lcd.print("  Modo Mensaje: ");
            delay(4000);
            lcd.setCursor(0, 0);
            lcd.print("Ingrese Mensaje");
            lcd.setCursor(0, 1);
            lcd.print("preguardado: ");
            Serial.println("Modo Mensaje");
            String num = "", posicion = "";
            Serial.println("Ingrese el mensaje preguardado: ");

            for(int i = 1; i<3; i++){
            if (i == 2){Serial.println();
                        lcd.clear();
                        lcd.print("Ingrese Contacto");
                        lcd.setCursor(0, 1);
                        lcd.print("a Enviar: ");
                        Serial.println("Ingrese la posicion a guardarse: ");}
            char tecla = keypad.getKey();
            while (tecla != '+'){
              tecla = keypad.getKey();
              if ((tecla != NO_KEY) && (tecla != '#') && (tecla != '*') && (tecla != '+') && (tecla != 'B') && (tecla != 'C') && (tecla != 'D')) {
                if (i == 1){num.concat(tecla);}
                if (i == 2){posicion.concat(tecla);}
                Serial.write(tecla);
                lcd.print(tecla);
                }   
              }}
            mensaje(num, posicion);
      }
      } 
  }

void oyente(){

  #define DEBUG(a) Serial.println(a);
  String data = "";
  int posicion = 8;
  Serial1.println("AT+CPAS");
  delay(1300);
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
   String numero4 = s.separa(data, '"', 5);
   //Serial.println("numero entero: "+numero+ " Contacto que llama: "+ numero4 + "  O tambien: " + String(posicion) + " Tamaño es: "+ numero4.length());
   //delay(100);

   if (numero4.length() > 0){
      posicion = numero4.toInt();
      if (posicion > 7){
        posicion = 8;}
        Serial.println("Contacto que llama: "+ numero4 + "  O tambien: " + String(posicion) + " Tamaño es: "+ numero4.length());}
    
   if (numero2.length() == 0){
      i = 0;
      j = 0;
      numero2 = "";}
      
   if (numero2.length() == 13 && i == 0 && numero.length() > 22){
      char tecla = keypad.getKey();
      i++;   
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Llamada Entrante:");
      lcd.setCursor(0, 1);
      lcd.print(numero2);
      
      while (tecla != '*' && tecla != '#'){
                tecla = keypad.getKey();
                if (tecla == '*') {
                  Serial1.println("ATA");
                  timmer(String(posicion));
                                  }
                  
                 if (tecla == '#') {
                  Serial1.println("ATH");
                  lcd.clear();
                  lcd.setCursor(0, 0);
                  lcd.print("    Llamada    ");
                  lcd.setCursor(0, 1);
                  lcd.print("   Rechazada   ");
                  delay(4500);
                  standby();
    }}
      }
                          
  }




  
