// Contents of usb_hid_report_desc.h
#pragma once

// Report ID definitions
#define REPORT_ID_GAMEPAD   0x01
#define REPORT_ID_RGB_OUT   0x02

// Gamepad report descriptor (1 button)
const uint8_t hid_report_desc_gamepad[] = {
  0x05, 0x01,       // Usage Page (Generic Desktop)
  0x09, 0x05,       // Usage (Game Pad)
  0xA1, 0x01,       // Collection (Application)
  0x85, REPORT_ID_GAMEPAD, //   Report ID
  0x05, 0x09,       //   Usage Page (Buttons)
  0x19, 0x01,       //   Usage Minimum (Button 1)
  0x29, 0x01,       //   Usage Maximum (Button 1)
  0x15, 0x00,       //   Logical Minimum (0)
  0x25, 0x01,       //   Logical Maximum (1)
  0x95, 0x01,       //   Report Count (1)
  0x75, 0x01,       //   Report Size (1)
  0x81, 0x02,       //   Input (Data, Var, Abs)
  0x95, 0x01,       //   Report Count (1) - padding
  0x75, 0x07,       //   Report Size (7 bits)
  0x81, 0x03,       //   Input (Const, Var, Abs)
  0xC0              // End Collection
};

// RGB HID OUT report descriptor (8-byte vendor-defined)
const uint8_t hid_report_desc_rgbout[] = {
  0x06, 0xFF, 0x00,       // Usage Page (Vendor Defined)
  0x09, 0x01,             // Usage (Vendor Usage 1)
  0xA1, 0x01,             // Collection (Application)
  0x85, REPORT_ID_RGB_OUT,//   Report ID
  0x95, 0x08,             //   Report Count (8)
  0x75, 0x08,             //   Report Size (8 bits)
  0x15, 0x00,             //   Logical Minimum (0)
  0x26, 0xFF, 0x00,       //   Logical Maximum (255)
  0x91, 0x02,             //   Output (Data, Var, Abs)
  0xC0                    // End Collection
};
