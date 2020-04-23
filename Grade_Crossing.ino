// Grade Crossing Signal using the onboard LED

void setup()
   {
    Serial.begin(9600);
    pinMode(13,OUTPUT);
    
   }

void loop()
   {    
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
