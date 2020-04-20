#include "SoftwareSerial.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//This sketch exercises a a 4 line Display
//using pin A4 and A5 to SDA and SCL, respectively
//It also requires 5V and GND to the servo

//address may be either 0x27 or 0x3F
LiquidCrystal_I2C lcd=LiquidCrystal_I2C(0x27,20,4);
int kounter=0;

void setup() 
{
  Serial.begin(9600);
  Serial.println("Inside SETUP");
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("DISPLAY TEST        ");
  delay(2000);
}


void loop() 
{ 
   kounter=kounter+1; 
   lcd.setCursor(0,2);
   lcd.print("Kounter = ");lcd.print(kounter);
   Serial.println("loop");
  delay(1984);
}
