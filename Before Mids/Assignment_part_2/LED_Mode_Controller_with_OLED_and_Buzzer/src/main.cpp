/*
  Project: LED Mode Controller with OLED and Buzzer (PWM Version)
  Name: Saad Faisal
  Reg No: 23-NTU-CS-1281
  Date: 26-Oct-2025
*/

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- Pin definitions ---
#define LED1 19
#define LED2 18
#define LED3 5
#define BTN_MODE 26
#define BTN_RESET 27
#define BUZZER 15

// --- PWM channels ---
#define PWM_LED1   0
#define PWM_LED2   1
#define PWM_LED3   2
#define PWM_BUZZER 3
#define RESOLUTION 8   // 8-bit resolution (0–255)

// --- OLED setup ---
Adafruit_SSD1306 display(128, 64, &Wire, -1);

// --- Global variables ---
int mode = 1;
unsigned long prevMillis = 0;
bool ledState = false;

// --- Display function ---
void showMsg(const String &msg) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 25);
  display.print("Mode: ");
  display.println(msg);
  display.display();
}

// --- Buzzer beep ---
void beepBuzzer(int freq, int dur) {
  ledcWriteTone(PWM_BUZZER, freq);
  delay(dur);
  ledcWrite(PWM_BUZZER, 0); // turn off sound
}

// --- Startup animation ---
void startupAnimation() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(15, 25);
  display.print("Initializing...");
  display.display();

  for (int i = 0; i < 3; i++) {
    ledcWrite(PWM_LED1, 255);
    ledcWrite(PWM_LED2, 0);
    beepBuzzer(700 + (i * 200), 100);
    delay(150);
    ledcWrite(PWM_LED1, 0);
    ledcWrite(PWM_LED2, 255);
    delay(150);
  }

  ledcWrite(PWM_LED1, 0);
  ledcWrite(PWM_LED2, 0);
  showMsg("System Ready!");
  delay(600);
}

void setup() {
  pinMode(BTN_MODE, INPUT_PULLUP);
  pinMode(BTN_RESET, INPUT_PULLUP);

  // --- OLED init ---
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();

  // --- PWM setup ---
  ledcSetup(PWM_LED1, 5000, RESOLUTION);
  ledcAttachPin(LED1, PWM_LED1);

  ledcSetup(PWM_LED2, 5000, RESOLUTION);
  ledcAttachPin(LED2, PWM_LED2);

  ledcSetup(PWM_LED3, 5000, RESOLUTION);
  ledcAttachPin(LED3, PWM_LED3);

  ledcSetup(PWM_BUZZER, 2000, RESOLUTION);
  ledcAttachPin(BUZZER, PWM_BUZZER);

  startupAnimation();
  showMsg("Both OFF");
}

void loop() {
  // --- Mode button ---
  if (digitalRead(BTN_MODE) == LOW) {
    delay(200);
    mode++;
    if (mode > 4) mode = 1;

    switch (mode) {
      case 1:
        ledcWrite(PWM_LED1, 0);
        ledcWrite(PWM_LED2, 0);
        ledcWrite(PWM_LED3, 0);
        showMsg("Both OFF");
        beepBuzzer(800, 120);
        break;

      case 2:
        showMsg("Alternate Blink");
        beepBuzzer(1000, 120);
        break;

      case 3:
        ledcWrite(PWM_LED1, 255);
        ledcWrite(PWM_LED2, 255);
        ledcWrite(PWM_LED3, 0);
        showMsg("Both ON");
        beepBuzzer(1200, 120);
        break;

      case 4:
        showMsg("PWM Fade");
        beepBuzzer(1500, 120);
        break;
    }
  }

  // --- Reset button ---
  if (digitalRead(BTN_RESET) == LOW) {
    delay(200);
    mode = 1;
    ledcWrite(PWM_LED1, 0);
    ledcWrite(PWM_LED2, 0);
    ledcWrite(PWM_LED3, 0);
    showMsg("Reset to OFF");
    beepBuzzer(500, 200);
  }

  // --- Mode 2: Alternate Blink ---
  if (mode == 2) {
    if (millis() - prevMillis >= 500) {
      prevMillis = millis();
      ledState = !ledState;
      ledcWrite(PWM_LED1, ledState ? 255 : 0);
      ledcWrite(PWM_LED2, ledState ? 0 : 255);
    }
  }

  // --- Mode 4: PWM Fade ---
  if (mode == 4) {
    for (int i = 0; i <= 255; i++) {
      ledcWrite(PWM_LED3, i);
      delay(4);
    }
    for (int i = 255; i >= 0; i--) {
      ledcWrite(PWM_LED3, i);
      delay(4);
    }
  }
}
