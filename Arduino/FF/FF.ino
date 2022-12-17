//CONVEYOR BELT PIN SETTINGS
const int Con_stepPin = 13;
const int Con_dirPin = 12;
//PLATE HOLDER PIN SETTINGS
const int holder_stepPin = 6;
const int holder_dirPin = 5;
const int sleepPin = 7;
              //BUTTON PIN SETTING                                                                                                                                                                                                                                                                                                                                                                                                                      
const int buttonPin = 9; 
//AVOID DELAY SETTINGS
unsigned long Con_previousMillis = 0;
unsigned long holder_previousMillis = 0;
//BUTTON CONFIG
int buttonState = LOW; 
int isbutton_ran= false;
//SUBHOOK
int tempbuttonstate = 0; //SUBHOOK FOR BUTTON
int templocation_x = 0; //TOTAL ROTATION DISTANCE RECORDER
//STEPPER MOTOR SPEED SETTING
const int frontstepsize =10; //FORWARD HOLDER SPEED
const int reversestepsize = 1; //REVERSE HOLDER SPEED
const int conveyorbeltstepsize = 15; //CONVEYOR SPEED
//STEPPER MOTOR ROTATION DISTANCE
unsigned long interval = 8000; //FIXED DISTANCE


void setup() {
  // put your setup code here, to run once:
//  Serial.begin(9600);
  pinMode(sleepPin,OUTPUT);
  
  //ACTIVATING CONVEYOR BELT PINS
  pinMode(Con_stepPin, OUTPUT);
  pinMode(Con_dirPin, OUTPUT);
  digitalWrite(Con_dirPin,LOW); //DEFAULT CONVEYOR BELT ROTATE DIRECTION
  //ACTIVATING PLATE HOLDER PINS
  pinMode(holder_stepPin, OUTPUT);
  pinMode(holder_dirPin, OUTPUT);
  digitalWrite(sleepPin, LOW); //PUT STEPPER MOTOR TO SLEEP
  //ACTIVATING BUTTON PIN VIA PULLUP
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() 
{
  //Serial.print(buttonState);
  buttonState = digitalRead(buttonPin); //READ CURRENT BUTTON STATE
  if(buttonState ==LOW)
  {
      tempbuttonstate = 1; //SUBHOOK
  }
  if(tempbuttonstate==1)
  {
    if(isbutton_ran == false)
    {
    
    digitalWrite(sleepPin, HIGH); //UNSLEEP MOTOR STEPPER
    digitalWrite(holder_dirPin,LOW); //MOVING TOWARD STEPPER MOTOR
    unsigned long holder_currentMillis = millis(); //GET CURRENT TIME
    
    if (holder_currentMillis - holder_previousMillis >= frontstepsize) 
      {
        digitalWrite(holder_stepPin,HIGH); //ACTIVATING HIGH_STEP
        templocation_x+=1; //UPDATE DISTANCE TRAVELLED
        holder_previousMillis = holder_currentMillis; //UPDATE TIME
        digitalWrite(holder_stepPin,LOW); //ACTIVATING LOW_STEP
      }
    if( templocation_x >= interval)
    {
      //reset
      digitalWrite(sleepPin, LOW); //PUT STEPPER MOTOR TO SLEEP
      tempbuttonstate= 0; //RESET SUBHOOK BUTTON STATE
      templocation_x =0; //RESET DISTANCE TRAVELLED
      isbutton_ran = true; //RESET PREVIOUS BUTTON STATE TO TRUE
    }
    }
  }
    if(tempbuttonstate==1)
    {
    if(isbutton_ran == true)
    {
     
    digitalWrite(sleepPin, HIGH); //UNSLEEP MOTOR STEPPER
    digitalWrite(holder_dirPin,HIGH); //MOVING AWAY FROM STEPPER MOTOR
    unsigned long holder_currentMillis = millis(); //GET CURRENT TIME
    
    if (holder_currentMillis - holder_previousMillis >= reversestepsize) 
      {
        digitalWrite(holder_stepPin,HIGH); //ACTIVATING HIGH_STEP
         templocation_x+=1; //UPDATE DISTANCE TRAVELLED
        holder_previousMillis = holder_currentMillis; //UPDATE TIME
        digitalWrite(holder_stepPin,LOW); //ACTIVATING LOW_STEP
      }
    if( templocation_x >= interval)
    {
       digitalWrite(sleepPin, LOW); //PUT STEPPER MOTOR TO SLEEP
      tempbuttonstate= 0; //RESET SUBHOOK BUTTON STATE
      templocation_x =0; //RESET DISTANCE TRAVELLED
      isbutton_ran = false; //RESET PREVIOUS BUTTON STATE TO FALSE
    }
    }
    }
    
  conveyorbelt(); //START CONVEYOR BELT
}

void conveyorbelt()
{
  
  
  unsigned long Con_currentMillis = millis(); //GET CURRENT TIME
  if (Con_currentMillis - Con_previousMillis >= conveyorbeltstepsize) 
    {
    digitalWrite(Con_stepPin,HIGH); //ACTIVATING HIGH_STEP
    Con_previousMillis = Con_currentMillis; //UPDATE TIME
    digitalWrite(Con_stepPin,LOW); //ACTIVING LOW_STEP
    }
}

