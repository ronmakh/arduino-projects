#include <AccelStepper.h>
AccelStepper s1 (1,3,4);
AccelStepper s2 (1,6,7);


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
if (s1.distanceToGo()==0);
  s1.moveTo(100);
  s2.moveTo(100);
  s1.setMaxSpeed(1000);
  s2.setMaxSpeed(1000);
  s1.setSpeed(20);
  s2.setSpeed(20);
  s1.runSpeed();
  s2.runSpeed();
}
