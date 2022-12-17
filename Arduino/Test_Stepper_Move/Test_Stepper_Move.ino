#include <AccelStepper.h>

AccelStepper aa(1, 6, 7);
int count = 0;

void fw800() {
  aa.setCurrentPosition(0);
  aa.setSpeed(2000);
  aa.moveTo(3200);
  aa.run();
  if (aa.distanceToGo() == 0) {
    delay(1000);
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  aa.setMaxSpeed(2000);
  aa.setCurrentPosition(0);
  //aa.moveTo(3200);
}

void loop() {
  while (count == 0) {
    // put your main code here, to run repeatedly:
    aa.setSpeed(2000);
    aa.moveTo(3200);
    aa.run();
    if (aa.distanceToGo() == 0) {
      count = 1;
    }
  }
}
