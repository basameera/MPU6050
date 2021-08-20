#include <MPU6050.h>

MPU6050 IMU (Wire);

long tm;

void setup() {
  IMU.Initialize(I2C_SPEED_400K);
  Serial.begin(115200);

  tm = micros();
  
  Serial.println(micros()-tm);
  
  if (IMU.isAvailable()){
    Serial.println("IMU OK");
  } else {
    Serial.println("No IMU");
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  IMU.blink();
}
