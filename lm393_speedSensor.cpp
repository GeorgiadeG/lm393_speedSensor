#include "lm393_speedSensor.h"
#include "Arduino.h"

lm393_speedSensor::lm393_speedSensor(int pin)
{
  _pin = pin;
  pinMode(_pin, INPUT);
}

/**
*   @brief  Interrupt Service Routine for the speed sensor
*   @param  currentTime: The current time in milliseconds
*   @retval Exit status 0 -> OK , 1 -> Error
*/
int lm393_speedSensor::timerISR(uint16_t currentTime)
{
    if (_lastTime == -1)
    {
        _lastTime = currentTime;
        return 0;
    } else if (_currTime == -1)
    {
        _currTime = currentTime;
        return 0;
    } else
    {
        _lastTime = _currTime;
        _currTime = currentTime;
        return 0;
    }
    return 1;
}

/**
*   @brief  Calculates the rotational speed of the motor, based on the time between two interrupts 
            two interrupts correspond to 1/20 of a rotation
*   @retval The rotational speed of the motor
*/
float lm393_speedSensor::getRotationalpeed(){
    return speed = (1/20 * 2 * PI) / ((_currTime - _lastTime) / 1000);
}