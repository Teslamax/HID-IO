// Contents of usb_cdc.cpp

#include "usb_cdc.h"
#include "command_parser.h"
#include "usb_desc.h"
#include <Arduino.h>
#include <string.h>

static bool echo_enabled = true;

static String generate_serial_from_ficr() {
  char serial_buf[17];
  snprintf(serial_buf, sizeof(serial_buf), "%08lX%08lX",
           (unsigned long)NRF_FICR->DEVICEID[1],
           (unsigned long)NRF_FICR->DEVICEID[0]);
  return String(serial_buf);
}

void usb_cdc_setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  Serial.println("🟢 CDC CLI ready. Type /help for commands.");
}

void usb_cdc_loop() {
  static char buffer[64];
  static size_t index = 0;

  while (Serial.available()) {
    char c = Serial.read();

    if (echo_enabled) Serial.write(c);

    if (c == '\r' || c == '\n') {
      buffer[index] = '\0';
      if (index > 0) {
        handle_cdc_command(buffer);
        index = 0;
      }
    } else if (index < sizeof(buffer) - 1) {
      buffer[index++] = c;
    }
  }
}

void handle_cdc_command(const char* cmd) {
  if (strcmp(cmd, "/help") == 0) {
    Serial.println("\n🔧 Available commands:");
    Serial.println("  /help        - show this list");
    Serial.println("  /ping        - reply with pong");
    Serial.println("  /uptime      - show millis uptime");
    Serial.println("  /usbinfo     - show USB descriptors");
    Serial.println("  /ficr        - show FICR raw values");
    Serial.println("  /echo on|off - toggle echo");
  } else if (strcmp(cmd, "/ping") == 0) {
    Serial.println("🏓 pong");
  } else if (strcmp(cmd, "/uptime") == 0) {
    Serial.print("⏱️ uptime: ");
    Serial.print(millis());
    Serial.println(" ms");
  } else if (strcmp(cmd, "/usbinfo") == 0) {
    Serial.println("💡 USB Info:");
    Serial.print("  VID: 0x"); Serial.println(USB_VID, HEX);
    Serial.print("  PID: 0x"); Serial.println(USB_PID, HEX);
    Serial.print("  Manufacturer: "); Serial.println(USB_MANUFACTURER);
    Serial.print("  Product: "); Serial.println(USB_PRODUCT);
    Serial.print("  Serial (static): "); Serial.println(USB_SERIAL);
    Serial.print("  Serial (FICR): "); Serial.println(generate_serial_from_ficr());
  } else if (strcmp(cmd, "/ficr") == 0) {
    Serial.println("🧬 FICR DeviceID:");
    Serial.print("  DEVICEID[1]: 0x"); Serial.println((uint32_t)NRF_FICR->DEVICEID[1], HEX);
    Serial.print("  DEVICEID[0]: 0x"); Serial.println((uint32_t)NRF_FICR->DEVICEID[0], HEX);
  } else if (strncmp(cmd, "/echo", 5) == 0) {
    const char* arg = cmd + 6;
    if (strcmp(arg, "on") == 0) {
      echo_enabled = true;
      Serial.println("🔈 echo enabled");
    } else if (strcmp(arg, "off") == 0) {
      echo_enabled = false;
      Serial.println("🔇 echo disabled");
    } else {
      Serial.println("⚠️ usage: /echo on|off");
    }
  } else {
    parse_command(cmd);  // Pass to main parser for RGB, etc.
  }
}
