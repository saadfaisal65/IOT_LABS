#include <Arduino.h>

#define LED1_PIN     19
#define LED2_PIN     18
#define BUZZER_PIN   27
#define PWM_BUZZER   0      // PWM channel for buzzer
#define PWM_LED1     1
#define PWM_LED2     2
#define RESOLUTION   8      // 8-bit resolution (0–255)

// Super Mario melody (intro only)
int melody[] = {
  660, 660, 0, 660, 0, 520, 660, 0,
  440, 0, 0, 520, 0, 440, 0,
  349, 0, 392, 0, 440, 0, 349, 0,
  392, 0, 440, 0, 330, 0, 0, 0,
  660, 0, 660, 0, 660, 0, 0, 0,
  520, 0, 660, 0, 440, 0, 0, 0,
  349, 0, 392, 0, 440, 0, 0, 0
};

int noteDurations[] = {
  100, 100, 100, 100, 100, 100, 100, 100,
  100, 100, 100, 100, 100, 100, 100,
  100, 100, 100, 100, 100, 100, 100, 100,
  100, 100, 100, 100, 100, 100, 100, 100,
  100, 100, 100, 100, 100, 100, 100, 100,
  100, 100, 100, 100, 100, 100, 100, 100,
  100, 100, 100, 100, 100, 100, 100, 100
};

int numNotes = sizeof(melody) / sizeof(melody[0]);

void setup() {
  // Setup PWM for LEDs
  ledcSetup(PWM_LED1, 5000, RESOLUTION);
  ledcAttachPin(LED1_PIN, PWM_LED1);
  
  ledcSetup(PWM_LED2, 5000, RESOLUTION);
  ledcAttachPin(LED2_PIN, PWM_LED2);
  
  // Setup PWM for buzzer
  ledcSetup(PWM_BUZZER, 2000, RESOLUTION);
  ledcAttachPin(BUZZER_PIN, PWM_BUZZER);
}

void loop() {
  for (int i = 0; i < numNotes; i++) {
    int freq = melody[i];
    int duration = noteDurations[i];
    
    // Play tone
    if (freq == 0) {
      ledcWrite(PWM_BUZZER, 0); // silence
    } else {
      ledcWriteTone(PWM_BUZZER, freq);
    }
    
    // LED behavior: brightness proportional to frequency
    int brightness = map(freq, 300, 1000, 50, 255);
    brightness = constrain(brightness, 0, 255);
    
    // Flash LED1 and LED2 alternately with different brightness
    ledcWrite(PWM_LED1, (i % 2 == 0) ? brightness : brightness / 2);
    ledcWrite(PWM_LED2, (i % 2 == 1) ? brightness : brightness / 2);
    
    delay(duration);
    
    // Turn off sound and LEDs briefly between notes
    ledcWrite(PWM_BUZZER, 0);
    ledcWrite(PWM_LED1, 0);
    ledcWrite(PWM_LED2, 0);
    delay(20);
  }
  
  delay(1000); // Pause before repeating melody
}