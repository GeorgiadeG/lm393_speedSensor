#ifndef LM393_SPEEDSENSOR_H
#define LM393_SPEEDSENSOR_H

#include <Arduino.h>

class LM393_SpeedSensor
{
  public:
    LM393_SpeedSensor(int pin);
    float getRotationalSpeed();
    int timerISR(uint16_t currentTime);
  private:
    int _pin;
    unsigned long _lastTime = -1;
    unsigned long _currTime = -1;
};

#endif