#include <AccelStepper.h>
#include <EEPROM.h>

struct dataMotor {
  int arahPutar;
  float posisiMotor;
};

#define MP1  8
#define MP2  9
#define MP3  10
#define MP4  11

#define pinPir 2
int kondisi;
int putar=0, motor;

#define MotorInterfaceType 8
AccelStepper stepper = AccelStepper(MotorInterfaceType, MP1, MP3, MP2, MP4);
const int SPR = 10.24;

void setup() {
  Serial.begin(115200);
 
  stepper.setMaxSpeed(1000);//kecepatan maximum
  stepper.setAcceleration(200);//Set the maximum acceleration in steps per second^2
}

void loop() {
  checkSensor();
}
void checkSensor() {
    if (putar == 0) { //putar kanan
      if (motor == 1024) {
        putar = 1;
        return;
      }
      Serial.println("kiri");
      motor += SPR;
      stepper.moveTo(motor);
      stepper.runToPosition();
    }
    else { //putar kiri
      if (motor == 0) {
        putar = 0;
        return;
      }
      Serial.println("kanan");
      motor -= SPR;
      stepper.moveTo(motor);
      stepper.runToPosition();
    }
    Serial.println(motor);
    delay(1000);
    
}
