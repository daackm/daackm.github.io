#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//  Written by Dave Ackmann, June 2020
/*   
 There are nine slots for storing control values for LED.  For each slot we store the number of
 the pin controlled by this slot and its current state ("ON" or "OFF").  MinOnTime and MaxOnTime
 represent the upper and lower bounds for how long, in milliseconds, that this LED in this slot 
 may be on without cycling off.  MinOffTime and MaxOffTime represent the upper and lower bounds for 
 how long, in milliseconds, that the LED in this slot may be off without cycling on.  NextStateChangeTime
 represents the next time, in milliseconds, when the LED in this slot is scheduled to cycle
 into its opposite state. Note that arrays are zero-based, not one-based, but we will not be using 
 the first entry in each array (the zero-base).  Why?  Because it made it easier on my feeble mind. 

 Pins D2-D10 are reserved for controlling the LEDs;
 
 */
int PinNumber[10];  
String LEDState[10];
unsigned int MinOnTime[10];
unsigned int MaxOnTime[10];
unsigned int MinOffTime[10];
unsigned int MaxOffTime[10];
unsigned long StartTime[10];
unsigned long NextStateChangeTime[10];


int i;
int NumberOfPinsUsed;
//
// Most displays are at address 0x27, but some are 0x35; use the SCANNER program 
// available at some Arduino sites to see which you have, or if 0x27 fails,
// try 0x35.
//

   LiquidCrystal_I2C lcd=LiquidCrystal_I2C(0x27,20,4);



void setup()
{  
   Serial.begin(9600);  //Start serial communication
   delay(1000);
   Serial.println("Monty's Motors 06/03/20");
   lcd.init();
   lcd.backlight();
   lcd.setCursor(0,0);
   lcd.print("Monty's Motors  06/03/20");
   lcd.setCursor(1,1);
   lcd.print("                    ");

   pinMode(2,OUTPUT);
   pinMode(3,OUTPUT);
   pinMode(4,OUTPUT);
   pinMode(5,OUTPUT);
   pinMode(6,OUTPUT);
   pinMode(7,OUTPUT);
   pinMode(8,OUTPUT);
   pinMode(9,OUTPUT);
   pinMode(10,OUTPUT);

   digitalWrite(2,HIGH);
   digitalWrite(3,HIGH);
   digitalWrite(4,HIGH);
   digitalWrite(5,HIGH);
   digitalWrite(6,HIGH);
   digitalWrite(7,HIGH);
   digitalWrite(8,HIGH);
   digitalWrite(9,HIGH);
   digitalWrite(10,HIGH);

   delay(5000);

//initialize LED Slot Parameters
//
//  by my convention, the red wire is on the long LED lead (anode),
//  and the black wire is on the shorter lead (cathode).  The black
//  wire will have the resistor, and is connected to the ground bus.
//  Which by elimination means that the red wire is connected to a
//  digital pin.
//


NumberOfPinsUsed=5;

PinNumber[1]=7;        //Monty's Motors  for some reason pin 2 does not work on this extension board
   LEDState[1]="OFF";
   MinOnTime[1]=8000;            //  all instances must be less than 65000
   MaxOnTime[1]=8000;            //  all instances must be less than 65000
   MinOffTime[1]=1000;           //  all instances must be less than 65000
   MaxOffTime[1]=2000;           //  all instances must be less than 65000
   NextStateChangeTime[1]=500;
   
PinNumber[2]=3;        //Bowling Alley
   LEDState[2]="OFF";
   MinOnTime[2]=5000;
   MaxOnTime[2]=10000;
   MinOffTime[2]=2000;
   MaxOffTime[2]=4000;
   NextStateChangeTime[2]=8000;
   
PinNumber[3]=4;        //Store Room
   LEDState[3]="OFF";
   MinOnTime[3]=200;
   MaxOnTime[3]=800;
   MinOffTime[3]=2200;
   MaxOffTime[3]=4200;
   NextStateChangeTime[3]=200;
   
PinNumber[4]=5;         //Barney's Bar & Grill
   LEDState[4]="OFF";
   MinOnTime[4]=7000;
   MaxOnTime[4]=9000;
   MinOffTime[4]=4000;
   MaxOffTime[4]=10000;
   NextStateChangeTime[4]=5000;
   
PinNumber[5]=6;          //Ballroom
   LEDState[5]="OFF";
   MinOnTime[5]=10000;
   MaxOnTime[5]=20000;
   MinOffTime[5]=5000;
   MaxOffTime[5]=8000;
   NextStateChangeTime[5]=2000;
   
PinNumber[6]=7;
   LEDState[6]="OFF";
   MinOnTime[6]=200;
   MaxOnTime[6]=400;
   MinOffTime[6]=500;
   MaxOffTime[6]=700;
   NextStateChangeTime[6]=2000;
   
PinNumber[7]=8;
   LEDState[7]="OFF";
   MinOnTime[7]=100;
   MaxOnTime[7]=200;
   MinOffTime[7]=2000;
   MaxOffTime[7]=4000;
   NextStateChangeTime[7]=2000;
   
PinNumber[8]=9;
   LEDState[8]="OFF";
   MinOnTime[8]=1000;
   MaxOnTime[8]=2000;
   MinOffTime[8]=5000;
   MaxOffTime[8]=7000;
   NextStateChangeTime[8]=2000;
   
PinNumber[9]=10;
   LEDState[9]="OFF";
   MinOnTime[9]=800;
   MaxOnTime[9]=1200;
   MinOffTime[9]=3000;
   MaxOffTime[9]=4000;
   NextStateChangeTime[9]=2000;
   
PinNumber[3]=4;
   LEDState[3]="OFF";
   MinOnTime[3]=200;
   MaxOnTime[3]=400;
   MinOffTime[3]=200;
   MaxOffTime[3]=400;
   NextStateChangeTime[3]=2000;

Serial.println("End of Setup");

}

void loop()
{
//
//  check to see if the player has come to the end of the background MP3 file
//
lcd.setCursor(0,1);lcd.print("                    ");
lcd.setCursor(0,1);
lcd.print("Elapsed Sec: ");
lcd.print(millis()/1000);


//
//   Cycle through the LED Slots
//
   for (i = 1; i <= NumberOfPinsUsed; i++) 
   {
    CheckStatus(i, millis());
  }
} //  end of main loop


void CheckStatus(int index, unsigned long Xmillis)
   {
    int LocalPinNumber;
    String LocalLEDState;
    unsigned long LocalNextStateChangeTime;
    unsigned long Localmillis;
    unsigned long Delta;  

    
    LocalPinNumber=PinNumber[index];
    LocalLEDState=LEDState[index];
    Localmillis=Xmillis;


    
    //
    //  Has the NextChangeStateTime for this slot passed?
    //
    if(NextStateChangeTime[index]<=Localmillis)
       {
        Serial.print("NextStateChangeTime triggered,  Current LedState = ");Serial.print(LocalLEDState);
        Serial.print("  millis = ");Serial.println(Localmillis);
        Serial.print("  Index = ");Serial.print(index);
        Serial.print("  PinNumber = ");Serial.println(PinNumber[index]);
        
           if(LocalLEDState=="OFF")
              {
              //  we need to transition from dark to light state,
              //  calculate the time of the next state change,
              //  and change the state of the slot
                  Serial.println("    LEDState OFF Triggered");
                  digitalWrite(LocalPinNumber,HIGH);
                  StartTime[index]=Localmillis;
                  NextStateChangeTime[index]=random(MinOnTime[index],MaxOnTime[index])+Localmillis;
                  Serial.print("      Turning LED ON, NextStateChangeTime = ");Serial.println(NextStateChangeTime[index]);
                  LEDState[index]="ON";
              }   //  end of LEDState = OFF
              
          if(LocalLEDState=="ON")
              {
              //  we need to transition from light to dark state
              //  calculate the time of the next state change,
              //  and change the state of the slot
       
                  Serial.println("    LEDState ON Triggered");
                  digitalWrite(LocalPinNumber,LOW);
                  NextStateChangeTime[index]=random(MinOffTime[index],MaxOffTime[index])+Localmillis;
                  Serial.print("      Turning LED OFF, NextStateChangeTime = ");Serial.println(NextStateChangeTime[index]);
                  LEDState[index]="OFF";
              }   //  end of LEDState= ON
        }  //end of NextStateChangeTime
   return 1;
   }
