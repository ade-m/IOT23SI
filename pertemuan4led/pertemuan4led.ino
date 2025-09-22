#define LED_MERAH  21
#define LED_KUNING 22
#define LED_HIJAU  23

void setup() {
  pinMode(LED_MERAH, OUTPUT);
  pinMode(LED_KUNING, OUTPUT);
  pinMode(LED_HIJAU, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // Lampu Merah
  digitalWrite(LED_MERAH, HIGH);
  digitalWrite(LED_KUNING, LOW);
  digitalWrite(LED_HIJAU, LOW);
  Serial.println("Merah - STOP");
  delay(1000);

  // Lampu Hijau
  digitalWrite(LED_MERAH, LOW);
  digitalWrite(LED_KUNING, LOW);
  digitalWrite(LED_HIJAU, HIGH);
  Serial.println("Hijau - JALAN");
  delay(1000);

  // Lampu Kuning
  digitalWrite(LED_MERAH, LOW);
  digitalWrite(LED_KUNING, HIGH);
  digitalWrite(LED_HIJAU, LOW);
  Serial.println("Kuning - SIAP");
  delay(1000);
}
