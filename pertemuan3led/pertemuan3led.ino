#define led 5
#define led2 23

void setup() {
  Serial.begin(115200);
  Serial.println("IoT Telegram kendali LED");
  pinMode(led, OUTPUT); 
  pinMode(led2, OUTPUT); 
}

void loop() {
  digitalWrite(led, HIGH);
  digitalWrite(led2, LOW);
  Serial.println("LED ON");
  delay(1000);

  digitalWrite(led, LOW);
  digitalWrite(led2, HIGH);
  Serial.println("LED OFF");
  delay(1000);
}
