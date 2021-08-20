#include <MPU6050.h>

MPU6050 IMU (Wire);

long tm;

void setup() {
  IMU.Initialize(I2C_SPEED_400K);
  Serial.begin(115200);

  tm = micros();
  IMU.readRegister();
  
  Serial.println(micros()-tm);
  
  if (IMU.who_am_i == MPU_WHO_AM_I_VAL){
    Serial.println("IMU OK");
  } else {
    Serial.println("No IMU");
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  IMU.blink();
}
