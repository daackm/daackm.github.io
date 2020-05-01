//Carousel.  David Ackmann  March 16, 2020


#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX 
DFRobotDFPlayerMini myDFPlayer;  //Instantiate myDFPlayer 






/*
  I REALLY hate to do this, but I can't make the "readFileCounts" function work
  for the DFPlayerMini, unless the USB cable between the Arduino and the PC
  is connected.  I think it is related to some "COM" port issue.
  So, I have "bitten the bullet" and require you to hard code the proper
  number of MP3 files on your SD card in order for this to work.  DAA 03/23/2020
 */
int maxSongs = 14;  //How many songs are on the SD card?








char version[]= "0.1";  
int motorState=LOW;
int incomingByte=0;
long currentSong=0;
int A0Value; int A1Value; int A2Value;
unsigned long newSeed;
unsigned long pinZeroValue;
const int buttonPin=9;
const int relayPin=7;
int playingMinutes;
int playingSeconds;
unsigned long playingStart;
unsigned long playingTotal;
const int boardingSeconds=20;
int buttonState=0;
int lastButtonState=0;
unsigned long lastDebounceTime=0;  //last time the pin was toggled
unsigned long debounceDelay=50;
int play_state;
int reading;
int kounter;
//
// Most displays are at address 0x27, but some are 0x35; use the SCANNER program 
// available at some Arduino sites to see which you have, or if 0x27 fails,
// try 0x35.
//
LiquidCrystal_I2C lcd=LiquidCrystal_I2C(0x27,20,4);


void setup()
{
mySoftwareSerial.begin(9600);  //Start serial communication
lcd.init();
lcd.backlight();
lcd.setCursor(0,0);
lcd.print("Carousel v");lcd.print(version);
lcd.setCursor(1,1);
lcd.print("                    ");
A0Value=analogRead(0);
A1Value=analogRead(1);
A2Value=analogRead(2);
newSeed=(A0Value*A1Value*A2Value)*millis();
randomSeed(newSeed);
Serial.print("newSeed=");Serial.print(newSeed);  Serial.print("   A0Value=");Serial.println(A0Value);           
pinMode(buttonPin, INPUT_PULLUP);
pinMode (relayPin,OUTPUT);
delay(2000);
Serial.begin(9600); 
Serial.println("DFRobot DFPlayer Mini");
Serial.println("Initializing DFPlayer... (please wait 3~5 seconds)");
if (!myDFPlayer.begin(mySoftwareSerial))
{
lcd.setCursor(0,2);lcd.print("Player init failure");
Serial.println("Initialization Failure:");
Serial.println("1.Check the connections to the DFPlayer Mini");
Serial.println("2.Make certain the SD card is inserted in the player");
while (true);
}
lcd.setCursor(0,1);lcd.print("Player init success ");








Serial.println();
Serial.println("DFPlayer Mini Module initialized!");
//maxSongs = myDFPlayer.readFileCounts(DFPLAYER_DEVICE_SD);
delay(1000);
lcd.setCursor(0,2);
lcd.print("                    ");
lcd.setCursor(0,3);
lcd.print("                    ");
lcd.setCursor(0,2);
lcd.print("Songs on Chip       ");
lcd.setCursor(14,2);
lcd.print(maxSongs);


A0Value=analogRead(0);

//Initialize Player Parameters
//delay(1500);
myDFPlayer.setTimeOut(500); //Timeout serial 500ms
//delay(500);
myDFPlayer.volume(30); // Max Volume is 30  
//delay(500);   
myDFPlayer.EQ(0); //Normal Equalization
//delay(500);




Serial.println();
Serial.print("Number of sound files on SD card: "); Serial.println(maxSongs);
motorState=LOW;                  
digitalWrite(relayPin, LOW);
play_state=digitalRead(8);  //Is the MP3 device playing anything at the moment?
delay(2000);
lcd.setCursor(0,2);
lcd.print("                    ");
lcd.setCursor(0,3);
lcd.print("Flip Switch To Start");
}

void loop()
{
  reading=digitalRead(buttonPin);  //What is the state of the switch?
                                   //reading is zero if the switch is closed
                                   //and one if the switch is open; Yeah, kinda backwards
  Serial.print("reading = ");Serial.println(reading);
  Serial.print("lastButtonstate = ");Serial.println(lastButtonState);
  
  if (reading != lastButtonState)//has there been a change in the status of the main switch? 
     {
      lastDebounceTime=millis();
     }
     //
     //   Yes, there has been a change in the main switch status.  But
     //   have we waited long enough for transient voltages to diminish?
     //
  if((millis()-lastDebounceTime)>debounceDelay)
     //
     //  We have waited long enough for transient voltages to diminish, so let's
     //  decide if we are in EXECUTION of TURN OFF state
     //
     {
      // Serial.print("   Switch is stable.  ");Serial.print("reading=");Serial.print(reading);
      // Serial.print("  buttonState=");Serial.println(buttonState);
      if (reading==0)
        { 
          //
          //  We are entering EXECUTION state.  Give power to the Relay (carousel motor)
          //  Generate a random number for the music and start playing the song
          //
          // Serial.println("we are in EXECUTION state!!");
          buttonState=reading;             
          motorState=HIGH;
          digitalWrite(relayPin, HIGH);    
          currentSong=random(0,maxSongs)+1;  //Generate a random number of a song to play
          Serial.print("Now Playing: "); Serial.println(currentSong);
          myDFPlayer.play(currentSong);      //Start playing the random song
          playingStart=millis();
          lcd.setCursor(0,0);
          lcd.print("Carousel Running    ");
          lcd.setCursor(0,1);
          lcd.print("Song:               ");
          lcd.setCursor(6,1);
          lcd.print(currentSong);
          kounter=9;
          lcd.setCursor(kounter,1);
          lcd.print("Time:     ");
          lcd.setCursor(0,3);
          lcd.print("Flip Switch To Pause");
          delay(100);
          boolean play_state=digitalRead(8);
          //
          //  When the play state goes from 0 (the carousel is running) to 1 (the song is over)
          //  or the switch is OFF, shut things down
          //
          while (play_state==0)
             {
              //
              //We stay in this WHILE loop until a switch change, just repeatedly playing
              //random songs and proving "boarding time" between each song.
              //
              delay(250);
              playingTotal=(millis()-playingStart)/1000; 
              //Serial.print("PlayingTotal = ");Serial.print(playingTotal); 
              //Serial.print("   playingStart=");Serial.println(playingStart); 
              kounter=15;
              lcd.setCursor(kounter,1);
              playingMinutes=playingTotal/60;
              playingSeconds=playingTotal-(playingMinutes*60);
              lcd.print(playingMinutes);
              kounter=kounter+1;
              lcd.print(":");
              if(playingSeconds<10)  //print a leading zero
                 {
                  lcd.print("0");
                  kounter=kounter+1;
                 }
              lcd.print(playingSeconds);
              play_state=digitalRead(8);
              reading=digitalRead(buttonPin);
              buttonState=reading;
              if(buttonState==1)
                 {
                  //
                  //  The switch has been turned off, so stop the music
                  //  and stop the carousel motor
                  //
                  motorState=LOW;                  
                  digitalWrite(relayPin, LOW);
                  myDFPlayer.stop();
                  play_state=digitalRead(8);
                  lcd.setCursor(0,0);
                  lcd.print("Carousel Paused     ");
                  lcd.setCursor(0,1);
                  lcd.print("                    ");
                  lcd.setCursor(0,3);
                  lcd.print("Flip Switch To Start");
                 }
              } 
              //
              //  We have come to the end of a song, so shut down the carousel motor
              //  and allow the riders to get off and new ones to board
              //
              if (buttonState==0)
              {
                 play_state=digitalRead(8);              
                 digitalWrite(relayPin, LOW);
                 kounter=boardingSeconds-1;
                 while(kounter>0)
                 {
                   lcd.setCursor(0,0);
                   lcd.print("Carousel Re-Boarding");
                   lcd.setCursor(0,1);
                   lcd.print("Remaining Time:                    ");
                   lcd.setCursor(16,1);
                   //if(kounter>=10){lcd.setCursor(7,1);}
                   lcd.print(kounter);
                   lcd.setCursor(0,3);
                   lcd.print("                    ");
                   delay(1000);
                   kounter=kounter-1;
                }
              } 
              
              if(buttonState!=0)
                 {
                 lcd.setCursor(0,0);
                 lcd.print("Carousel Paused     ");
                 lcd.setCursor(0,3);
                 lcd.print("Flip Switch To Start     ");
                 }
           }  //end of if(readinge==0)



           
      if(reading!=0)
         {
          //Serial.println("We are now in TURN OFF state");
          motorState=LOW;
          digitalWrite(relayPin, LOW);
          myDFPlayer.stop(); 
          lcd.setCursor(0,0);
          lcd.print("Carousel Paused     ");
          lcd.setCursor(0,1);
          lcd.print("                    ");
          //newSeed=millis();         
          //randomSeed(newSeed);
          currentSong=random(0,maxSongs)+1;  //Generate a random number of a song to play 
         }  // else of if(reading!=0)
         
     }  //end of if(millis()-lastDebounceTime)>debounceDelay)

     delay(1000);
     
} //  end of main loop
