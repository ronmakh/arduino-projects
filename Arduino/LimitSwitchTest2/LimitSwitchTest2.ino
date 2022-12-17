//Limit Switch notes
//Must put resistor to ground
//COM goes to ground
//NC at 5V, NO at pin gives 1 when not pressed
//NO at 5V, NC at pin gives 0 when not pressed
#include <AccelStepper.h>

AccelStepper p(1, 2, 3);
AccelStepper c(1, 6, 7);

//Platform Pin Settings
const int bp = 9;
int s = 2000;
bool pONOFF = false;
int ptemp = 0;

//Conveyor Belt Pin Settings
const int bc = 8;
int v = 300;
bool cONOFF = false;
int ctemp = 0;

void setup() {
  Serial.begin(9600);
  pinMode (8, INPUT);
  pinMode (9, INPUT);
  p.setMaxSpeed(s);
  c.setMaxSpeed(v);
  p.setCurrentPosition(0);
  c.setCurrentPosition(0);
}

void loop() {
  
  if (pONOFF == false && digitalRead(bp) == HIGH) {
    pONOFF = true;
  }
  if (pONOFF == true){
    p.moveTo(3200);
    p.setSpeed(s);
    p.run();
    if (p.distanceToGo() == 0) {
      p.setCurrentPosition(0);
      Serial.print("It happened");
      pONOFF = false;
    }
  }
  
//  if (pONOFF == false){
//    p.moveTo(0);
//    p.setSpeed(s);
//    p.run();
//    if (p.distanceToGo() == 0) {
//      delay(1000);
//    }
//  }
  
  
}
