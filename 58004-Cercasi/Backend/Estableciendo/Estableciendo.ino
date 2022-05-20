void setup() {
  Serial.begin(9600); // Establece la velocidad para el Monitor Serie.
  Serial.println("SIM800L EVB");
  Serial3.begin(9600); // Establece la velocidad para el sim800l.
}

void loop() {
  if(Serial3.available()) // Si bytes disponibles para leer.
  {
    Serial.println(Serial3.readString()); // Lee desde el sim800l e imprime por el Monitor Serial.
  }

  if(Serial.available()) // Si bytes disponibles para leer.
  {
    Serial3.println(Serial.readString()); // Envia los comandos AT que lee desde el Monitor Serial al sim800l.
  }
}
