# lm393_speedSensor library

## Info
This library acts as an overlay for some basic functionalities for the **lm393 speed sensor**. It was implemented for a personal project and there is no guarantee that there are no flaws but if you notice any issue let me know.

## How to use
### Clone repository
Navigate to your library folder inside the Arduino directory
```cmd
 ../Arduino/libraries
```
And then clone this repository
```
git clone git@github.com:GeorgiadeG/lm393_speedSensor.git
```
### Include library in the code

Include the library and initialize an 'object' for the Speed Sensor.

Moreover to actually use the functionality you need to attach an Interrupt routine to run every time the sensor detects a change from **LOW** to **HIGH**

```c++
#include <lm393_speedSensor.h>

const int speed_sensor_pin = 2; // Change the pin number to the appropriate number according to your setup

LM393_SpeedSensor lm = LM393_SpeedSensor(speed_sensor_pin);


/**
 * Please put this function otherwise it wont work
 * because if I pass the new time as parameter in the ISR function, Arduino doesnt like it
 * so this is a cheap way to work around it but it is TODO to fix this.
 **/
void updateISR() {
  lm._newTime = millis();
  lm.timerISR();
} 

void setup() {
    ...
    attachInterrupt(digitalPinToInterrupt(speed_sensor_pin), updateISR, RISING);
}

void loop() {
    ...
    // Simply print the rotational speed
    Serial.println(lm.getRotationalSpeed());
    ...
}
```




