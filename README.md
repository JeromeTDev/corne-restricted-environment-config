# Corne Restricted Environment Config

Security-hardened QMK firmware for the Corne v4 (crkbd rev4_0 standard), designed for high-security environments where "on-the-fly" layout changes (VIA/Vial) are prohibited.

## Table of Contents

- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Configuration](#configuration)
- [Building and Flashing](#building-and-flashing)
- [Security Audit](#security-audit)

## Prerequisites

Install the required compilers and QMK CLI:

```bash
# Fedora
sudo dnf install arm-none-eabi-gcc-cs arm-none-eabi-newlib dfu-util git

# Install QMK CLI
uv tool install qmk
qmk setup
```

> Note: Type `Y` when asked to clone the firmware and install udev rules.

## Installation

```bash
# Clone the repository
git clone <your-repo-url>
cd corne-restricted-environment-config

# Create the target directory and symlink to QMK
mkdir -p ~/qmk_firmware/keyboards/crkbd/rev4_0/standard/keymaps/
ln -s "$PWD" ~/qmk_firmware/keyboards/crkbd/rev4_0/standard/keymaps/restricted
```

## Configuration

This setup is optimized for security:

- **rules.mk**: Disables VIA, Vial, and Raw HID to prevent unauthorized memory access.
- **keymap.c**: The physical "source of truth" for your keys.

> Note: Ensure you have the `QK_BOOT` key assigned to a layer to enter flash mode without opening the case.

## Building and Flashing

```bash
chmod +x flash.sh
./flash.sh
```

The script will:
1. Compile the firmware
2. Wait for the keyboard to enter Bootloader Mode
3. Flash the firmware automatically

**Action Required**: Press the Reset button on your Corne v4 twice quickly (or use your `QK_BOOT` key combination).

Repeat for the second half of the keyboard.

### Script Details

The `flash.sh` script is path-independent and automatically locates your QMK home directory.

## Security Audit

To verify what is being installed on your hardware:

1. Check `rules.mk` to ensure `VIAL_ENABLE = no` and `VIA_ENABLE = no`
2. Review `keymap.c` for any unexpected macros
3. Build the firmware and (optionally) check the SHA256 hash of the resulting `.uf2` file
