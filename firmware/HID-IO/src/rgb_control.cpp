// Contents of rgb_control.cpp

#include "rgb_control.h"
#include <Arduino.h>

// RGB LED pins (active LOW)
#define LED_RED_PIN    23  // P0.23
#define LED_GREEN_PIN  22  // P0.22
#define LED_BLUE_PIN   24  // P0.24

static uint8_t brightness = 255;
static uint8_t base_r = 0, base_g = 0, base_b = 0;
static uint8_t mode = 0;  // 0 = static, 1 = blink, 2 = breathe
static uint32_t last_update = 0;
static uint32_t effect_interval = 500;
static bool effect_toggle = false;

void rgb_init() {
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
  rgb_off();
}

void rgb_set(uint8_t r, uint8_t g, uint8_t b) {
  base_r = r;
  base_g = g;
  base_b = b;
  mode = 0;  // Static mode

  digitalWrite(LED_RED_PIN,   (r * brightness / 255) ? LOW : HIGH);
  digitalWrite(LED_GREEN_PIN, (g * brightness / 255) ? LOW : HIGH);
  digitalWrite(LED_BLUE_PIN,  (b * brightness / 255) ? LOW : HIGH);
}

void rgb_off() {
  base_r = base_g = base_b = 0;
  mode = 0;
  digitalWrite(LED_RED_PIN,   HIGH);
  digitalWrite(LED_GREEN_PIN, HIGH);
  digitalWrite(LED_BLUE_PIN,  HIGH);
}

void rgb_set_brightness(uint8_t level) {
  brightness = level;
  rgb_set(base_r, base_g, base_b);
}

void rgb_blink(uint8_t r, uint8_t g, uint8_t b, uint32_t interval_ms) {
  base_r = r;
  base_g = g;
  base_b = b;
  effect_interval = interval_ms;
  mode = 1;  // Blink mode
  last_update = millis();
}

void rgb_breathe(uint8_t r, uint8_t g, uint8_t b, uint32_t cycle_ms) {
  base_r = r;
  base_g = g;
  base_b = b;
  effect_interval = cycle_ms;
  mode = 2;  // Breathe mode
  last_update = millis();
}

void rgb_loop() {
  uint32_t now = millis();

  if (mode == 1 && now - last_update >= effect_interval) {  // Blink
    effect_toggle = !effect_toggle;
    last_update = now;
    if (effect_toggle) {
      digitalWrite(LED_RED_PIN,   (base_r * brightness / 255) ? LOW : HIGH);
      digitalWrite(LED_GREEN_PIN, (base_g * brightness / 255) ? LOW : HIGH);
      digitalWrite(LED_BLUE_PIN,  (base_b * brightness / 255) ? LOW : HIGH);
    } else {
      digitalWrite(LED_RED_PIN,   HIGH);
      digitalWrite(LED_GREEN_PIN, HIGH);
      digitalWrite(LED_BLUE_PIN,  HIGH);
    }
  } else if (mode == 2) {  // Breathe
    float phase = (now % effect_interval) / (float)effect_interval;
    float fade = 0.5f * (1.0f - cos(2 * PI * phase));  // cosine fade
    uint8_t scaled = (uint8_t)(brightness * fade);
    digitalWrite(LED_RED_PIN,   (base_r * scaled / 255) ? LOW : HIGH);
    digitalWrite(LED_GREEN_PIN, (base_g * scaled / 255) ? LOW : HIGH);
    digitalWrite(LED_BLUE_PIN,  (base_b * scaled / 255) ? LOW : HIGH);
  }
}
