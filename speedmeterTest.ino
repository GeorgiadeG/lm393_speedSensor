#include <lm393_speedSensor.h>
#include <ArduPID.h>

/**
  Setup pins for testing purposes (?)
**/
const int ENA_pin = 6;
const int in_1 = A1;
const int in_2 = A0;

unsigned long myTime = 0;

double targetRotationalSpeed = 12.0;

float p = 0.2;
float i = 0.2;
float d = 0.0;

double output = 130;
double input = 0.0;

const int min_pwm = 100;
const int max_pwm = 240;

LM393_SpeedSensor lm = LM393_SpeedSensor(2);
ArduPID pid;

void setup() {
  Serial.begin(9600); //adjust  
  pinMode(ENA_pin, OUTPUT);
  pinMode(in_1, OUTPUT);
  pinMode(in_2, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(2), updateISR, RISING);

  pid.begin(&input, &output, &targetRotationalSpeed, p, i, d);
  pid.setOutputLimits(min_pwm, max_pwm);
  // attachInterrupt(digitalPinToInterrupt(2), helloWorld, RISING);
  digitalWrite(in_1, HIGH);
  digitalWrite(in_2, LOW);
  delay(3000);
  pid.start();
}

void updateISR() {
  lm._newTime = millis();
  lm.timerISR();
}

// void helloWorld() {
//   Serial.println("Hello world");
//   Serial.println(millis())
// }

// uint16_t getTime(){
//   return millis();
// }

void loop()
{
  input = lm.getRotationalSpeed();
  pid.compute();
  //Serial.print("Input : ");
  //Serial.println(output);
  analogWrite(ENA_pin, output);
  // Serial.print("Time--: ");
  // myTime = millis();

  // Serial.println(myTime); // prints time since program started
  delay(200);         
  Serial.println(lm.getRotationalSpeed());
  // delay(10);
}