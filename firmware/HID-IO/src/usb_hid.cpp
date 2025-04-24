// Contents of usb_hid.cpp
#include "usb_hid.h"
#include "usb_hid_report_desc.h"
#include "tusb.h"
#include <stdint.h>

// Composite descriptor buffer
uint8_t const* tud_hid_descriptor_report_cb(uint8_t instance) {
  if (instance == 0) return hid_report_desc_gamepad;
  if (instance == 1) return hid_report_desc_rgbout;
  return NULL;
}

// Handle incoming HID OUT reports
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id,
                           hid_report_type_t report_type,
                           uint8_t const* buffer, uint16_t bufsize) {
  if (instance == 1 && report_type == HID_REPORT_TYPE_OUTPUT && report_id == REPORT_ID_RGB_OUT) {
    // TODO: route to RGB handler (parse_command or RGB API)
  }
}



void usb_hid_setup() {}

