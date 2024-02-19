#include <Arduino.h>
#include <Wire.h>
#include "MPU9250.h"

#define POLLING_RATE_50_HZ 19
#define POLLING_DELAY 20

#define ACTUATOR_PIN 8

MPU9250 IMU(Wire, 0x68);
int status;

void SoundBuzzer();

void setup()
{
  Serial.begin(9600);
  status = IMU.begin();
  if (status < 0)
  {
    Serial.println("IMU Init failed");
    Serial.print("Status:");
    Serial.println(status);
    while (true)
    {
    }
  }

  pinMode(ACTUATOR_PIN, OUTPUT);

  IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);
  IMU.setSrd(POLLING_RATE_50_HZ);
}

void loop()
{
  IMU.readSensor();

  float z = IMU.getAccelZ_mss();
  Serial.println(z, 6);

  if (z > 1)
  {
    Serial.println("WOO");
    SoundBuzzer();
  }

  delay(POLLING_DELAY);
}

void SoundBuzzer()
{
  for (int i = 0; i < 100; i++)
  {                                   // make a sound
    digitalWrite(ACTUATOR_PIN, HIGH); // send high signal to buzzer
    delay(1);                         // delay 1ms
    digitalWrite(ACTUATOR_PIN, LOW);  // send low signal to buzzer
    delay(1);
  }
  delay(50);
  for (int j = 0; j < 100; j++)
  { // make another sound
    digitalWrite(ACTUATOR_PIN, HIGH);
    delay(2); // delay 2ms
    digitalWrite(ACTUATOR_PIN, LOW);
    delay(2);
  }
  delay(500);
}