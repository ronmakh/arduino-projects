#include <AccelStepper.h> //Stepper Motor Library http://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html#ace236ede35f87c63d18da25810ec9736

//PIN SETTINGS
AccelStepper myStepper1(1, 2, 3); //Platform Stepper
AccelStepper myStepper2(1, 4, 5); //Platform Stepper
AccelStepper myStepper3(1, 6, 7); //Conveyor Belt Stepper

const int conv_butt = 8; //Button for Conveyor Belt
const int plat_butt = 9; //Button for Platform
bool pONOFF = false;     //Digital Mode for Platform Button
bool cONOFF = false;     //Digital Mode for PLatform Button

int s = 2000; //Platform Motor Speed
int c = 800;  //Cloveyor Belt Motor Speed

int state = 0;//Increment for Platform MOvement

//num of steps
//3200 steps for 1 full revolution
//1 rev == 4cm
int F = 3200; //* 6.25; //FORWARD
int B = 3200; //* 6.25; //BACKWARD
int L = 3200; //* 2.075; //LEFT
int R = 3200; //* 2.075 * 2; //RIGHT
int conveyor; //= 3200; //CONVEYOR BELT

//to stop all motors
void allStop() {
  PORTD = B00000000; //sets all of the pins 0 to 7 as LOW to power off stepper1
  PORTB = B00000000; //sets all of the pins 8 to 13 as LOW to power off stepper2
}

//to move conveyor belt
void beltStep() {
  myStepper3.moveTo(conveyor);
  myStepper3.setSpeed(c);
  myStepper3.run();
}

//to move the motors forward
void forwardStep() {
  myStepper1.moveTo(F);
  myStepper2.moveTo(F);
  myStepper1.setSpeed(s);
  myStepper2.setSpeed(s);
  myStepper1.run();
  myStepper2.run();
}

// to move the motors back
void backwardStep() {
  myStepper1.moveTo(-B);
  myStepper2.moveTo(-B);
  myStepper1.setSpeed(-s);
  myStepper2.setSpeed(-s);
  myStepper1.run();
  myStepper2.run();
  Serial.print(myStepper1.currentPosition()); Serial.print(",");Serial.println (myStepper2.currentPosition());
}


// to move the motors in opposite directions (left)
void leftStep() {
  myStepper1.moveTo(-L);
  myStepper2.moveTo(L);
  myStepper1.setSpeed(-s);
  myStepper2.setSpeed(s);
  myStepper1.run();
  myStepper2.run();
}

// to move the motors in opposite directions (right)
void rightStep() {
  myStepper1.moveTo(R);
  myStepper2.moveTo(-R);
  myStepper1.setSpeed(s);
  myStepper2.setSpeed(-s);
  myStepper1.run();
  myStepper2.run();
}

//run functions once
void setup() {
  Serial.begin(9600);
  pinMode (8, INPUT);
  pinMode (9, INPUT);
  myStepper1.setMaxSpeed(s);
  myStepper2.setMaxSpeed(s);
  myStepper3.setMaxSpeed(c);
  myStepper1.setCurrentPosition(0);
  myStepper2.setCurrentPosition(0);
  myStepper3.setCurrentPosition(0);
}

//run functions in a loop
void loop() {
  //CALLING BUTTON LOGICS
  if (digitalRead(conv_butt) == HIGH) {
    cONOFF = true;
  }

  if (digitalRead(plat_butt) == HIGH ) {
    pONOFF = true;
  }

  //IF BOTH BUTTONS ARE PRESSED
  if (digitalRead(plat_butt) == HIGH && digitalRead(conv_butt) == HIGH) {
    //allStop();                                                               //STOP MOVEMENT
    //delay(1000);
    Serial.print(myStepper1.currentPosition()); Serial.print(",");Serial.println (myStepper2.currentPosition());
    if (digitalRead(plat_butt) == LOW && digitalRead(conv_butt) == LOW) {
      myStepper1.moveTo(0);
      myStepper2.moveTo(0);
      Serial.println("It happened");
      myStepper1.setSpeed(-s);
      myStepper2.setSpeed(-s);
      myStepper1.run();
      myStepper2.run();
      delay(1000);   
      cONOFF = false;
      pONOFF = false;
    }
  }

  //IF PLATFORM BUTTON IS PRESSED (PRESS 7 TIMES TO COMPLETE CYCLE)
  if (pONOFF == true && state == 0) {         //MOVE BACKWARDS
    backwardStep();
    if (myStepper1.distanceToGo() == 0) {
      //myStepper1.setCurrentPosition(0);
      //myStepper2.setCurrentPosition(0);
      state ++;
      pONOFF = false;
    }
  }
  else if (pONOFF == true && state == 1) {    //MOVE LEFT
    leftStep();
    if (myStepper1.distanceToGo() == 0) {
      //myStepper1.setCurrentPosition(0);
      //myStepper2.setCurrentPosition(0);
      state ++;
      pONOFF = false;
    }
  }

  else if (pONOFF == true && state == 2) {    //MOVE FORWARD
    forwardStep();
    if (myStepper1.distanceToGo() == 0) {
      //myStepper1.setCurrentPosition(0);
      //myStepper2.setCurrentPosition(0);
      state ++;
      pONOFF = false;
    }
  }

  else if (pONOFF == true && state == 3) {    //MOVE LEFT
    leftStep();
    if (myStepper1.distanceToGo() == 0) {
      //myStepper1.setCurrentPosition(0);
      //myStepper2.setCurrentPosition(0);
      state ++;
      pONOFF = false;
    }
  }

  else if (pONOFF == true && state == 4) {    //MOVE BACKWARDS
    backwardStep();
    if (myStepper1.distanceToGo() == 0) {
      myStepper1.setCurrentPosition(0);
      myStepper2.setCurrentPosition(0);
      state ++;
      pONOFF = false;
    }
  }

  else if (pONOFF == true && state == 5) {    //MOVE RIGHT
    rightStep();
    if (myStepper1.distanceToGo() == 0) {
      myStepper1.setCurrentPosition(0);
      myStepper2.setCurrentPosition(0);
      state ++;
      pONOFF = false;
    }
  }
  else if (pONOFF == true && state == 6) {    //MOVE FORWARD
    forwardStep();
    if (myStepper1.distanceToGo() == 0) {
      myStepper1.setCurrentPosition(0);
      myStepper2.setCurrentPosition(0);
      state = 0;
      pONOFF = false;
    }
  }
  //MOVE CONVEYOR BELT WHEN PRESSED
  if (cONOFF == true) {
    beltStep();
    if (myStepper3.distanceToGo() == 0) {
      Serial.print("Belt moved");
      myStepper3.setCurrentPosition(0);
      cONOFF = false;
    }
  }
}

