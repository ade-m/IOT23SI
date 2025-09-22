const int analogPin = 34; // A0 sensor ke GPIO34
const int digitalPin = 25; // D0 sensor ke GPIO25

void setup() {
  Serial.begin(115200);
  pinMode(digitalPin, INPUT);
}

void loop() {
  // Baca nilai analog (0 - 4095 untuk ESP32)
  int nilaiADC = analogRead(analogPin);
  // Mapping ke persen kelembapan
  int kelembapan = map(nilaiADC, 4095, 0, 0, 100);

  // Baca nilai digital (0/1, berdasarkan trimpot modul)
  int statusTanah = digitalRead(digitalPin);

  Serial.print("ADC: ");
  Serial.print(nilaiADC);
  Serial.print(" | Kelembapan: ");
  Serial.print(kelembapan);
  Serial.print("% | Status: ");
  if (statusTanah == LOW) {
    Serial.println("Basah");
  } else {
    Serial.println("Kering");
  }

  delay(1000);
}

