#include <ESP32Servo.h>

const int trigPin = 26;
const int echoPin = 25;
const int servoPin = 14;

Servo myservo;

int servoClosed = 10; 
int servoOpen   = 90; 

long duration;
float distance;

unsigned long lastChange = 0;
const long debounceDelay = 5000; // minimal 5s antar perubahan
int stateDoor = 0; // 0 = closed, 1 = open

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  myservo.attach(servoPin);
  myservo.write(servoClosed); 
}

float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // cm
  return distance;
}

void loop() {
  float d = getDistance();
  Serial.print("Distance: ");
  Serial.println(d);

  unsigned long now = millis();

  if (d > 0 && d < 20 && stateDoor == 0 && (now - lastChange > debounceDelay)) {
    // objek terdeteksi <20cm, buka pintu
    myservo.write(servoOpen);
    stateDoor = 1;
    lastChange = now;
    Serial.println("Pintu Terbuka");
  } else if (d >= 20 && stateDoor == 1 && (now - lastChange > debounceDelay)) {
    // tidak ada objek, tutup pintu
    myservo.write(servoClosed);
    stateDoor = 0;
    lastChange = now;
    Serial.println("Pintu Tertutup");
  }

  delay(500);
}
