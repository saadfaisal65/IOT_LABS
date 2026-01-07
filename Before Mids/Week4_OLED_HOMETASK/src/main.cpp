#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---- OLED setup ----
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Wire.begin(21, 22); // ESP32 default I2C pins (SDA=21, SCL=22)
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    // If it fails, check wiring and address (0x3C/0x3D)
    for (;;);
  }
  display.clearDisplay();
}

void loop() {
  // Display diagonal lines
  display.clearDisplay();
  display.drawLine(0, 0, 127, 63, SSD1306_WHITE);
  display.drawLine(0, 63, 127, 0, SSD1306_WHITE);
  display.display();
  delay(2000);
  
  // Display "Hello AI"
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(1, 5);
  display.println("Hello");
  display.setTextSize(2);
  display.setCursor(20, 26);
  display.println("AI");
  display.display();
  delay(2000);
  
  // Display Name and ID with box
  display.clearDisplay();
  
  // Draw rectangle border
  display.drawRect(10, 15, 108, 35, SSD1306_WHITE);
  
  // Display Name
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(30, 20);
  display.println("Saad");
  
  // Display ID
  display.setTextSize(1);
  display.setCursor(38, 38);
  display.println("ID: 1281");
  
  display.display();
  delay(2000);
}