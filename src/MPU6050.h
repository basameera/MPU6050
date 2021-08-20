/*
    MPU6050.h - Arduino IMU Library
    Copyright (c) 2021 Sameera

    https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf
    https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf
*/

#ifndef MPU6050_h
#define MPU6050_h

#include <Arduino.h>
#include <Wire.h>

#define MPU_ADD 0x68

// MPU 6050 address define: Based on https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf
// - data registers
#define MPU_ACCEL_XOUT_H 0x3B
#define MPU_TEMP_OUT_H 0x41
#define MPU_GYRO_XOUT_H 0x43

// - config registers
#define MPU_SMPLRT_DIV 0x19
#define MPU_CONFIG 0x1A
#define MPU_GYRO_CONFIG 0x1B
#define MPU_ACCEL_CONFIG 0x1C
#define MPU_PWR_MGMT_1 0x6B

#define MPU_WHO_AM_I 0x75
#define MPU_WHO_AM_I_VAL 0x68

// - Config register values
#define GYRO_FS_SEL_0 0x00     // 250 deg/s
#define GYRO_FS_SEL_1 (1 << 3) // 500 deg/s
#define GYRO_FS_SEL_2 (2 << 3) // 1000 deg/s
#define GYRO_FS_SEL_3 (3 << 3) // 2000 deg/s

#define ACC_AFS_SEL_0 0x00     // 2g
#define ACC_AFS_SEL_1 (1 << 3) // 4g
#define ACC_AFS_SEL_2 (2 << 3) // 8g
#define ACC_AFS_SEL_3 (3 << 3) // 16g

// My address definition
#define MPU_GYRO_ADD MPU_GYRO_XOUT_H
#define MPU_ACC_ADD MPU_ACCEL_XOUT_H
#define MPU_TEMP_ADD MPU_TEMP_OUT_H

// I2C stuff
#define I2C_SPEED_100K 100000
#define I2C_SPEED_400K 400000

class MPU6050
{
public:
    MPU6050(TwoWire &w, int i2cAddress = MPU_ADD);
    void blink(void);
    // Setup method
    void Initialize(int speed = I2C_SPEED_100K);
    void readRegister(void);

    int who_am_i;

private:
    // I²C stuff
    TwoWire *wire;

    int address;
    int16_t rawAccX, rawAccY, rawAccZ, rawGyroX, rawGyroY, rawGyroZ, rawTemp;
};

#endif