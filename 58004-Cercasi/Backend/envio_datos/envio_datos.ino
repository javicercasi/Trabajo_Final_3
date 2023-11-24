#include <String.h>
unsigned long previo, actual, a;

void setup()
{
  // when using Serial 1 connect gsm pins to pin RX1 (pin 19) and TX1 (pin 18) of Arduino Mega
  // if you want to use RX2 and TX2 then you have to change all Serial1 in this code to Serial2
  //encendido();
  Serial1.begin(9600);               
  Serial.begin(9600);                
  Serial.println("Start!...");
  Serial1.println("AT");
  delay(1000);
  ShowSerialData();
  
  //Configuracion();
  //envio_trama();
  delay(10000);
  Serial.println("Llamando a la funcion Timmer");
  timmer();
  
  //Serial.println(filtrado("2616227739"));
  //ShowSerialData();
 
}
 
void loop()
{

ShowSerialData();

} 
void ShowSerialData(){
  
  while (Serial1.available()) // if serial 1, which is Gsm, is sending information,
    Serial.write(Serial1.read()); // then write those information to serial monitor
  if (Serial.available()) // if something is sent using serial monitor
    Serial1.write(Serial.read());  // then write it to Serial 1 which is GSM
 
}

void comando(String at, int unsigned tiempo){
  Serial1.println(at);  //Identificador de llamda activado
  delay(tiempo);
  ShowSerialData();
}

void encendido(){
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  delay(5000);
  }


void timmer()
  {
 
  previo = millis()/1000;
  delay(6000);
  Serial.print( "Pase" );
  while (a= millis()/1000 < 20){
    Serial.print(a);
  }
  
  actual = millis()/1000;
 
  Serial.print( "La función tardó:" );
  Serial.print( actual - previo );
  Serial.println( " s" );
 
  delay(200);
}




void Configuracion(){
  
  comando("AT+CLIP=1", 500);    //Identificador de llamda activado
  comando("AT+CMIC=0,7", 500);  //Ganancia microfono 0-15
  comando("AT+CALS=4", 500);    //Tono seleccionado 0-19
  comando("AT+CLVL=80", 500);   //Volumen parlante 0-100
  comando("AT+CRSL=1", 500);    //Volumen Llamada 0-4
  
  //Serial1.println("AT+CLIP=1");  //Identificador de llamda activado
  //delay(500);
  //ShowSerialData();
  //Serial1.println("AT+CMIC=0,7");   //Ganancia microfono (0,1,2)-15
  //delay(500);
  //Serial1.println("AT+CALS=4");   //Tono seleccionado
  //delay(1000);
  //Serial1.println("AT+CLVL=80");  //Volumen parlante 0-100
  //delay(500);
  //Serial1.println("AT+CRSL=1");   //Volumen Llamada 0-4
  
  }

String filtrado(String num){

  String field = "";
  switch (num.toInt()) {
  case (2616227734):
    field = "field1";
    break;
  case (2616227736):
    field = "field2";
    break;
  default:
   field = "field3";}
   return field;
}

void envio_trama(){
  //field = filtrado(2616227734);
  comando("AT+CIPSTATUS", 2000);
  comando("AT+CIPMUX=0", 2000);
  comando("AT+CSTT=\"datos.personal.com\",\"datos\",\"datos\"", 1000);
  comando("AT+CIICR", 3000);
  comando("AT+CIFSR", 2000);
  comando("AT+CIPSPRT=0", 3000);
  comando("AT+CIPSTART=\"TCP\",\"184.106.153.149\",\"80\"", 6000);
  comando("AT+CIPSEND", 4000);
  String datos="GET https://184.106.153.149/update?api_key=IDQE7V5M1W6EAUY6&";
  comando(datos, 4000);
  Serial1.println((char)26);
  delay(5000);
  comando("",500);
  comando("AT+CIPSHUT",4000);
  }
