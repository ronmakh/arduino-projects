const int pwm = 2 ;     //initializing pin 2 as ‘pwm’ variable
void setup()
{
  pinMode(pwm, OUTPUT) ; //Set pin 2 as output
}
void loop()
{
  analogWrite(pwm, 250) ;
  delay(1000);
  
  delay(2000);
}
