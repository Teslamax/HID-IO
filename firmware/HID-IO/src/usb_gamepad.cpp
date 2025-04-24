// Contents of usb_gamepad.cpp

#include "usb_gamepad.h"
#include "usb_hid_report_desc.h"
#include "tusb.h"
#include <Arduino.h>

#define GAMEPAD_BUTTON_PIN 18  // P0.18 = USER/RESET button on dongle

static bool gamepad_state = false;

void usb_gamepad_setup() {
  pinMode(GAMEPAD_BUTTON_PIN, INPUT_PULLUP);  // Initialize physical button input
}

void usb_gamepad_loop() {
  static bool prev_state = false;
  bool current_state = digitalRead(GAMEPAD_BUTTON_PIN) == LOW;

  if (current_state != prev_state && tud_hid_ready()) {
    uint8_t report[2] = { 0 };
    report[0] = current_state ? 0x01 : 0x00;  // Button 1 pressed or released
    tud_hid_report(REPORT_ID_GAMEPAD, report, sizeof(report));
  }
  prev_state = current_state;
}
