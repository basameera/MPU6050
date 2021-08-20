/*
 MPU6050.h - Arduino IMU Library
 Copyright (c) 2021 Sameera


*/

#include <Arduino.h>
#include "MPU6050.h"

MPU6050::MPU6050(TwoWire &w, int i2cAddress)
{
    pinMode(13, OUTPUT);
}

void MPU6050::blink(void)
{

    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);
}
