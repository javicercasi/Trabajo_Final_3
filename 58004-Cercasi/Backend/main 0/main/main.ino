
#include "auxiliar.h"
unsigned long tiempo_previo = 0, transcurrido = 0;
const long intervalo = 3000;
 

 void setup(){
  inicio();
 }


  void loop(){
  teclado();
  transcurrido = millis();
  
  if (transcurrido - tiempo_previo >= intervalo) 
      { 
      tiempo_previo = transcurrido;
      oyente();                                   
      }
  }
