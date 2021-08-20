/*
 MPU6050.h - Arduino IMU Library
 Copyright (c) 2021 Sameera


*/

#include <Arduino.h>
#include "MPU6050.h"

MPU6050::MPU6050(TwoWire &w, int i2cAddress)
{
    pinMode(13, OUTPUT);
    wire = &w;
    address = i2cAddress;
}

void MPU6050::blink(void)
{

    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);
}

void MPU6050::Initialize(int speed)
{

    // Beginning Wire
    wire->begin();
    wire->setClock(speed);
    // TODO: Set clock frequency
    // this->BaseInititalize();
}

void MPU6050::readRegister(void)
{
    // Begin comm. with MPU 6050
    wire->beginTransmission(address);

    //  Write address to start reading from
    wire->write(MPU_WHO_AM_I);

    //  End transmission: false = repeated start
    wire->endTransmission(false);

    // Request 6 bytes from the previously given address
    wire->requestFrom(MPU_ADD, 1);

    who_am_i = wire->read();
}