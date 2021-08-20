/*
 MPU6050.h - Arduino IMU Library
 Copyright (c) 2021 Sameera


*/

#ifndef MPU6050_h
#define MPU6050_h

#include <Arduino.h>

#define ON true
#define OFF false

class MPU6050
{
public:
    MPU6050(int pin);                                        //Constructor. attach pin to blink
    void blink(bool value);                                  //enable blinking with 1s duration
private:
    uint8_t pinNumber;
};

#endif