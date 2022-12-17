
#include <AccelStepper.h>

// Define some steppers and the pins the will use
AccelStepper stepper1(AccelStepper::DRIVER, 3, 4); 
AccelStepper stepper2(AccelStepper::DRIVER, 6, 7);

void setup()
{  
    
    stepper1.setMaxSpeed(60.0);
    //stepper1.setAcceleration(100.0);
    //stepper1.moveTo(1000000);
    
    stepper2.setMaxSpeed(60.0);
    //stepper2.setAcceleration(100.0);
    //stepper2.moveTo(1000000);
     
}

void loop()
{
    // Change direction at the limits
    //if (stepper1.distanceToGo() == 0)
  //stepper1.moveTo(-stepper1.currentPosition());
  stepper1.setSpeed(60);
  stepper2.setSpeed(60);
  stepper1.runSpeed();
  stepper2.runSpeed();
}

