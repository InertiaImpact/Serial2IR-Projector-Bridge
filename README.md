# Serial2IR-Projector-Bridge

This project bridges an RS-232 control interface to an IR emitter, allowing devices like the Liberty AV DL-UHDILC HDMI controller to control an Epson PowerLite 1286 projector via infrared.

## Purpose

This setup enables automation of projector power control in environments like conference rooms and Microsoft Teams Rooms (MTR). For example:

- Simply plugging in an HDMI device (e.g. a laptop) can automatically turn on the projector.
- In a Teams Room setup, the **MTR control surface** (such as a touch panel) includes a built-in PIR sensor. When someone walks into the room, the MTR wakes up, triggering the DL-UHDILC to send a serial command that powers on the projector — no remote or manual action required.

## Overview

An Arduino Nano receives RS-232 serial commands from the Liberty AV DL-UHDILC room controller. When it detects a control code (`A1` or `A2`), it sends the appropriate IR power command to the Epson projector via an IR LED positioned in front of the projector's IR receiver.

### Key Components

- **Arduino Nano**
  - [Amazon Link](https://www.amazon.com/dp/B0DFGX3MSL)
- **Liberty AV DL-UHDILC**
  - *HDMI In-Line Auto Sensing RS-232 Controller*
  - Part #: DL-UHDILC
- **Projector**
  - Epson PowerLite 1286
- **IR LED**
  - Connected to D3 on the Nano and aimed at the projector's IR receiver

## How It Works

1. The DL-UHDILC sends ASCII serial strings via RS-232:
   - `"A1"` = Power ON
   - `"A2"` = Power OFF
2. The Arduino Nano reads these over hardware Serial (pin 0).
3. It sends NEC-formatted IR commands to the projector using the onboard IR LED.
4. For the power-off command, the signal is sent twice with a 3-second delay in between, matching the projector's expected behavior.

## IR Command Details

- **Protocol:** NEC
- **IR Address:** `0x5583`
- **IR Command:** `0x6F90`
- **Send Pin:** D3
- **Repeat:** No repeat (`false`)

## Notes

- Disconnect the RS-232 RX pin (D0) during sketch upload to avoid interference with the USB serial interface.
- Ensure the IR LED is directly aligned with the projector’s IR receiver.
- This system works entirely without a network or HDMI-CEC, making it a reliable and standalone control solution.
