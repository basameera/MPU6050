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

void MPU6050::initialize(int speed)
{
    // Beginning Wire
    wire->begin();
    wire->setClock(speed);

    // this->BaseInititalize();
}

uint8_t MPU6050::readRegister(uint8_t reg)
{
    // Begin comm. with MPU 6050
    wire->beginTransmission(address);

    //  Write address to start reading from
    wire->write(reg);

    //  End transmission: false = repeated start
    wire->endTransmission(false);

    // Request 6 bytes from the previously given address
    wire->requestFrom(address, 1);

    return wire->read();
}

bool MPU6050::isAvailable(void)
{
    if (this->readRegister(MPU_WHO_AM_I) == MPU_WHO_AM_I_VAL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void MPU6050::readRawTemp(void)
{
    // Begin comm. with MPU 6050
    wire->beginTransmission(address);

    //  Write address to start reading from
    wire->write(MPU_TEMP_ADD);

    //  End transmission: false = repeated start
    wire->endTransmission(false);

    // Request 6 bytes from the previously given address
    wire->requestFrom(address, 2);

    rawTemp = wire->read() << 8;
    rawTemp |= wire->read();
}

void MPU6050::readRawGyro(void)
{
    // Begin comm. with MPU 6050
    wire->beginTransmission(address);

    //  Write address to start reading from
    wire->write(MPU_GYRO_ADD);

    //  End transmission: false = repeated start
    wire->endTransmission(false);

    // Request 6 bytes from the previously given address
    wire->requestFrom(address, 6);

    // Gyro X
    rawGyroX = wire->read() << 8;
    rawGyroX |= wire->read();

    // Gyro Y
    rawGyroY = wire->read() << 8;
    rawGyroY |= wire->read();

    // Gyro Z
    rawGyroZ = wire->read() << 8;
    rawGyroZ |= wire->read();
}

void MPU6050::readRawAcc(void)
{
    // Begin comm. with MPU 6050
    wire->beginTransmission(address);

    //  Write address to start reading from
    wire->write(MPU_ACC_ADD);

    //  End transmission: false = repeated start
    wire->endTransmission(false);

    // Request 6 bytes from the previously given address
    wire->requestFrom(address, 6);

    // Acc X
    rawAccX = wire->read() << 8;
    rawAccX |= wire->read();

    // Acc Y
    rawAccY = wire->read() << 8;
    rawAccY |= wire->read();

    // Acc Z
    rawAccZ = wire->read() << 8;
    rawAccZ |= wire->read();
}

void MPU6050::readRawAll(void)
{
    // This is faster than initializing the bus twice (for gyro and acc)
    // Begin comm. with MPU 6050
    wire->beginTransmission(address);

    //  Write address to start reading from
    wire->write(MPU_ACC_ADD);

    //  End transmission: false = repeated start
    wire->endTransmission(false);

    // Request 6 bytes from the previously given address
    wire->requestFrom(address, 14);

    // Acc X
    rawAccX = wire->read() << 8;
    rawAccX |= wire->read();

    // Acc Y
    rawAccY = wire->read() << 8;
    rawAccY |= wire->read();

    // Acc Z
    rawAccZ = wire->read() << 8;
    rawAccZ |= wire->read();

    // TEMP
    rawTemp = wire->read() << 8;
    rawTemp |= wire->read();

    // Gyro X
    rawGyroX = wire->read() << 8;
    rawGyroX |= wire->read();

    // Gyro Y
    rawGyroY = wire->read() << 8;
    rawGyroY |= wire->read();

    // Gyro Z
    rawGyroZ = wire->read() << 8;
    rawGyroZ |= wire->read();
}

void MPU6050::readConfig(void)
{
    // Begin comm. with MPU 6050
    wire->beginTransmission(address);

    //  Write address to start reading from
    wire->write(MPU_SMPLRT_DIV);

    //  End transmission: false = repeated start
    wire->endTransmission(false);

    // Request 6 bytes from the previously given address
    wire->requestFrom(address, 4);

    SMPLRT_DIV_val, CONFIG_val, GYRO_CONFIG_val, ACCEL_CONFIG_val, PWR_MGMT_1_val;

    SMPLRT_DIV_val = wire->read();
    CONFIG_val = wire->read();

    GYRO_CONFIG_val = wire->read();
    ACCEL_CONFIG_val = wire->read();

    PWR_MGMT_1_val = this->readRegister(MPU_PWR_MGMT_1);
}

void MPU6050::writeRegister(uint8_t reg, uint8_t data)
{

    // Begin comm. with MPU 6050
    wire->beginTransmission(address);

    //  Write address to start reading from
    wire->write(reg);

    //  Write data
    wire->write(data);

    // End tx
    wire->endTransmission();
}