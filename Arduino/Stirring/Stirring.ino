const int stir = 3;

void setup() {
  // put your setup code here, to run once:
pinMode(stir, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
analogWrite(stir, 200);
}
