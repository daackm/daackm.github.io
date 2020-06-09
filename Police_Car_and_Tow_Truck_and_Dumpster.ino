
int i;

void setup() 
 {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);  
  pinMode(11,OUTPUT);
 }

void loop() {
 
  digitalWrite(2,HIGH);
  for (i=1; i<=4; i++)
    {
      digitalWrite(7,HIGH);
      digitalWrite(8,LOW);
      delay(200); 
      
      analogWrite(3, 50+random(205));
      analogWrite(5, 50+random(205));
      analogWrite(6, 50+random(205));
      analogWrite(9, 50+random(205));
      analogWrite(10, 50+random(205));
      analogWrite(11, 50+random(205));
  
      digitalWrite(7,LOW);
      digitalWrite(8,HIGH);
      delay(200);
      
      analogWrite(3, 50+random(205));
      analogWrite(5, 50+random(205));
      analogWrite(6, 50+random(205));
      analogWrite(9, 50+random(205));
      analogWrite(10, 50+random(205));
      analogWrite(11, 50+random(205));
  
    }
  digitalWrite(2,LOW);
  for (i=1; i<=4; i++)
    {
      digitalWrite(7,HIGH);
      digitalWrite(8,LOW);
      delay(200); 
  
      analogWrite(3, 50+random(205));
      analogWrite(5, 50+random(205));
      analogWrite(6, 50+random(205));
      analogWrite(9, 50+random(205));
      analogWrite(10, 50+random(205));
      analogWrite(11, 50+random(205));
  
      digitalWrite(7,LOW);
      digitalWrite(8,HIGH);
      delay(200);
      
      analogWrite(3, 50+random(205));
      analogWrite(5, 50+random(205));
      analogWrite(6, 50+random(205));
      analogWrite(9, 50+random(205));
      analogWrite(10, 50+random(205));
      analogWrite(11, 50+random(205));
      
    }
}
