#include <AccelStepper.h>

#define COMMAND_LEFT 'a'
#define COMMAND_RIGHT 'd'
#define COMMAND_FORWARD 'w'
#define COMMAND_BACK 's'

#define COMMAND_STOP ' '

AccelStepper myStepper1(1, 2, 3);
AccelStepper myStepper2(1, 4, 5);
AccelStepper myStepper3(1, 6, 7);


char lastCall = ' ';
int s = 1000;
int c = -400;

void beltStep(){
  myStepper3.setSpeed(c);
  myStepper3.runSpeed();
}

//to move the motors forward
void forwardStep(){
  //Serial.println("forward");
  //step one step each forward
  myStepper1.setSpeed(s);
  myStepper2.setSpeed(s);
  myStepper1.runSpeed();
  myStepper2.runSpeed();
}

// to move the motors back
void backwardStep(){
  //Serial.println("backward");
  // step one step each backward
  myStepper1.setSpeed(-s);
  myStepper2.setSpeed(-s);
  myStepper1.runSpeed();
  myStepper2.runSpeed();
}
 

// to move the motors in opposite directions (left)
void leftStep(){
  //Serial.println("left");
 // step one step each left
  myStepper1.setSpeed(-s);
  myStepper2.setSpeed(s);
  myStepper1.runSpeed();
  myStepper2.runSpeed();
}


// to move the motors in opposite directions (right)
void rightStep(){
  //Serial.println("right");
  //step one step each right
  myStepper1.setSpeed(s);
  myStepper2.setSpeed(-s);
  myStepper1.runSpeed();
  myStepper2.runSpeed(); 
}

// to power down the motor drivers and stop the motors
void allStop(){
  //Serial.println("stop");
  // steppers stop
  PORTD = B00000000; //sets all of the pins 0 to 7 as LOW to power off stepper1
  PORTB = B00000000; //sets all of the pins 8 to 13 as LOW to power off stepper2
}


void setup() {
  Serial.begin(9600);
  myStepper1.setMaxSpeed(s);
  myStepper2.setMaxSpeed(s);
  myStepper3.setMaxSpeed(c);
  //myStepper1.setAcceleration(0);
  //myStepper2.setAcceleration(0);
}

void loop() {
//check to see if there is serial communication and if so read the data
if(Serial.available()) {
char data = (char)Serial.read();
// switch to set the char via serial to a command
switch(data) {
  case COMMAND_FORWARD:
    forwardStep();
    beltStep();
    break; 
  case COMMAND_BACK:
    backwardStep();
    beltStep();
    break;
  case COMMAND_LEFT:
    leftStep();
    beltStep();
    break;
  case COMMAND_RIGHT:
    rightStep();
    beltStep();
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
    forwardStep();
    beltStep();
    break; 
  case COMMAND_BACK:
    backwardStep();
    beltStep();
    break;
  case COMMAND_LEFT:
    leftStep();
    beltStep();
    break;
  case COMMAND_RIGHT:
    rightStep();
    beltStep();
    break;
  case COMMAND_STOP:
    allStop();
    break;
}
lastCall = data;
}
}
