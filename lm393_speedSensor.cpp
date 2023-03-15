#include "lm393_speedSensor.h"
#include "Arduino.h"

LM393_SpeedSensor::LM393_SpeedSensor(int pin)
{
  _pin = pin;
  pinMode(_pin, INPUT);
}

/**
*   @brief  Interrupt Service Routine for the speed sensor
*   @param  currentTime: The current time in milliseconds
*   @retval Exit status 0 -> OK , 1 -> Error
*/
void LM393_SpeedSensor::timerISR()
{
    counter++;
    unsigned long currentTime = _newTime;
    if (_lastTime == -1)
    {
        _lastTime = currentTime;
        // Serial.println("test1");
        // Serial.println(_lastTime);
    } else if (_currTime == -1)
    {
        _currTime = currentTime;
    } else
    {
        _lastTime = _currTime;
        _currTime = currentTime;
        // Serial.println(_currTime);
        // Serial.println(_lastTime);
    }
}

/**
*   @brief  Calculates the rotational speed of the motor, based on the time between two interrupts 
            two interrupts correspond to 1/20 of a rotation
*   @retval The rotational speed of the motor
*/
float LM393_SpeedSensor::getRotationalSpeed(){
    // Serial.println(_currTime);
    // Serial.println(_lastTime);
    // Serial.println(1.0/20.0 * 2.0 * PI);
    // Serial.println((float)(_currTime - _lastTime) / 1000.0);
    if (_lastTime == -1 || _currTime == -1) {
        return 0;
    } 
    return (1.0/20.0 * 2.0 * PI) / ((float)(_currTime - _lastTime) / 1000);
}