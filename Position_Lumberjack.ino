#include "SoftwareSerial.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
SoftwareSerial mySoftwareSerial(7,8); // RX, TX 
#include <Servo.h> // Include the header file

LiquidCrystal_I2C lcd=LiquidCrystal_I2C(0x27,20,4);

// create an instance of the servo class 
Servo servoChopper;

int pos;

void setup() 
{
pinMode(2,OUTPUT);
delay(250); 

  Serial.begin(9600);
  mySoftwareSerial.begin(9600);  //Start serial communication

  mySoftwareSerial.println("In SETUP");
  servoChopper.attach(2);
  servoChopper.write(0);
  delay(1000);

//Initialize Player Parameters
lcd.setCursor(0,0);lcd.print("Moving Jack to     ");
lcd.setCursor(0,1);lcd.print(" Impact Position   ");
 
       for (pos=0; pos<=89;pos+=2)
          {
          servoChopper.write(pos);
          delay(17);          
          }
}

void loop() 
{
}
