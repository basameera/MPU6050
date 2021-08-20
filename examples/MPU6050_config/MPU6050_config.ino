/*
    Arduino Library for MPU-6050 IMU
    Copyright (c) 2021 Sameera

*/
#include <MPU6050.h>

MPU6050 IMU (Wire);

long tm;
char buff[50];

void setup() {
  IMU.initialize(I2C_SPEED_400K);
  Serial.begin(115200);

  if (IMU.isAvailable()) {
    Serial.println("IMU OK");
  } else {
    Serial.println("No IMU");
  }

  IMU.writeRegister(MPU_PWR_MGMT_1, 0x00);
  IMU.writeRegister(MPU_GYRO_CONFIG, GYRO_FS_SEL_1);
  IMU.writeRegister(MPU_ACCEL_CONFIG, ACC_AFS_SEL_1);

  IMU.readConfig();


  Serial.println("\n--- Config ---");
  Serial.print("SMPLRT_DIV\t: ");   Serial.println(IMU.Get_SMPLRT_DIV(), HEX);
  Serial.print("CONFIG\t\t: ");   Serial.println(IMU.Get_CONFIG(), HEX);
  Serial.print("GYRO_CONFIG\t: ");   Serial.println(IMU.Get_GYRO_CONFIG(), HEX);
  Serial.print("ACCEL_CONFIG\t: ");   Serial.println(IMU.Get_ACCEL_CONFIG(), HEX);
  Serial.print("PWR_MGMT_1\t: ");   Serial.println(IMU.Get_PWR_MGMT_1(), HEX);
  Serial.println("--- Config ---\n");
}

void loop() {

}
