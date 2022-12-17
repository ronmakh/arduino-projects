#include <AccelStepper.h>

AccelStepper myStepper3(1, 6, 7);

int c = 800;
int distance = 200;
int count = 0;
void beltStep() {
  myStepper3.moveTo(distance);
  myStepper3.setSpeed(c);
  myStepper3.run();
}

void setup() {
  myStepper3.setMaxSpeed(c);
  myStepper3.setCurrentPosition(0);
}

void loop() {
  beltStep();
  if myStepper3.distanceToGo() == 0) {
    count 
  }
}

