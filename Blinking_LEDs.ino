#include "SoftwareSerial.h"
int kounter=0;  //Ignore the rest of this line

void setup()
   {
    Serial.begin(9600);
    pinMode(2,OUTPUT);
    pinMode(7,OUTPUT);
    pinMode(8,OUTPUT);
   }

void loop()
   {
    kounter=kounter+1;
    digitalWrite(7,HIGH);
    digitalWrite(8,LOW);
    delay(1000);
   
    digitalWrite(7,LOW);
    digitalWrite(8,HIGH);
    delay(1000);
   }
