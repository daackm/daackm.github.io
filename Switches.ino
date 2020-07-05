
int pinState;
void setup() {
  
  // This code tests the use of switches
  // Make ABSOLUTELY CERTAIN that the pinMode on the input
  // pin is set to "INPUT_PULLUP", not "INPUT".
  
Serial.begin(9600);
pinMode(2,INPUT_PULLUP);
pinMode(13,OUTPUT);
}

void loop() {
  
  // Every time through the loop, we will test to see if the
  // switch on pin 2 is open or closed. When the switch is closed,  
  // the LED on pin 13, the one in the center of the Arduino, near 
  // one end, will turn on, and when the switch is open, the
  // LED will turn off.  You could take any action when the 
  // switch changes state, like changing the value of a variable,
  // or whatever. 
  
  // NOTE: that a LOW value
  // indicates that the switch is closed, and a HIGH value
  // indicates that the switch is open.  Counter-intuitive,
  // but that's the way it works.
  
pinState=digitalRead(2);

if(pinState==LOW)
  {
   digitalWrite(13,HIGH); 
  }
 else
 {
 digitalWrite(13,LOW);
 }
}
