#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
SoftwareSerial mySoftwareSerial(10,11); // RX, TX 
DFRobotDFPlayerMini myDFPlayer;  //Instantiate myDFPlayer 
int maxSongs = 1;  //How many songs are on the SD card?  Not used in this program


/*   
 There are nine slots for storing control values for LED.  For each slot we store the number of
 the pin controlled by this slot and its current state ("ON" or "OFF"). For analog controlled LEDs
 three additional states exist : "RISE", "DWELL" and "FALL") 
 We also note whether the pin is Digital or Analog ("D" or "A"). MinOnTime and MaxOnTime
 represent the upper and lower bounds for how long, in milliseconds, that this LED in this slot 
 may be on without cycling off.  MinOffTime and MaxOffTime represent the upper and lower bounds for 
 how long, in milliseconds, that the LED in this slot may be off without cycling on.  NextStateChangeTime
 represents the next time, in milliseconds, when the LED in this slot is scheduled to cycle
 into its opposite state.  
 
 */
int PinNumber[10];  
String LEDState[10];
char AnalogOrDigital[10];
unsigned int MinOnTime[10];
unsigned int MaxOnTime[10];
unsigned int MinOffTime[10];
unsigned int MaxOffTime[10];
unsigned long StartTime[10];
unsigned long NextStateChangeTime[10];
int RisePercent[10];
int FallPercent[10];


int i;
long currentSong=1;
int A0Value;
unsigned long newSeed;
boolean play_state;
int NumberOfPinsUsed;
//
// Most displays are at address 0x27, but some are 0x35; use the SCANNER program 
// available at some Arduino sites to see which you have, or if 0x27 fails,
// try 0x35.
//

//LiquidCrystal_I2C lcd=LiquidCrystal_I2C(0x27,20,4);

void setup()
{     
   pinMode(2,OUTPUT);
   pinMode(3,OUTPUT);
   pinMode(4,OUTPUT);
   pinMode(5,OUTPUT);
   pinMode(6,OUTPUT);
   pinMode(7,OUTPUT);
   pinMode(8,OUTPUT);
   pinMode(9,OUTPUT);
   pinMode(12,OUTPUT);

   digitalWrite(2,HIGH);
   digitalWrite(3,HIGH);
   digitalWrite(4,HIGH);
   digitalWrite(5,HIGH);
   digitalWrite(6,HIGH);
   digitalWrite(7,HIGH);
   digitalWrite(8,HIGH);
   digitalWrite(9,HIGH);
   digitalWrite(12,HIGH);

   delay(5000);

   mySoftwareSerial.begin(9600);  //Start serial communication
   Serial.println("Waterfall 06/30/20");
   //lcd.init();
   //lcd.backlight();
   //lcd.setCursor(0,0);
   //lcd.print("Waterfall   06/30/20");
   //lcd.setCursor(1,1);
   //lcd.print("                    ");
   A0Value=analogRead(0);
   newSeed=millis()*A0Value;
   randomSeed(newSeed);
   //Serial.print("newSeed=");Serial.print(newSeed);  Serial.print("   A0Value=");Serial.println(A0Value);           
   //pinMode(buttonPin, INPUT_PULLUP);
   delay(500);
   Serial.begin(9600); 
   Serial.println("DFRobot DFPlayer Mini");
   Serial.println("Initializing DFPlayer... (please wait 3~5 seconds)");
   

   if (!myDFPlayer.begin(mySoftwareSerial))
      {
      Serial.println("Initialization Failure:");
      Serial.println("1.Check the connections to the DFPlayer Mini");
      Serial.println("2.Make certain the SD card is inserted in the player");
      //lcd.setCursor(0,1);lcd.print("Player init failure");
      while (true);  //remove comment after MP3 Player installed
      }


   Serial.println();
   Serial.println("DFPlayer Mini Module initialized!");
   delay(1000);
   A0Value=analogRead(0);
   newSeed=millis()*A0Value;
   randomSeed(newSeed);
   Serial.print("newSeed=");Serial.print(newSeed);  Serial.print("   A0Value=");Serial.println(A0Value); 


//initialize LED Slot Parameters
//
//  by my convention, the red wire is on the long LED lead (anode),
//  and the black wire is on the shorter lead (cathode).  The black
//  wire will have the resistor, and is connected to the ground bus.
//  Which by elimination means that the red wire is connected to a
//  digital pin.
//


NumberOfPinsUsed=9;

PinNumber[1]=2;                 //  by default, pin 2 is a consistant "heart beat"
   AnalogOrDigital[1]='D';
   LEDState[1]="OFF";
   MinOnTime[1]=400;            //  all instances must be less than 65000
   MaxOnTime[1]=400;            //  all instances must be less than 65000
   MinOffTime[1]=1000;          //  all instances must be less than 65000
   MaxOffTime[1]=1000;          //  all instances must be less than 65000
   NextStateChangeTime[1]=500;
   
PinNumber[2]=3;
   AnalogOrDigital[2]='D';
   LEDState[2]="OFF";
   MinOnTime[2]=500;
   MaxOnTime[2]=2000;
   MinOffTime[2]=1500;
   MaxOffTime[2]=3000;
   NextStateChangeTime[2]=8000;
   
PinNumber[3]=4;
   AnalogOrDigital[3]='D';
   LEDState[3]="OFF";
   MinOnTime[3]=200;
   MaxOnTime[3]=400;
   MinOffTime[3]=200;
   MaxOffTime[3]=400;
   NextStateChangeTime[3]=2000;
   
PinNumber[4]=5;
   AnalogOrDigital[4]='D';
   LEDState[4]="OFF";
   MinOnTime[4]=500;
   MaxOnTime[4]=700;
   MinOffTime[4]=4000;
   MaxOffTime[4]=10000;
   NextStateChangeTime[4]=5000;
   
PinNumber[5]=6;
   AnalogOrDigital[5]='D';
   LEDState[5]="OFF";
   MinOnTime[5]=200;
   MaxOnTime[5]=400;
   MinOffTime[5]=200;
   MaxOffTime[5]=400;
   NextStateChangeTime[5]=2000;
   
PinNumber[6]=7;
   AnalogOrDigital[6]='D';
   LEDState[6]="OFF";
   MinOnTime[6]=200;
   MaxOnTime[6]=400;
   MinOffTime[6]=500;
   MaxOffTime[6]=700;
   NextStateChangeTime[6]=2000;
   
PinNumber[7]=8;
   AnalogOrDigital[7]='D';
   LEDState[7]="OFF";
   MinOnTime[7]=100;
   MaxOnTime[7]=200;
   MinOffTime[7]=2000;
   MaxOffTime[7]=4000;
   NextStateChangeTime[7]=2000;
   
PinNumber[8]=9;
   AnalogOrDigital[8]='D';
   LEDState[8]="OFF";
   MinOnTime[8]=500;
   MaxOnTime[8]=1000;
   MinOffTime[8]=5000;
   MaxOffTime[8]=7000;
   NextStateChangeTime[8]=2000;
   
PinNumber[9]=12;
   AnalogOrDigital[9]='D';
   LEDState[9]="OFF";
   MinOnTime[9]=800;
   MaxOnTime[9]=1200;
   MinOffTime[9]=3000;
   MaxOffTime[9]=4000;
   NextStateChangeTime[9]=2000;





//Initialize Player Parameters

   myDFPlayer.setTimeOut(500); //Timeout serial 500ms
   myDFPlayer.volume(30); // Max Volume is 30     
   myDFPlayer.EQ(0); //Normal Equalization
   //maxSongs = myDFPlayer.readFileCounts(DFPLAYER_DEVICE_SD);
   Serial.println();
   //lcd.setCursor(0,1);lcd.print("Player init success");
   delay(500);
   myDFPlayer.play(currentSong);
   play_state=digitalRead(13);  //Is the MP3 device playing anything at the moment?
Serial.print("in setup, play_state = ");Serial.println(play_state);
  
      
}

void loop()
{

//
//  check to see if the player has come to the end of the background MP3 file
//
play_state=digitalRead(13);
Serial.print("   in loop play_state = ");Serial.println(play_state);

 
 if(play_state==true)
   {
    myDFPlayer.play(currentSong);
   }

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
        //Serial.print("   NextStateChangeTime triggered,  LedState = ");Serial.print(LocalLEDState);
        //Serial.print("  Index = ");Serial.print(index);
       // Serial.print("  millis = ");Serial.print(Localmillis);
        //Serial.print("  AnalogOrDigital = ");Serial.println(AnalogOrDigital[index]);
        if(AnalogOrDigital[index]=='D')  //  Is it a digital pin
           {
           //Serial.println("   AnalogOrDigital: Digital Triggered");
           if(LocalLEDState=="OFF")
              {
              //  we need to transition from dark to light state,
              //  calculate the time of the next state change,
              //  and change the state of the slot
                  //Serial.println("LEDState OFF Triggered");
                  digitalWrite(LocalPinNumber,HIGH);
                  StartTime[index]=Localmillis;
                  NextStateChangeTime[index]=random(MinOnTime[index],MaxOnTime[index])+Localmillis;
                  //Serial.print("      Turning LED ON, NextStateChangeTime = ");Serial.print(NextStateChangeTime[index]);
                  //Serial.print("  Upon leaving, AnalogOrDigital = ");Serial.println(AnalogOrDigital[index]);
                  LEDState[index]="ON";
              }   //  end of LEDState = OFF
          if(LocalLEDState=="ON")
              {
              //  we need to transition from light to dark state
              //  calculate the time of the next state change,
              //  and change the state of the slot
       
                  //Serial.println("LEDState ON Triggered");
                  digitalWrite(LocalPinNumber,LOW);
                  NextStateChangeTime[index]=random(MinOffTime[index],MaxOffTime[index])+Localmillis;
                  //Serial.print("      Turning LED OFF, NextStateChangeTime = ");Serial.print(NextStateChangeTime[index]);
                  //Serial.print("  Upon leaving, AnalogOrDigital = ");Serial.println(AnalogOrDigital[index]);
                  LEDState[index]="OFF";
              }   //  end of LEDState= ON
           }  // end of AnalogOrDigital = D
        }  //end of NextStateChangeTime
   return 1;
   }
