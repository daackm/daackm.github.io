void setup() 
 {
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);  
  pinMode(11,OUTPUT);
 }

void loop() 
 {
  analogWrite(3, 50+random(205));
  analogWrite(5, 50+random(205));
  analogWrite(6, 50+random(205));
  analogWrite(9, 50+random(205));
  analogWrite(10, 50+random(205));
  analogWrite(11, 50+random(205));
  delay(100);
 }
