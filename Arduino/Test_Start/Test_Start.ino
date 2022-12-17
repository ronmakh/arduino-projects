#include <AccelStepper.h>

AccelStepper myStepper1(1, 2, 3); //Platform Stepper
AccelStepper myStepper2(1, 4, 5); //Platform Stepper
const int x_butt = 10;
const int y_butt = 11;
bool xSTART = false;
bool ySTART = false;
int s = 2000;
int startspeed = 800;
int L = 3200; //LEFT
int F = 3200; //RIGHT
int countSTART = 0;

void allStop() {
  PORTD = B00000000; //sets all of the pins 0 to 7 as LOW to power off stepper1
  PORTB = B00000000; //sets all of the pins 8 to 13 as LOW to power off stepper2
}

//to move the motors forward
void forwardStep(int F, int s) {
  myStepper1.moveTo(F);
  myStepper2.moveTo(F);
  myStepper1.setSpeed(s);
  myStepper2.setSpeed(s);
  myStepper1.run();
  myStepper2.run();
}

// to move the motors in opposite directions (left)
void leftStep(int L, int s) {
  myStepper1.moveTo(-L);
  myStepper2.moveTo(L);
  myStepper1.setSpeed(-s);
  myStepper2.setSpeed(s);
  myStepper1.run();
  myStepper2.run();
}

void backSTART() {
  myStepper1.setSpeed(-s);
  myStepper2.setSpeed(-s);
  myStepper1.runSpeed();
  myStepper2.runSpeed();
}

void rightSTART() {
  myStepper1.setSpeed(s);
  myStepper2.setSpeed(-s);
  myStepper1.runSpeed();
  myStepper2.runSpeed();
}

//run functions once
void setup() {
  //To setup Serial Monitor
  Serial.begin(9600);
  //Setup pins for buttons
  pinMode (8, INPUT);
  pinMode (9, INPUT);
  pinMode (10, INPUT);
  pinMode (11, INPUT);
  //Setting Max Speed of Stepper Motors
  myStepper1.setMaxSpeed(s);
  myStepper2.setMaxSpeed(s);
  myStepper3.setMaxSpeed(c);
  myStepper1.setCurrentPosition(0);
  myStepper2.setCurrentPosition(0);
  myStepper3.setCurrentPosition(0);

  while (countSTART <= 2) {
    //CALLING BUTTON LOGICS
    if (digitalRead(x_butt) == HIGH) {
      xSTART = true;
    }
    if (digitalRead(y_butt) == HIGH) {
      ySTART = true;
    }

    if (countSTART == 2) {
      allStop();
      Serial.print("0");
      break;
    }

    while (xSTART == false && ySTART == false) {
      rightSTART();   //move right to hit right button
      break;
    }
    while (xSTART == true && ySTART == false) {
      backSTART();    //move downwards to hit bottom button
      break;
    }

    while (xSTART == true && ySTART == true && countSTART <= 1) {
      if (countSTART == 0) {
        myStepper1.setCurrentPosition(0);
        myStepper2.setCurrentPosition(0);
        countSTART ++;
      }
      if (countSTART == 1) {
        forwardStep(F, s);      //positioning platform to start position
        if (myStepper1.distanceToGo() == 0) {
          myStepper1.setCurrentPosition(0);
          myStepper2.setCurrentPosition(0);
          countSTART ++;
          break;
        }
      }
    }
  }
}



void loop() {
}
