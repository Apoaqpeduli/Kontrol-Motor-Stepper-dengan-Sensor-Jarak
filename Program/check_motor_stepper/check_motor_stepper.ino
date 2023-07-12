#include <AccelStepper.h> 

#define MP1  8 
#define MP2  9
#define MP3  10
#define MP4  11

#define MotorInterfaceType 8 
AccelStepper stepper = AccelStepper(MotorInterfaceType, MP1, MP3, MP2, MP4);
const int SPR = 2048;//Steps per revolution

void setup() {
  stepper.setMaxSpeed(1000);//kecepatan maximum 
  stepper.setAcceleration(200);//Set the maximum acceleration in steps per second^2
}

void loop() {
  stepper.moveTo(3*SPR); 
  stepper.runToPosition();
  delay(1000);
  stepper.moveTo(-3*SPR);
  stepper.runToPosition();
  delay(1000);
}
