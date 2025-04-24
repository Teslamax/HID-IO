// Contents of usb_desc.h
#pragma once

#define USB_VID           0xCAFE
#define USB_PID           0x4000
#define USB_MANUFACTURER  "hid-io"
#define USB_PRODUCT       "RGB Composite Dongle"
#define USB_SERIAL        "HIDIO-001"

// TinyUSB configuration macros for composite device
#define CFG_TUD_HID        2  // Gamepad IN + RGB OUT
#define CFG_TUD_CDC        1
#define CFG_TUD_COMPOSITE  1
