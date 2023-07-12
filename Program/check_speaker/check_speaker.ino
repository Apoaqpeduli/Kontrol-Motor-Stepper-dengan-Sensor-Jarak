#define pinSpeaker 12

void setup() {
  Serial.begin(115200);
  pinMode(pinSpeaker, OUTPUT);
}

void loop() {
  digitalWrite(pinSpeaker, HIGH);
  delay(1000);
  digitalWrite(pinSpeaker, LOW);
  delay(1000);
}
