// Contents of usb_gamepad.cpp

#include "usb_gamepad.h"
#include "usb_hid_report_desc.h"
#include "tusb.h"

static bool gamepad_state = false;

void usb_gamepad_loop() {
  static bool prev_state = false;

  // Simulated button input (toggle every call)
  gamepad_state = !gamepad_state;

  if (tud_hid_ready()) {
    uint8_t report[2] = { 0 };
    report[0] = gamepad_state ? 0x01 : 0x00;  // Button 1 pressed or released
    tud_hid_report(REPORT_ID_GAMEPAD, report, sizeof(report));
  }
}

void usb_gamepad_setup() {
  // TODO: Initialize button input and report as gamepad
}

