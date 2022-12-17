//Limit Switch notes
//Must put resistor to ground
//COM goes to ground
//NC at 5V, NO at pin gives 1 when not pressed
//NO at 5V, NC at pin gives 0 when not pressed
const int sw = 10;
int pstate = LOW;
int nstate = HIGH;
int state;

void setup() {
  // put your setup code here, to run once:
  pinMode (sw, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly)
  state = digitalRead(sw);
  Serial.print(state);
  delay(10);
} 
