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
int putar, motor;

#define MotorInterfaceType 8
AccelStepper stepper = AccelStepper(MotorInterfaceType, MP1, MP3, MP2, MP4);
const int SPR = 10.24;

void setup() {
  Serial.begin(115200);
  pinMode(pinPir, INPUT);
  loadData();
  stepper.setMaxSpeed(1000);//kecepatan maximum
  stepper.setAcceleration(200);//Set the maximum acceleration in steps per second^2
}

void loop() {
  checkSensor();
}
void checkSensor() {
  kondisi = digitalRead(pinPir);

  if (kondisi == 0) {
    //motor gerak
    if (putar == 0) { //putar kanan
      if (motor == 180) {
        putar = 1;
        return;
      }
      motor += SPR;
      stepper.move(SPR);
      stepper.runToPosition();
    }
    else { //putar kiri
      if (motor == 0) {
        putar = 0;
        return;
      }
      motor -= SPR;
      stepper.move(-1 * SPR);
      stepper.runToPosition();
    }
    saveData();
  }

  else {
    Serial.println("asd");
  }
}

void saveData() {
  int addres;
  dataMotor save = {
    putar,
    motor
  };
  Serial.print("arah putaran motor:");
  Serial.println(putar);
  Serial.print("sudut update:");
  Serial.println(motor);
  Serial.println("save sukses");
  EEPROM.put(addres, save);

}

void loadData() {
  int addres;
  dataMotor load;
  EEPROM.get(addres, load);
  putar = load.arahPutar;
  motor = load.posisiMotor;
  Serial.print("arah putaran motor:");
  Serial.println(putar);
  Serial.print("sudut terakhir:");
  Serial.println(motor);

}
