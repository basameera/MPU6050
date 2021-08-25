/*
 MPU6050.h - Arduino IMU Library
 Copyright (c) 2021 Sameera


*/

#include <Arduino.h>
#include "MPU6050.h"
#include <util/delay.h>

MPU6050::MPU6050(TwoWire &w, int i2cAddress)
{
    wire = &w;
    address = i2cAddress;
}

void MPU6050::initialize(int speed)
{
    // Beginning Wire
    wire->begin();
    wire->setClock(speed);

    this->baseInititalize();
}

void MPU6050::baseInititalize(void)
{
    // initialize variables
    offsetAccX = 0;
    offsetAccY = 0;
    offsetAccZ = 0;
    offsetGyroX = 0;
    offsetGyroY = 0;
    offsetGyroZ = 0;
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

void MPU6050::updateGyroValues(float factor)
{
    gyroX = (float)(rawGyroX - offsetGyroX) / factor;
    gyroY = (float)(rawGyroY - offsetGyroY) / factor;
    gyroZ = (float)(rawGyroZ - offsetGyroZ) / factor;
}

void MPU6050::updateAccValues(float factor)
{
    accX = (float)rawAccX / factor;
    accY = (float)rawAccY / factor;
    accZ = (float)rawAccZ / factor;
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

void MPU6050::setGyroOffset(int16_t x, int16_t y, int16_t z)
{
    offsetGyroX = x;
    offsetGyroY = y;
    offsetGyroZ = z;
}

void MPU6050::setAccOffset(int16_t x, int16_t y, int16_t z)
{
    offsetAccX = x;
    offsetAccY = y;
    offsetAccZ = z;
}

void MPU6050::discard(void)
{
    // discard first 100 readings
    for (uint16_t loop_x = 0; loop_x < DISCARD_MEASUREMENTS; loop_x++)
    {
        this->readRawAll();
        _delay_ms(1);
    }
}

void MPU6050::calibration(void)
{
    int16_t Ax = 0,
            Ay = 0,
            Az = 0,
            Gx = 0,
            Gy = 0,
            Gz = 0;

    this->discard();

    // TODO: why only Gyro calibration

    for (uint16_t loop_x = 0; loop_x < CALIB_MEASUREMENTS; loop_x++)
    {
        this->readRawGyro();

        Gx += rawGyroX;
        Gy += rawGyroY;
        Gz += rawGyroZ;

        _delay_ms(1);
    }

    Gx /= CALIB_MEASUREMENTS;
    Gy /= CALIB_MEASUREMENTS;
    Gz /= CALIB_MEASUREMENTS;

    this->setGyroOffset(Gx, Gy, Gz);
}