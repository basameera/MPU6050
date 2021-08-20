/*
 MPU6050.h - Arduino IMU Library
 Copyright (c) 2021 Sameera


*/

#include <Arduino.h>
#include "MPU6050.h"

MPU6050::MPU6050(int pin)
{
    pinMode(pin, OUTPUT);
    pinNumber = pin;
}

void MPU6050::blink(bool value)
{
    if (value == true)
    {
        digitalWrite(pinNumber, HIGH);
        delay(1000);
        digitalWrite(pinNumber, LOW);
        delay(1000);
    }
    else
    {
        digitalWrite(pinNumber, LOW);
    }
}
