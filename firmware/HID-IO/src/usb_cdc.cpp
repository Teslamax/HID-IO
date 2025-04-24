#include "usb_cdc.h"

void usb_cdc_setup() {
  Serial.begin(115200);
}

void usb_cdc_loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    // TODO: Parse command and call RGB control
  }
}
