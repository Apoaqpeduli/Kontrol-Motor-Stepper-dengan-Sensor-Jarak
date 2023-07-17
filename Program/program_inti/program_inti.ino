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

#define MotorInterfaceType 8
AccelStepper stepper = AccelStepper(MotorInterfaceType, MP1, MP3, MP2, MP4);

float SPR = 10.24; //1.8'

int putar;
float sudut;
int kondisi;


void setup() {
  Serial.begin(115200);
  pinMode(pinPir,INPUT);
  loadData();
  stepper.setCurrentPosition(sudut);
  stepper.setMaxSpeed(1000);//kecepatan maximum
  stepper.setAcceleration(200);//Set the maximum acceleration in steps per second^2
}

void loop() {
  checkKeadaan();
  if(kondisi==0){
    Serial.println("tidak ada halangan");
    return;
  }
  motorjalan();
}

void checkKeadaan(){
  kondisi=digitalRead(pinPir);
  Serial.println(kondisi);
}

void motorjalan(){
  
  if(putar==0){
    if(sudut>=1024){
      putar=1;
      return;
    }
    sudut+=SPR;
    Serial.print("kanan:");
    Serial.println(sudut);
    stepper.moveTo(sudut);
    stepper.runToPosition();
  }

  else{
    if(sudut<=0){
      putar=0;
      return;
    }
    sudut-=SPR;
    Serial.print("kiri:");
    Serial.println(sudut);
    stepper.moveTo(sudut);
    stepper.runToPosition();
  }
  saveData();
}

void loadData(){
  int addres;
  dataMotor load;
  EEPROM.get(addres, load);
  putar = load.arahPutar;
  sudut = load.posisiMotor;
  Serial.print("arah putaran motor:");
  Serial.println(putar);
  Serial.print("sudut terakhir:");
  Serial.println(sudut);
}

void saveData() {
  int addres;
  dataMotor save = {
    putar,
    sudut
  };
  Serial.print("arah putaran motor:");
  Serial.println(putar);
  Serial.print("sudut update:");
  Serial.println(sudut);
  Serial.println("save sukses");
  EEPROM.put(addres, save);
}
