#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Posisi bola mata
int leftEyeX = 40, leftEyeY = 32;
int rightEyeX = 88, rightEyeY = 32;
int eyeRadius = 20;
int pupilRadius = 6;

// Posisi pupil
int offsetX = 0, offsetY = 0;
int dirX = 1, dirY = 1;

// Ekspresi: 0=normal, 1=ngantuk, 2=kaget, 3=senang
int expression = 0;
unsigned long lastChange = 0;

void setup() {
  Wire.begin(21, 22);
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
}

void loop() {
  display.clearDisplay();

  // Ganti ekspresi tiap 5 detik
  if (millis() - lastChange > 1000) {
    expression = random(0, 4);
    lastChange = millis();
  }

  switch (expression) {
    case 0: drawNormalEyes(); break;
    case 1: drawSleepyEyes(); break;
    case 2: drawSurprisedEyes(); break;
    case 3: drawHappyEyes(); break;
  }

  display.display();
  delay(50);
}

// ===== Mode Normal (pupil gerak) =====
void drawNormalEyes() {
  // Bola mata
  display.drawCircle(leftEyeX, leftEyeY, eyeRadius, SSD1306_WHITE);
  display.drawCircle(rightEyeX, rightEyeY, eyeRadius, SSD1306_WHITE);

  // Gerak pupil
  offsetX += dirX;
  offsetY += dirY;
  if (offsetX > 6 || offsetX < -6) dirX = -dirX;
  if (offsetY > 4 || offsetY < -4) dirY = -dirY;

  // Pupil kiri & kanan
  display.fillCircle(leftEyeX + offsetX, leftEyeY + offsetY, pupilRadius, SSD1306_WHITE);
  display.fillCircle(rightEyeX + offsetX, rightEyeY + offsetY, pupilRadius, SSD1306_WHITE);
}

// ===== Mode Ngantuk =====
void drawSleepyEyes() {
  display.drawLine(leftEyeX - eyeRadius, leftEyeY, leftEyeX + eyeRadius, leftEyeY, SSD1306_WHITE);
  display.drawLine(rightEyeX - eyeRadius, rightEyeY, rightEyeX + eyeRadius, rightEyeY, SSD1306_WHITE);
}

// ===== Mode Kaget =====
void drawSurprisedEyes() {
  display.drawCircle(leftEyeX, leftEyeY, eyeRadius, SSD1306_WHITE);
  display.drawCircle(rightEyeX, rightEyeY, eyeRadius, SSD1306_WHITE);

  // pupil kecil
  display.fillCircle(leftEyeX, leftEyeY, 3, SSD1306_WHITE);
  display.fillCircle(rightEyeX, rightEyeY, 3, SSD1306_WHITE);
}

// ===== Mode Senang =====
void drawHappyEyes() {
  // lengkung bawah (mata senyum)
  display.drawCircleHelper(leftEyeX, leftEyeY, eyeRadius, 0b1100, SSD1306_WHITE);
  display.drawCircleHelper(rightEyeX, rightEyeY, eyeRadius, 0b1100, SSD1306_WHITE);
}

