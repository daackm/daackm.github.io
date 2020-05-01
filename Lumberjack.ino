#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
SoftwareSerial mySoftwareSerial(7,8); // RX, TX 
DFRobotDFPlayerMini myDFPlayer;  //Instantiate myDFPlayer 
 
// Arduino stepper motor control code

#include <Servo.h> // Include the header file

LiquidCrystal_I2C lcd=LiquidCrystal_I2C(0x27,20,4);

// create an instance of the servo class 
Servo servoChopper;
Servo servoTree;

int pos;
int chops;
int cycle;
int startflag=HIGH;
unsigned long int laststarttime;

void setup() 
{
pinMode(12,INPUT_PULLUP);
pinMode(3,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(2,OUTPUT);
pinMode(5,OUTPUT);
delay(250); 


lcd.init();
lcd.backlight();
lcd.setCursor(0,0);
lcd.print("Lumberjack v0.1     ");
lcd.setCursor(1,1);
lcd.print("                    ");
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);  //Start serial communication

  mySoftwareSerial.println("In SETUP");
  servoChopper.attach(2);
  servoTree.attach(4);
  servoChopper.write(0);
  servoTree.write(0);
  delay(1000);
  servoChopper.detach();
  servoTree.detach();
/*
  lcd.setCursor(0,1);
  lcd.print("chopper at 0");
  delay(5000);
  servoChopper.write(90);
  lcd.setCursor(0,1);
  lcd.print("chopper at 90");
  delay(5000);
  servoChopper.write(0);
  delay(1000);           // without a delay before detach the motor will not
                         // have enough time to react, and will stay in the wrong position  
  servoChopper.detach();  

  
  lcd.setCursor(0,1);
  lcd.print("tree should be at 40");
  servoTree.write(40);
  delay(5000);
  servoTree.write(0);
  delay(1000);            // gotta have the delay before the detach!!
  servoTree.detach();
 // delay(10000);
*/
  
//Initialize Player Parameters
myDFPlayer.setTimeOut(500); //Timeout serial 500ms
delay(500);
if (!myDFPlayer.begin(mySoftwareSerial))
      {
      Serial.println("MP3 Player Initialization Failure:");
      Serial.println("1.Check the connections to the DFPlayer Mini");
      Serial.println("2.Make certain the SD card is inserted in the player");
      lcd.setCursor(0,1);
      lcd.print("MP3 Startup Failed  ");
      while (true);  //stay here forever, until MP3 is fixed and system re-started
      }
      else
      {
      lcd.setCursor(0,1); 
      lcd.print("MP3 Startup Success ");
      delay(2500);
      lcd.setCursor(0,1);
      lcd.print("                    ");
      }
myDFPlayer.volume(30); // Max Volume is 30     
myDFPlayer.EQ(0); //Normal Equalization
lcd.setCursor(0,0);lcd.print("   Press Button    ");
lcd.setCursor(0,1);lcd.print("     To Start      ");
}

void loop() 
{

   analogWrite(3, 50+random(205));
   analogWrite(5, 50+random(205));
   analogWrite(6, 50+random(205));

  startflag=digitalRead(12);
  delay(200);
  Serial.print("startflag = ");Serial.println(startflag);
  if(startflag==LOW)
    {


    // Report the the chopping cycle has started
      
    cycle=cycle+1;
    Serial.print("Lumberjack Chopping, cycle = ");Serial.println(cycle);
    lcd.setCursor(0,0);
    lcd.print("Lumberjack Chopping ");  
    lcd.setCursor(0,1);
    lcd.print("                    ");  
    lcd.setCursor(0,1);lcd.print(" Chop ");



    // Start the chopping action
    
    for (chops = 1; chops <= 5; chops++) 
       {       
       myDFPlayer.play(1); //single chop
       servoChopper.attach(2);
       
       for (pos=0; pos<=89;pos+=2)
          {
          lcd.setCursor(6,1);lcd.print(chops);
          servoChopper.write(pos);
          delay(17);          
          }
          delay(500);
          
       for (pos=89; pos>=1; pos-=2)
          {
          servoChopper.write(pos);
          delay(33); 
          }
       servoChopper.write(0);
       
       delay(100);              //gotta have the delay before the detach
       servoChopper.detach();
       delay(180);
       }



    //  Report the start of the Treefall
    
    lcd.setCursor(0,1);lcd.print("                    ");   
    myDFPlayer.play(2); //falling tree

    Serial.println("  Tree is Falling");
    lcd.setCursor(0,0);
    lcd.print("Lumberjack Treefall ");


    // Start the Treefall
    
    delay(1500);
    servoTree.attach(4);
    for (pos=1; pos<=5; pos+=1)
       {
        servoTree.write(pos);     //total movement should be about 70 degrees
        delay(300);
       }  
   
    for (pos=7; pos<=12; pos+=1)
       {
        servoTree.write(pos);     
        delay(150);
       }
   
    for (pos=13; pos<=30; pos+=1)
       {
        servoTree.write(pos);     
        delay(80);
       }
   
    for (pos=31; pos<=75; pos+=1)
       {
        servoTree.write(pos);     
        delay(40);
       } 

   delay(200);
       
   for (pos=75; pos>=65; pos-=1)  //Bounce Up
       {
        servoTree.write(pos);     
        delay(50);
       }
       
   for (pos=64; pos>=60; pos-=1)  //Bounce Up
       {
        servoTree.write(pos);     
        delay(70);
       }
       
    delay(100);
    
    for (pos=61; pos<=64; pos+=1)    //bounce down
       {
        servoTree.write(pos);     
        delay(100);
       }

   delay(20);
    
    for (pos=65; pos<=75; pos+=1)    //bounce down
       {
        servoTree.write(pos);     
        delay(75);
       }          
   servoTree.detach();

// Let the tree lie there for 15 seconds

    lcd.setCursor(0,0);
        lcd.print("                    ");
        lcd.setCursor(0,0);
        lcd.print("Tree Down.");
        lcd.setCursor(1,1);lcd.print("Wait ");
    for (pos=1; pos<=15; pos+=1)
       {
        lcd.setCursor(6,1);       
        lcd.print(15-pos);lcd.print(" seconds.   ");
        delay(1000);
       }




    //  Raise the tree back to upright position
       
    lcd.setCursor(0,1);lcd.print("                    ");
    lcd.setCursor(0,0);
    lcd.print("Restoring Tree.      ");
    servoTree.attach(4);
    delay(1000);
    for (pos=75; pos>=0; pos-=1)  //Return to upright
       {
        servoTree.write(pos);     
        delay(60);
       }

    servoTree.write(0);
    delay(1000);
    servoTree.detach();


    // Allow the lumberjack to rest

    lcd.setCursor(0,0);
    lcd.print("Lumberjack Resting. ");
    for (pos=1; pos<=15; pos+=1)
       {        
        lcd.setCursor(1,1);lcd.print("Wait ");
        lcd.print(15-pos);lcd.print(" seconds.  ");
        delay(1000); 
       }
    



    // Allow the process to be repeated
    
    lcd.setCursor(0,0);lcd.print("   Press Button    ");
    lcd.setCursor(0,1);lcd.print("     To Start      ");
    Serial.println("  Action is completed");
    startflag=0;
   }
}
