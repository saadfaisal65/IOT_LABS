/*
  Project: Button Press Detection (Short / Long Press) - PWM Version
  Name: Saad Faisal
  Reg No: 23-NTU-CS-1281
  Date: 26-Oct-2025
*/

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- Pin Definitions ---
#define BTN       25   // Button pin
#define LED       5    // LED pin
#define BUZZER    18   // Buzzer pin

// --- PWM Channels and Settings ---
#define PWM_LED       0
#define PWM_BUZZER    1
#define LED_FREQ      5000     // 5 kHz for LED
#define BUZZER_FREQ   2000     // start freq for buzzer
#define RESOLUTION    8        // 8-bit PWM (0–255)

// --- OLED Setup ---
Adafruit_SSD1306 display(128, 64, &Wire, -1);

// --- Variables ---
bool ledState = false;
unsigned long pressTime = 0;
bool pressed = false;

// --- OLED Helper Function ---
void showText(const String &msg) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 25);
  display.println(msg);
  display.display();
}

// --- PWM Buzzer Function ---
void beepBuzzer(int freq, int duration) {
  ledcWriteTone(PWM_BUZZER, freq); // play tone
  delay(duration);
  ledcWrite(PWM_BUZZER, 0);        // stop tone
}

// --- Setup Function ---
void setup() {
  pinMode(BTN, INPUT_PULLUP);

  // --- OLED Initialization ---
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  showText("Ready...");

  // --- PWM Setup ---
  ledcSetup(PWM_LED, LED_FREQ, RESOLUTION);
  ledcAttachPin(LED, PWM_LED);

  ledcSetup(PWM_BUZZER, BUZZER_FREQ, RESOLUTION);
  ledcAttachPin(BUZZER, PWM_BUZZER);
}

// --- Main Loop ---
void loop() {
  // --- Button Pressed ---
  if (digitalRead(BTN) == LOW && !pressed) {
    pressed = true;
    pressTime = millis();
  }

  // --- Button Released ---
  if (digitalRead(BTN) == HIGH && pressed) {
    pressed = false;
    unsigned long duration = millis() - pressTime;

    // --- Long Press (>1.5s) ---
    if (duration > 1500) {
      showText("Long Press → Buzzer");
      beepBuzzer(1000, 400); // long beep
    }
    // --- Short Press ---
    else {
      ledState = !ledState;                // toggle LED
      ledcWrite(PWM_LED, ledState ? 255 : 0); // ON/OFF brightness
      showText("Short Press → LED Toggle");
    }
  }
}
