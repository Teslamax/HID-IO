# HID-IO

**HID-IO** is a USB-based I/O interface for headless systems (like Raspberry Pi), providing a simple **pushbutton input** and a fully-controllable **RGB status LED** over a **composite USB HID + CDC interface**.

- [nRF52840 MDK USB Dongle](https://wiki.makerdiary.com/nrf52840-mdk-usb-dongle/) ([Nordic Semiconductor nRF52840](https://www.nordicsemi.com/Products/nRF52840))

It is designed for service monitoring, status indication, and user interaction in environments where GPIO access is unavailable or undesirable.

---

## ✨ Features

- 🔘 **HID input**: Button exposed as a standard USB HID input (ideal for udev, evdev, or event-loop tools)
- 🌈 **HID output**: RGB LED controllable via HID OUT report (supports color, blink, breathe, fade, etc.)
- 💬 **CDC serial interface**: For CLI-based control, debugging, logging, or interactive scripting
- 🔧 **Shared command parser**: CDC and HID both invoke a unified backend API
- 🔌 **Plug-and-play**: Fully USB class-compliant (no drivers needed)
- 💡 **Custom VID/PID and product strings** to safely identify the device

---

## 📦 Intended Use Cases

- Status LED for **headless Raspberry Pi**
- Systemd notifier or watchdog indicator
- Remote `systemctl` status display with color feedback
- USB-based **button-triggered restart/reset**
- CLI-controlled RGB signaling tool (via serial or HID)

---

## 🧱 USB Configuration

| Interface | Description                    |
|-----------|--------------------------------|
| HID IN    | Pushbutton input (report ID 1) |
| HID OUT   | RGB LED control (report ID 2)  |
| CDC ACM   | Serial command-line interface  |

### USB Identity

| Field         | Value                        |
|---------------|------------------------------|
| Vendor ID     | `0xCAFE` (DIY/hobbyist)      |
| Product ID    | `0x4000`                     |
| Manufacturer  | `"hid-io"`                   |
| Product       | `"RGB Indicator Dongle"`     |
| Serial        | `"HIDIO-001"`                |

---

## 🔧 Command Set

All commands are supported over both **CDC serial** and **HID OUT** (as structured 8-byte reports).

| Command   | Arguments             | Description                        |
|-----------|-----------------------|------------------------------------|
| `set`     | `R G B`               | Set LED to static color            |
| `blink`   | `R G B COUNT SPEED`   | Blink LED `COUNT` times            |
| `breathe` | `R G B SPEED`         | Continuous breathing effect        |
| `fade`    | `R G B TIME`          | Smooth transition to color         |
| `off`     | *(none)*              | Turn off LED                       |
| `status`  | *(CDC only)*          | Print internal state               |

---

## 🧰 Example Usage (Pi CLI)

**Via CDC (Serial):**
```bash
echo "set 255 0 0" > /dev/ttyACM0        # Static red
echo "blink 255 255 0 3 250" > /dev/ttyACM0  # Blink yellow 3x
```

**Via HID (Python/hidapi):**
```python
import hid
dev = hid.device()
dev.open(0xCAFE, 0x4000)
dev.write([0x02, 0x01, 255, 0, 0, 0, 0, 0])  # Command 1 = set RGB
```

---

## 🛠 Repository Structure

```
hid-io/
├── firmware/              # TinyUSB-based HID+CDC firmware
│   ├── src/
│   ├── platformio.ini     # Build config
│   └── README.md
├── scripts/               # Pi-side CLI tools (Python or shell)
│   ├── hid-send.py        # HID command sender
│   ├── serial-cli.py      # CDC interface tester
├── docs/
│   └── pinout.md
├── LICENSE
└── README.md              # This file
```

---

## 🧠 Future Ideas

- Support for **HID IN report responses** (e.g., status feedback or heartbeat)
- **BLE HID** compatibility
- **Multiple button** support via I2C expander or GPIO mux
- **VIA/OpenRGB** plugin mode

---

## 🧾 License

MIT License. © You.
