#include <AccelStepper.h>

// Define a stepper and the pins it will use

AccelStepper stepper1 (1,3,4); // Defaults to 4 pins on 2, 3, 4, 5

AccelStepper stepper2 (1,6,7); // Defaults to 4 pins on 2, 3, 4, 5



void setup()

{  
}



void checkStepper(AccelStepper & astepper){

    if (astepper.distanceToGo() == 0)

    {

 // Random change to speed, position and acceleration

 // Make sure we dont get 0 speed or accelerations



 astepper.moveTo(rand() % 12800);

 astepper.setMaxSpeed((rand() % 3200) + 1);

 astepper.setAcceleration((rand() % 6400) + 1);

    }





}



void loop()

{

  checkStepper(stepper1)  ;

  checkStepper(stepper2)  ;

  stepper1.run();

  stepper2.run();  

} 
