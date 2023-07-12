#define pinPir 2
int kondisi; //1=ada object dan 0=tidak ada object

void setup() {
  Serial.begin(115200);
  pinMode(pinPir, INPUT);
}

void loop() {
  kondisi=digitalRead(pinPir);
  Serial.print("check kondisi ruangan:");
  Serial.println(kondisi);
  delay(500);
}
