void setup() {
 for(int i =2;i<10;i++){  //loop to setup pinModes from pin 2 to pin 9, 8 LEDS
  pinMode(i,OUTPUT);
}

}

void loop() {
  // put your main code here, to run repeatedly:
for(int x = 2; x<10;x++){
  digitalWrite(x,HIGH);
  delay(1000);
  digitalWrite(x,LOW);
}
}
