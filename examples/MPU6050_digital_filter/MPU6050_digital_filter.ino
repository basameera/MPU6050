/*
    Arduino Library for MPU-6050 IMU
    Copyright (c) 2021 Sameera

*/

#include <MPU6050.h>
#include <DFilter.h>
#include <util/delay.h>

MPU6050 IMU(Wire);
DFilter GXDF(0.5, 0.3, 0.2);

unsigned long tm;
float gX, gX_df;

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
  


  Serial.println("\ngX\tgX_df");
}

void loop()
{
  //  IMU.readRawGyro();
  //  IMU.readRawAcc();
  //  IMU.readRawTemp();
  IMU.readRawAll();

  IMU.updateGyroValues(G_SSF_1);
  IMU.updateAccValues(A_SSF_1);

  gX = IMU.GetGyroX();
  GXDF.push(gX);
  gX_df = GXDF.update();
  
  Serial.print(gX); Serial.print("\t");
  Serial.println(gX_df);


  _delay_ms(20);
  
  
}
