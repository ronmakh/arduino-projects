am t/*
USMC BattleBots Training Code

Simplified version
Author: IvanLing
Last Updated: 12/12/17 1646 Hr

Bluetooth --> TX to Pin 10,  RX to Pin 11
Continuous Rotation Servos --> Pin 8 and 9

*/

#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial mySerial(10, 11);

Servo myservoL;  // create servo object to control the Left servo
Servo myservoR;  // create servo object to control the Right servo
//The servos used in this example are continuous rotation servos, 
//which works slightly differently than conventional servos.

void setup() {
    Serial.begin(9600); //Start the serial on bluetooth
    myservoL.attach(8); //Connect Left servo to pin 8
    myservoR.attach(9); //Connect Right servo to pin 9
}

void loop() {
  //Reads the Bluetooth
  String input = Serial.readString();
  if(input == "up")
  {
    Serial.println("Hello world");
  }
  if(input == "down")
  {
    Serial.println("stupidaf")
  }
  //Make a decision based on what you read

  //Take note because of the way the servo is mounted
  // 0 = turn clockwise max speed, 180 = counter clockwise max speed, 
  //90 = stop. Anything in between = slower speed.
  
  if(input == "u"){
    myservoL.write(0);
    myservoR.write(180);  
  }
  else if(input == "d"){
    myservoL.write(180);
    myservoR.write(0);
  }
  else if(input == "l"){
    myservoL.write(0);
    myservoR.write(0);
  }
  else if(input == "r"){
    myservoL.write(180);
    myservoR.write(180);
  }
  else if(input == "s")
  {
    myservoL.write(90);
    myservoR.write(90);
  }
  
}
