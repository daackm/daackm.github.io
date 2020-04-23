// Grade Crossing Signal using the onboard LED
int kounter=0

void setup()
   {
    Serial.begin(9600);
    pinMode(13,OUTPUT);    
   }

void loop()
   { 
    kounter=kounter+1;
    Serial.print("kounter = ");Serial.println(kounter);   
    digitalWrite(13,HIGH);
    delay(1500);
    digitalWrite(13,LOW);
    delay(1000); 
    
    digitalWrite(13,HIGH);
    delay(1500);
    digitalWrite(13,LOW);
    delay(1000); 
    
    digitalWrite(13,HIGH);
    delay(500);
    digitalWrite(13,LOW);
    delay(1000);
     
    digitalWrite(13,HIGH);
    delay(1500);
    digitalWrite(13,LOW);
    delay(1000);

    delay(5000);
   }
