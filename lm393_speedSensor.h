#ifndef LM393_SPEEDSENSOR_H
#define LM393_SPEEDSENSOR_H

#include <Arduino.h>

class LM393_SpeedSensor
{
  public:
    LM393_SpeedSensor(int pin);
    float getRotationalSpeed();
    void timerISR();
    unsigned long _newTime = -1;
  private:
    int _pin;
    unsigned long _lastTime = -1;
    unsigned long _currTime = -1;
};

#endif