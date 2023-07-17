#include <AccelStepper.h>
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
struct dataMotor {
  int arahPutar;
  float posisiMotor;
  int langka;
};

#define MP1  8
#define MP2  9
#define MP3  10
#define MP4  11
#define pinPir 2

#define MotorInterfaceType 8
AccelStepper stepper = AccelStepper(MotorInterfaceType, MP1, MP3, MP2, MP4);

float maxStep = 1024.12;
float minStep = -10.12;
int maxSudut = 180;
int minSudut = 0;
int cnt;


float SPR = 10.24; //1.8'

int putar;
float sudut;
int kondisi;
int convertSudut;


void setup() {
  Serial.begin(115200);
  pinMode(pinPir, INPUT);
  loadData();
  lcd.init();
  lcd.backlight();

  stepper.setCurrentPosition(sudut);
  stepper.setMaxSpeed(1000);//kecepatan maximum
  stepper.setAcceleration(200);//Set the maximum acceleration in steps per second^2

  lcd.setCursor(0, 0);
  lcd.print("nama");
  lcd.setCursor(0, 1);
  lcd.print("nim");
  delay(2000);
  lcd.clear();
}

void loop() {
  checkKeadaan();
  if (kondisi == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Diem         ");
    lcd.setCursor(0, 1);
    lcd.print("            ");
    Serial.println("tidak ada halangan");
    return;
  }
  motorjalan();
  tampilanLCD();
}

void checkKeadaan() {
  kondisi = digitalRead(pinPir);
  Serial.println(kondisi);
}

void motorjalan() {
  if (putar == 0) {
    if (sudut >= 1024) {
      putar = 1;
      cnt = 0;
      return;
    }
    cnt += 1;
    sudut += SPR;
    Serial.print("kanan:");
    Serial.println(sudut);
    stepper.moveTo(sudut);
    stepper.runToPosition();
  }

  else {
    if (sudut <= 0) {
      putar = 0;
      cnt = 0;
      return;
    }
    cnt += 1;
    sudut -= SPR;
    Serial.print("kiri:");
    Serial.println(sudut);
    stepper.moveTo(sudut);
    stepper.runToPosition();
  }
  Serial.print("langkah:");
  Serial.println(cnt);
  Serial.print("convertSudut:");
  Serial.println(convertSudut);
  saveData();
}

void loadData() {
  int addres;
  dataMotor load;
  EEPROM.get(addres, load);
  putar = load.arahPutar;
  sudut = load.posisiMotor;
  cnt = load.langka;
  Serial.print("arah putaran motor:");
  Serial.println(putar);
  Serial.print("sudut terakhir:");
  Serial.println(sudut);
}

void saveData() {
  int addres;
  dataMotor save = {
    putar,
    sudut,
    cnt
  };
  Serial.print("arah putaran motor:");
  Serial.println(putar);
  Serial.print("sudut update:");
  Serial.println(sudut);
  Serial.print("langkah update:");
  Serial.println(cnt);
  Serial.println("save sukses");
  EEPROM.put(addres, save);
}

void tampilanLCD() {
  convertSudut = map(sudut, minStep, maxStep, minSudut, maxSudut);
  lcd.setCursor(0, 0);
  lcd.print("Sudut:");
  lcd.print(convertSudut);
  lcd.print("   ");

  if (putar == 0) {
    lcd.setCursor(0, 1);
    lcd.print("Kanan:");
    lcd.print(cnt);
    lcd.print("  ");
  }
  else{
    lcd.setCursor(0, 1);
    lcd.print("Kiri :");
    lcd.print(cnt);
    lcd.print("  ");
  }

}
