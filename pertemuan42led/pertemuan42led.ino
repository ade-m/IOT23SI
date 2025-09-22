#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C  // biasanya 0x3C, kalau tidak tampil coba ganti 0x3D

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Wire.begin(21, 22);   // SDA=21, SCL=22
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();

  // Teks sederhana
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.println(F("Halo, SSD1315!"));
  display.display();
  delay(2000);

  // Gambar kotak
  display.clearDisplay();
  display.drawRect(10, 10, 50, 30, SSD1306_WHITE);
  display.display();
  delay(2000);
}

void loop() {
  // Counter berjalan
  static int counter = 0;
  display.clearDisplay();
  display.setCursor(0, 20);
  display.setTextSize(2);
  display.print("Hitung Mundur: ");
  display.print(counter);
  display.display();
  counter++;
  delay(1000);
}
