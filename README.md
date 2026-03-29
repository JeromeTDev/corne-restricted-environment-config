# Corne Restricted Environment Config

Security-hardened QMK firmware for the Corne v4.1 (crkbd rev4_1 standard). This configuration is specifically designed for high-security environments where dynamic memory access (VIA/Vial) and "unidentified" USB devices are prohibited by IT security policies.

## Key Features (Hardcoded)

Unlike standard firmwares, this setup is a **"Static Source of Truth"**:

- **No Dynamic Storage**: VIA, Vial, and Raw HID are completely disabled. Layout changes require a physical re-flash of the firmware.
- **USB Stealth Identity**: The keyboard identifies as a "Generic USB HID Keyboard" to bypass USB whitelists and security scanners.
- **Home Row Combos**: Essential symbols (`[ ] { } ( ) \ | ~ \``) are accessible via simultaneous keypresses on the home row.
- **Shift-Backspace Morph**: Shift + Backspace automatically sends Delete.
- **Mod-Tap Logic**: Tab acts as Control when held, and Tab when tapped.

## Table of Contents

- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Configuration Details](#configuration-details)
- [Combo Reference](#combo-reference)
- [Building and Flashing](#building-and-flashing)
- [Security Audit](#security-audit)

## Prerequisites

Install the required build tools (Example for Fedora):

```bash
sudo dnf install arm-none-eabi-gcc-cs arm-none-eabi-newlib dfu-util git

# Install QMK CLI
uv tool install qmk
qmk setup
```

## Installation

```bash
# Clone the repository
git clone <your-repo-url>
cd corne-restricted-environment-config

# Create a symlink to your QMK firmware directory
ln -s "$PWD" ~/qmk_firmware/keyboards/crkbd/rev4_1/standard/keymaps/restricted
```

## Configuration Details

### 1. Stealth & Security (`config.h`)

- **USB Spoofing**: Uses VendorID `0x04D9` (Holtek) and the product string "USB HID Keyboard".
- **Polling Rate**: Capped at 125Hz (8ms) to mimic standard office peripherals.
- **No Startup Check**: Disables USB startup checks for a faster, more "standard" boot behavior.

### 2. Feature Lockdown (`rules.mk`)

To minimize the attack surface and power consumption:

- `RGB_MATRIX_ENABLE = no` (All LEDs disabled)
- `CONSOLE_ENABLE = no` (No debug data sent over USB)
- `COMMAND_ENABLE = no` (Disables "Magic" boot commands)
- `VIA_ENABLE = no` (Prevents unauthorized layout changes)

## Combo Reference

| Keys (Layer 0) | Result  | Description       |
| -------------- | ------- | ----------------- | ---- |
| J + K          | `ESC`   | Escape            |
| D + F          | `(`     | Left Parenthesis  |
| H + J          | `)`     | Right Parenthesis |
| R + T          | `[`     | Left Bracket      |
| Y + U          | `]`     | Right Bracket     |
| V + B          | `{`     | Left Brace        |
| N + M          | `}`     | Right Brace       |
| . + /          | `\`     | Backslash         |
| / + Shift      | ` | `                 | Pipe |
| L + ;          | `~`     | Tilde             |
| `;` + '        | `` ` `` | Backtick / Grave  |

## Building and Flashing

```bash
# Execute the flash script
chmod +x flashscript.sh
./flashscript.sh
```

**Procedure:**

1. Start the script.
2. Put the Corne v4.1 into Bootloader Mode (double-tap the physical Reset button or use your QK_BOOT key combo).
3. Repeat the process for the second half of the keyboard.

## Security Audit

To verify the firmware's integrity:

1. **Source Check**: Review `rules.mk` to ensure `VIAL_ENABLE` and `VIA_ENABLE` are set to `no`.
2. **Device Identity**: After flashing, the OS will list the device as a "Generic USB HID Keyboard".
3. **Static Analysis**: All macros and combos are hardcoded in `keymap.c`, leaving no writeable user-space memory.

## Final Implementation Tip

Since you are using `L + ;` for Tilde and `; + '` for Grave, make sure your operating system's language matches your keymap expectations. If your PC is set to German (DE), you might need to adjust the specific keycodes (like `ALGR(KC_PLUS)` for Tilde) accordingly.
