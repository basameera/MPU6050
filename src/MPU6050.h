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

#define MPU_ADDRESS 0x68

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
// -- MPU_GYRO_CONFIG values
#define GYRO_FS_SEL_0 0x00     // 250 deg/s
#define GYRO_FS_SEL_1 (1 << 3) // 500 deg/s
#define GYRO_FS_SEL_2 (2 << 3) // 1000 deg/s
#define GYRO_FS_SEL_3 (3 << 3) // 2000 deg/s
// -- MPU_ACCEL_CONFIG
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

// Sensitivity Scale Factor (SSF)
// - Gyro
#define G_SSF_0 131.0f
#define G_SSF_1 65.5f
#define G_SSF_2 32.8f
#define G_SSF_3 16.4f

// - Acc
#define A_SSF_0 16384.0f
#define A_SSF_1 8192.0f
#define A_SSF_2 4096.0f
#define A_SSF_3 2048.0f

// - calibration
#define DISCARD_MEASUREMENTS 100
#define CALIB_MEASUREMENTS 1000

class MPU6050
{
public:
    MPU6050(TwoWire &w, int i2cAddress = MPU_ADDRESS);

    // Setup method
    void initialize(int speed = I2C_SPEED_100K);
    void baseInititalize(void);
    uint8_t readRegister(uint8_t reg);
    bool isAvailable(void);

    void readRawTemp(void);
    void readRawGyro(void);
    void readRawAcc(void);
    void readRawAll(void);
    void readConfig(void);
    void writeRegister(uint8_t reg, uint8_t data);

    int16_t GetRawAccX() { return rawAccX; };
    int16_t GetRawAccY() { return rawAccY; };
    int16_t GetRawAccZ() { return rawAccZ; };
    int16_t GetRawGyroX() { return rawGyroX; };
    int16_t GetRawGyroY() { return rawGyroY; };
    int16_t GetRawGyroZ() { return rawGyroZ; };
    int16_t GetRawTemp() { return rawTemp; };

    uint8_t Get_SMPLRT_DIV() { return SMPLRT_DIV_val; };
    uint8_t Get_CONFIG() { return CONFIG_val; };
    uint8_t Get_GYRO_CONFIG() { return GYRO_CONFIG_val; };
    uint8_t Get_ACCEL_CONFIG() { return ACCEL_CONFIG_val; };
    uint8_t Get_PWR_MGMT_1() { return PWR_MGMT_1_val; };

    void updateGyroValues(float factor);
    void updateAccValues(float factor);

    float GetAccX() { return accX; };
    float GetAccY() { return accY; };
    float GetAccZ() { return accZ; };
    float GetGyroX() { return gyroX; };
    float GetGyroY() { return gyroY; };
    float GetGyroZ() { return gyroZ; };
    float GetTemp() { return temp; };

    void setGyroOffset(int16_t x, int16_t y, int16_t z);
    void setAccOffset(int16_t x, int16_t y, int16_t z);
    void discard(void);
    void calibration(void);

    int16_t offsetAccX, offsetAccY, offsetAccZ, offsetGyroX, offsetGyroY, offsetGyroZ;

private:
    // I??C stuff
    TwoWire *wire;
    int address;

    int who_am_i;
    int16_t rawAccX, rawAccY, rawAccZ, rawGyroX, rawGyroY, rawGyroZ, rawTemp;
    float accX, accY, accZ, gyroX, gyroY, gyroZ, temp;

    uint8_t SMPLRT_DIV_val, CONFIG_val, GYRO_CONFIG_val, ACCEL_CONFIG_val, PWR_MGMT_1_val;
};

#endif