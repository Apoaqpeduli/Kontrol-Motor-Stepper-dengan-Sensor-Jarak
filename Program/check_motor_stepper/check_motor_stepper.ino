#include <AccelStepper.h>

#define MP1  8
#define MP2  9
#define MP3  10
#define MP4  11

#define MotorInterfaceType 8
AccelStepper stepper = AccelStepper(MotorInterfaceType, MP1, MP3, MP2, MP4);
const int SPR = 2048;//360
//const int SPR = 1024;//180
//const int SPR = 512;//90
//const int SPR = 256; //45
//const int SPR = 128;//22.5

void setup() {
  stepper.setMaxSpeed(1000);//kecepatan maximum
  stepper.setAcceleration(200);//Set the maximum acceleration in steps per second^2
}

void loop() {
  for (int a = 0; a <= 100; a ++) {
    stepper.moveTo(SPR);
    stepper.runToPosition();
    delay(1000);
  }

  for (int a = 0; a <= 100; a ++) {
    stepper.moveTo(-1*SPR);
    stepper.runToPosition();
    delay(1000);
  }

  
}
