/*
    Arduino Library for MPU-6050 IMU
    Copyright (c) 2021 Sameera

*/

#include <MPU6050.h>

MPU6050 IMU (Wire);

char buff[50];

void setup() {
  IMU.initialize(I2C_SPEED_400K);
  Serial.begin(115200);

  if (IMU.isAvailable()) {
    Serial.println("IMU OK");
  } else {
    Serial.println("No IMU");
  }
  Serial.println("AX\tAY\tAZ\tgX\tgY\tgZ\tTemp");
}

void loop() {
  //  IMU.readRawGyro();
  //  IMU.readRawAcc();
  //  IMU.readRawTemp();
  IMU.readRawAll();

  sprintf(buff, "%d\t%d\t%d\t%d\t%d\t%d\t%d", IMU.GetRawAccX(), IMU.GetRawAccY(), IMU.GetRawAccZ(), IMU.GetRawGyroX(), IMU.GetRawGyroY(), IMU.GetRawGyroZ(), IMU.GetRawTemp());
  Serial.println(buff);
  delay(20);

}
