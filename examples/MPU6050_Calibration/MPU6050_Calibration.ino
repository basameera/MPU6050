/*
    Arduino Library for MPU-6050 IMU
    Copyright (c) 2021 Sameera

*/

#include <MPU6050.h>

MPU6050 IMU(Wire);

unsigned long tm;

void setup()
{
  IMU.initialize(I2C_SPEED_400K);
  Serial.begin(115200);

  if (IMU.isAvailable())
  {
    Serial.println("IMU OK");
  }
  else
  {
    Serial.println("No IMU");
  }

  IMU.writeRegister(MPU_PWR_MGMT_1, 0x00);
  IMU.writeRegister(MPU_GYRO_CONFIG, GYRO_FS_SEL_1);
  IMU.writeRegister(MPU_ACCEL_CONFIG, ACC_AFS_SEL_1);

  Serial.println(">>> Calibration started <<<");
  tm = micros();
  IMU.calibration();
  Serial.print(" Time: ");
  Serial.print((micros()-tm)/1000); Serial.println(" ms");
  Serial.print("offsetAccX: "); Serial.println(IMU.offsetAccX);
  Serial.print("offsetAccY: "); Serial.println(IMU.offsetAccY);
  Serial.print("offsetAccZ: "); Serial.println(IMU.offsetAccZ);
  
  Serial.print("offsetGyroX: "); Serial.println(IMU.offsetGyroX);
  Serial.print("offsetGyroY: "); Serial.println(IMU.offsetGyroY);
  Serial.print("offsetGyroZ: "); Serial.println(IMU.offsetGyroZ);
  


  Serial.println("\nAX\tAY\tAZ\tgX\tgY\tgZ");
}

void loop()
{
  //  IMU.readRawGyro();
  //  IMU.readRawAcc();
  //  IMU.readRawTemp();
  IMU.readRawAll();

  IMU.updateGyroValues(G_SSF_1);
  IMU.updateAccValues(A_SSF_1);

  
  Serial.print(IMU.GetAccX()); Serial.print("\t");
  Serial.print(IMU.GetAccY()); Serial.print("\t");
  Serial.print(IMU.GetAccZ()); Serial.print("\t");
  Serial.print(IMU.GetGyroX()); Serial.print("\t");
  Serial.print(IMU.GetGyroY()); Serial.print("\t");
  Serial.println(IMU.GetGyroZ());


  delay(20);
  
  
}
