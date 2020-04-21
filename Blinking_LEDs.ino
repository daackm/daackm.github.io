#include "SoftwareSerial.h"
int kounter=0;  //Ignore the rest of this line

void setup()
   {
    Serial.begin(9600);
   }

void loop()
   {
    kounter=kounter+1;
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
    delay(1000);
    digitalWrite(2,LOW);
    digitalWrite(3,HIGH);
    delay(1000);
   }
