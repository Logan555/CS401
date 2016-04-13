#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include<Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 bno = Adafruit_BNO055(0x28);
Adafruit_MotorShield shield1 = Adafruit_MotorShield(0x60);
Adafruit_StepperMotor *stepper1 = shield1.getStepper(200, 1);
Adafruit_StepperMotor *stepper2 = shield1.getStepper(200, 2);
imu::Vector<3> vector1{0,0,0};
void setup() {
  shield1.begin();
  stepper1->setSpeed(50);
  stepper2->setSpeed(50);
  bno.setExtCrystalUse(true);
}
void loop() {
    imu::Vector<3> vector2 = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    int v1x = vector1.x;
    int v2x = vector2.x;
    int v1z = vector1.z;
    int v2z = vector2.z;
    if(v1x != v2x){
        if(v1x > v2x){
            for(int i = 0; i < 5*(v1x-v2x)/9; i++){
                stepper1->step(1, FORWARD, DOUBLE);
              }
        }
          else{
            for(int i = 0; i < 5*(v2x-v1x)/9; i++){
                stepper1->step(1, BACKWARD, DOUBLE);
              }
          }
      }
       if(v1z != v2z){
        if(v1z > v2z){
            for(int i = 0; i < 5*(v1z-v2z)/9; i++){
                stepper1->step(1, FORWARD, DOUBLE);
              }
        }
          else{
            for(int i = 0; i < 5*(v2z-v1z)/9; i++){
                stepper1->step(1, BACKWARD, DOUBLE);
              }
          }
        }
        vector1 = vector2;
        delay(BNO055_SAMPLERATE_DELAY_MS);
}
