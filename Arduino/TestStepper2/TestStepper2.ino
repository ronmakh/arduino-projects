#include <AccelStepper.h>
#include <MultiStepper.h>
#include <Stepper.h>

//definitions for each command to be recieved via serial port
#define COMMAND_LEFT 'a'
#define COMMAND_RIGHT 'd'
#define COMMAND_FORWARD 'w'
#define COMMAND_BACK 's'
#define COMMAND_STOP ' '

AccelStepper myStepper1(1, 3, 4);
AccelStepper myStepper2(1, 6, 7);
MultiStepper steppers;

int spr = 60;
int num_of_steps = 50;

char lastCall = ' ';

void forwardStep(int steps){
  Serial.println("forward");
  // step one step each forward
  myStepper1.setSpeed(spr);
  myStepper2.setSpeed(spr);
  steppers.setSpeed(spr);
  stepper.runSpeed(spr);
  delay(10);
}

// to move the motors back
void backwardStep(int steps){
  Serial.println("backward");
  // step one step each backward
  myStepper1.setSpeed(-spr);
  myStepper2.setSpeed(-spr);
  steppers.setSpeed(spr);
  stepper.runSpeed(spr);
  delay(10);
}
 

// to move the motors in opposite directions (left)
void leftStep(int steps){
  Serial.println("left");
 // step one step each left
  myStepper1.step(spr);
  myStepper2.step(-spr);
  steppers.setSpeed(spr);
  stepper.runSpeed(spr);
  delay(10);
}


// to move the motors in opposite directions (right)
void rightStep(int steps){
  Serial.println("right");
  // step one step each right
  myStepper1.step(-spr);
  myStepper2.step(spr);
  steppers.setSpeed(spr);
  stepper.runSpeed(spr);
  delay(10); 
}

// to power down the motor drivers and stop the motors
void allStop(){
  Serial.println("stop");
  // steppers stop
  PORTD = B00000000; //sets all of the pins 0 to 7 as LOW to power off stepper1
  PORTB = B00000000; //sets all of the pins 8 to 13 as LOW to power off stepper2
}
void setup() {
  Serial.begin(9600);//start the serial monitor - send and recieve at 9600 baud
  // set the speed at 60 rpm:
  myStepper1.setMaxSpeed(60);
  myStepper2.setMaxSpeed(60);
  steppers.addStepper(myStepper1);
  steppers.addStepper(myStepper2);
}

void loop() {
//check to see if there is serial communication and if so read the data
if(Serial.available()) {
char data = (char)Serial.read();
// switch to set the char via serial to a command
switch(data) {
  case COMMAND_FORWARD:
    forwardStep(num_of_steps);
    break; 
  case COMMAND_BACK:
    backwardStep(num_of_steps);
    break;
  case COMMAND_LEFT:
    leftStep(num_of_steps);
    break;
  case COMMAND_RIGHT:
    rightStep(num_of_steps);
    break;
  case COMMAND_STOP:
    allStop();
    break;
}
// set the 'lastCall' variable to the last call from the serial
lastCall = data;
}
else{
char data = lastCall;
switch(data) {
  case COMMAND_FORWARD:
    forwardStep(num_of_steps);
    break; 
  case COMMAND_BACK:
    backwardStep(num_of_steps);
    break;
  case COMMAND_LEFT:
    leftStep(num_of_steps);
    break;
  case COMMAND_RIGHT:
    rightStep(num_of_steps);
    break;
  case COMMAND_STOP:
    allStop();
    break;
}
lastCall = data;
}
}
