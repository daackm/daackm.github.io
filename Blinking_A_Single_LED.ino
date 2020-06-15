void setup()
   {
    Serial.begin(9600);
   }

void loop()
   {
    kounter=kounter+1;
    digitalWrite(2,HIGH);
    delay(1000);
    digitalWrite(2,LOW);
    delay(1000);
   }
