---

# T-Beam Supreme Framework

## Introduction

The T-Beam Supreme S3 revision by LilyGo is a comprehensive package, integrating an array of sensor suites with advanced radio communication capabilities. It's designed for versatility, but users may encounter challenges when deviating from its intended use with SoftRF or Meshtastic, particularly during programming through Arduino IDE or PlatformIO.

## Issue Overview

A prevalent issue arises from the recommended configuration for Arduino/PlatformIO, which suggests selecting the "ESP32 S3 Dev Module" as the programming interface. This configuration leads to an error stemming from an improper boot sequence, characterized by an extended grounding of the GPIO0 pin, resulting in the following error message:

```plaintext
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce3808,len:0x44c
load:0x403c9700,len:0xbd8
load:0x403cc700,len:0x2a80
ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0x15 (USB_UART_CHIP_RESET),boot:0x1 (DOWNLOAD(USB/UART0))
Saved PC:0x40045ab3
waiting for download
```

This error can be attributed to either the prolonged grounding of the GPIO0 pin or a delay in releasing the bootstrapping pin GPIO45, likely caused by a capacitor issue as per the ESP32 S3's recommended specifications.

## Resolution

Although the exact reasons behind the successful flashing with Meshastic firmware remain unclear, this enviornment after cloning should allow you to program and upload to the T-Beam Supreme S3. You also must hold down the boot button either on the carrier board or the main board when plugging in the USB-C cable. The system will not restart until you power cycle the T-Beam Supreme S3 board after programming.

## Additional Guidance

For those encountering the "pins_arduino.h" missing error, particularly in relation to the ESP32 EEPROM, a simple file management solution is available. Navigate to your `~/.platformio/packages/framework-arduinoespressif32/cores` directory and place the `pins_arduino.h` file from `~/variants/tbeam-s3-core/` into it.

---
