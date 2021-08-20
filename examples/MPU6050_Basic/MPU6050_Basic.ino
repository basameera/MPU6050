#include <MPU6050.h>

MPU6050 IMU (Wire);

long tm;
char buff[50];

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

int data;

void loop() {
  IMU.readRawGyro();
  sprintf(buff, "%d\t%d\t%d", IMU.GetRawGyroX(), IMU.GetRawGyroY(), IMU.GetRawGyroZ());
  Serial.println(buff);
  delay(50);

}
