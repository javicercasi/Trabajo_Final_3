 void setup(){
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial.println("Start!...");
  Serial1.println("AT");
  //delay(1000);
  //Serial1.println("ATD2616227734;");
  //delay(10000);
  //Serial1.println("ATH");

  
  
 }

  void loop(){  
   //delay(2000);
   //Serial1.println("ATD2616227734"); 
   if (Serial1.available())
     Serial.write(Serial1.read());    
    if(Serial.available()) 
    Serial1.write(Serial.read());
  }
