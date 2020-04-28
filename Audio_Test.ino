#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
SoftwareSerial mySoftwareSerial(7,8); // RX, TX (the first number goes to pin 3 of the MP3 player
                                      //         and the second number to pin 2.  The one going to
                                      //         pin 2 must have an in-line 330 ohm resistor.
                                      //         It is not required that the pins be PWM capable. 
                                      //
                                      // On my test setup:
                                      //   red wire (power) goes to 5V
                                      //   orange wire (pin 2 on MP3) goes to Arduino D8 (330 ohm)
                                      //   dark green wire (Pin 3 on MP3) goes to Arduino D7
                                      //   orange and yellow wires(Pins 6 and 8) go to speaker
                                      //   black wire goes to ground
                                      //   my test setup does not test MP3 pins 4 & 5 (amplifier)
                                      //   my test setup does not test MP3 player pin 16 ("busy")
                                               
DFRobotDFPlayerMini myDFPlayer;  //Instantiate myDFPlayer 

void setup() 
{
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);  //Start serial communication
  
//Initialize Player Parameters
myDFPlayer.setTimeOut(500); //Timeout serial 500ms
delay(500);
if (!myDFPlayer.begin(mySoftwareSerial))
      {
      Serial.println("MP3 Player Initialization Failure:");
      Serial.println("1.Check the connections to the DFPlayer Mini");
      Serial.println("2.Make certain the SD card is inserted in the player");
      while (true);  //stay here forever, until MP3 is fixed and system re-started
      }
      else
      {
      Serial.println("MP3 Player Initialized Successfully");
      }
myDFPlayer.volume(30); // Max Volume is 30     
myDFPlayer.EQ(0); //Normal Equalization
myDFPlayer.play(1); 
Serial.println("Sound played");
}

void loop() 
{
}
