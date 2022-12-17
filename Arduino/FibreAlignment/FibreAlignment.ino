#include <AccelStepper.h>

AccelStepper myStepper1(1, 2, 3);
AccelStepper myStepper2(1, 4, 5);
AccelStepper myStepper3(1, 6, 7);

const int conv_butt = 8;
const int plat_butt = 9;
bool pONOFF = false;
bool cONOFF = false;

int s = 2000;
int c = 800;
int state = 0;
int conv_state = 123;

//direction distances
int F = 3200;
int B = 3200;
int L = 6400;
int R = 3200;
int conveyor = 3200;

void allStop() {
  if (digitalRead(plat_butt) == HIGH && digitalRead(conv_butt) == HIGH) {
    //Serial.println("stop");
    // steppers stop
    PORTD = B00000000; //sets all of the pins 0 to 7 as LOW to power off stepper1
    PORTB = B00000000; //sets all of the pins 8 to 13 as LOW to power off stepper2
  }
}

void beltStep() {
  myStepper3.moveTo(conveyor);
  myStepper3.setSpeed(c);
  myStepper3.run();
}

//to move the motors forward
void forwardStep() {
  //state ++;
  myStepper1.moveTo(F);
  myStepper2.moveTo(F);
  myStepper1.setSpeed(s);
  myStepper2.setSpeed(s);
  myStepper1.run();
  myStepper2.run();
}

// to move the motors back
void backwardStep() {
  state ++;
  while (B > 0) {
    if (pONOFF == false && digitalRead(plat_butt) == HIGH) {
      pONOFF = true;
    }
    if (pONOFF == true) {
      myStepper1.moveTo(-B);
      myStepper2.moveTo(-B);
      myStepper1.setSpeed(-s);
      myStepper2.setSpeed(-s);
      myStepper1.run();
      myStepper2.run();
      if (myStepper1.distanceToGo() == 0) {
        myStepper1.setCurrentPosition(0);
        myStepper2.setCurrentPosition(0);
        //Serial.print("Backward happened");
        pONOFF = false;
        break;
      }
    }
  }
}


// to move the motors in opposite directions (left)
void leftStep() {
  state ++;
  while (L >= 0) {
    if (pONOFF == false && digitalRead(plat_butt) == HIGH) {
      pONOFF = true;
    }
    if (pONOFF == true) {
      myStepper1.moveTo(-L);
      myStepper2.moveTo(L);
      myStepper1.setSpeed(-s);
      myStepper2.setSpeed(s);
      myStepper1.run();
      myStepper2.run();
      if (myStepper1.distanceToGo() == 0) {
        myStepper1.setCurrentPosition(0);
        myStepper2.setCurrentPosition(0);
        //Serial.print("Left happened");
        pONOFF = false;
        break;
      }
    }
  }
}

// to move the motors in opposite directions (right)
void rightStep() {
  state ++;

  if (pONOFF == true) {
    myStepper1.moveTo(R);
    myStepper2.moveTo(-R);
    myStepper1.setSpeed(s);
    myStepper2.setSpeed(-s);
    myStepper1.run();
    myStepper2.run();
    if (myStepper1.distanceToGo() == 0) {
      myStepper1.setCurrentPosition(0);
      myStepper2.setCurrentPosition(0);
      //Serial.print("Right happened");
    }
  }
}

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

void loop() {
  myStepper1.moveTo(F);
  myStepper2.moveTo(F);
  myStepper1.setSpeed(s);
  myStepper2.setSpeed(s);
  myStepper1.run();
  myStepper2.run();


  
//    if (cONOFF == false && digitalRead(conv_butt) == HIGH) {
//      cONOFF = true;
//      if (conv_state == true) {
//        beltStep();
//        if (myStepper3.distanceToGo() == 0) {
//          Serial.print("Belt moved");
//          myStepper3.setCurrentPosition(0);
//          cONOFF = false;
//        }
//      }
//    }
//    if (pONOFF == false && digitalRead(plat_butt) == HIGH ) {
//      pONOFF = true;
//      if (pONOFF == true && state == 0) {
//        forwardStep();
//        if (myStepper1.distanceToGo() == 0) {
//          myStepper1.setCurrentPosition(0);
//          myStepper2.setCurrentPosition(0);
//          state ++;
//          pONOFF = false;
//        }
//      }
//      else if (pONOFF == true && state == 1) {
//        rightStep();
//        if (myStepper1.distanceToGo() == 0) {
//          myStepper1.setCurrentPosition(0);
//          myStepper2.setCurrentPosition(0);
//          pONOFF = false;
//        }
//      }
//    }
}
