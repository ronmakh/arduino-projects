////////////////////////////////////////      PIN SETTINGS    ///////////////////////////
#include <DHT.h>

const int touch = 3;     //touch sensor
const int acid = 4;      //5v pump
const int alkali = 5;    //5v pump
const int nutrient = 6;  //5v pump
const int sprinkler = 40; //12v pump
const int exhaust = 8;   //5v pump
const int stir = 9;      //servo motor
const int atom = 38   ;     //24v ultrasonic atomiser
const int LED_humid = 24;//led
const int LED_nutri = 25;//led
const int LED_pH = 52;   //led
const int LS1 = A0;      //light sensor
const int LS2 = A1;      //light sensor
const int LPH = A2;      //ph sensor
const int LHUMID = A3;   //humidity/temp sensor
const int LNUTRI = A4;   //EC sensor
const int light = A5  ;  //use mosfet
const int fan = 42;      //use mosfet

bool START = false;

DHT dht(LHUMID, DHT11);

float nutri_level = 0.5;
float pH_LOW = 6.0;
float pH_HIGH = 6.5;
float humid_LOW = 400;
float humid_HIGH = 800;

//////////////////////////////     WATER LEVEL    ///////////////////////////
void highrise() {
  if (digitalRead(touch) == HIGH) {
    digitalWrite(exhaust, HIGH);
  }
  else if (digitalRead(touch) == LOW) {
    digitalWrite(exhaust, LOW);
  }
}

//////////////////////////////     WATERING ROOTS    ///////////////////////////
void watering() {
  digitalWrite(atom, HIGH);
  delay(10000);
  digitalWrite(atom, LOW);
  delay(10000);
}

//////////////////////////////     STIRRER    ///////////////////////////

void stirring() {
  analogWrite(stir, 200);
}

//////////////////////////////     pH LEVEL    ///////////////////////////
void pHing() {
  unsigned int pHValue;
  pHValue = analogRead(A2);
  if (pHValue >= pH_LOW) {
    digitalWrite(LED_pH, HIGH);
    digitalWrite(acid, HIGH);
    delay(500);
    digitalWrite(acid, LOW);
  }

  if (pHValue <= pH_HIGH) {
    digitalWrite(LED_pH, HIGH);
    digitalWrite(alkali, HIGH);
    delay(5000);
    digitalWrite(alkali, LOW);
  }
}

//////////////////////////////     NUTRIENT CONCENTRATION    ///////////////////////////
void ECing() {
  unsigned int nutriValue;
  nutriValue = analogRead(A4);
  if (nutriValue <= nutri_level) {
    stirring();
    digitalWrite(LED_nutri, HIGH);
    digitalWrite(exhaust, HIGH);
    delay(20000);
    digitalWrite(exhaust, LOW);
    delay(3000);
    digitalWrite(nutrient, HIGH);
  }
}

//////////////////////////////     HUMIDITY AND TEMPERATURE    ///////////////////////////
void humidtemp() {
  float humidValue = dht.readHumidity();
  float tempValue = dht.readTemperature();
  if (analogRead(humidValue) <= humid_LOW) {
    digitalWrite(LED_humid, HIGH);
    digitalWrite(fan, HIGH);
  }

  if (analogRead(humidValue) >= humid_HIGH) {
    digitalWrite(LED_humid, HIGH);
    digitalWrite(fan, HIGH);
  }
}

////////////////////////////////////////      SETUP SETTINGS    ///////////////////////////

void setup() {
  Serial.begin(9600);
  pinMode (3, INPUT);
  pinMode (4, OUTPUT);
  pinMode (5, OUTPUT);
  pinMode (6, OUTPUT);
  pinMode (7, OUTPUT);
  pinMode (8, OUTPUT);
  pinMode (9, OUTPUT);
  pinMode (10, OUTPUT);
  pinMode (11, OUTPUT);
  pinMode (12, OUTPUT);
  pinMode (13, OUTPUT);
  pinMode (A0, INPUT);
  pinMode (A1, INPUT);
  pinMode (A2, INPUT);
  pinMode (A3, INPUT);
  pinMode (A4, INPUT);
  pinMode (A5, OUTPUT);
  pinMode (A6, INPUT);

  dht.begin();


  
}

////////////////////////////////////////    LOOP SETTINGS    ///////////////////////////

void loop() {
  //  if (START == true) {
  //    digitalWrite(light, HIGH);
  //    stirring();
  //

  //    pHing();
  //

  //    ECing();
  //

  //    humidtemp();

  //  }
  stirring();
}
