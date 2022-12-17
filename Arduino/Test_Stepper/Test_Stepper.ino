
const int stepPin1 = 3;
const int dirPin1 = 4;
const int stepPin2 = 6;
const int dirPin2 = 7;

void setup() {
  pinMode (3, OUTPUT);
  pinMode (4, OUTPUT);
  pinMode (6, OUTPUT);
  pinMode (7, OUTPUT);
  Serial.begin(9600);
}

void movestep1(int steps1, int direc1) {
  digitalWrite(dirPin1, direc1);
  for(int x = 0; x < steps1; x++) {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds (500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
}

void movestep2(int steps2, int direc2) {
  digitalWrite(dirPin2, direc2);
  for(int x = 0; x < steps2; x++) {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds (500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
}
void simul(int stepss){
  digitalWrite(dirPin1, HIGH);
  digitalWrite(dirPin2, HIGH);
  for(int x = 0; x<stepss; x++) {
    digitalWrite(stepPin1, HIGH);
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
  digitalWrite(dirPin1, LOW);
  digitalWrite(dirPin2, LOW);
  for(int x = 0; x<stepss; x++) 
    digitalWrite(stepPin1, HIGH);
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
  }
}

void loop() { 
 movestep1(600, 1);
 //movestep2(600, 1);
}
