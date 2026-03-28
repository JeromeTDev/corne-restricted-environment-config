# corne-restricted-environment-config
This repository contains a hardened, high-compliance firmware configuration for the Corne (Crkbd) split keyboard.

Secure Corne v4 Firmware (Restricted Environment)
This repository contains a security-hardened QMK configuration for the Corne v4 (crkbd rev4_0 standard). It is designed for high-security environments where "on-the-fly" layout changes (VIA/Vial) are prohibited.

1. Prerequisites
Before starting, install the required compilers and the QMK CLI tool.

For Fedora Users:
Bash
sudo dnf install arm-none-eabi-gcc-cs arm-none-eabi-newlib dfu-util git
Install QMK CLI (using uv):
Bash
uv tool install qmk
qmk setup
Note: Type Y when asked to clone the firmware and install udev rules.

2. Installation & Setup
Clone this repository to your preferred development folder and link it to your QMK installation.

Bash
# 1. Clone the repository
git clone <your-repo-url>
cd corne-restricted-environment-config

# 2. Create the target directory in your QMK folder
mkdir -p ~/qmk_firmware/keyboards/crkbd/rev4_0/standard/keymaps/

# 3. Create a dynamic symbolic link (Works from any location)
ln -s "$PWD" ~/qmk_firmware/keyboards/crkbd/rev4_0/standard/keymaps/restricted
3. Configuration
This setup is optimized for security:

rules.mk: Disables VIA, Vial, and Raw HID to prevent unauthorized memory access.

keymap.c: The physical "source of truth" for your keys.

Note: Ensure you have the QK_BOOT key assigned to a layer to enter flash mode without opening the case.

4. Building and Flashing
We provide an automated script to handle the compilation and the flashing process.

Set Permissions:
Bash
chmod +x flash.sh
Run the Flash Process:
Bash
./flash.sh
How to use the script:
The script will first compile the code.

It will then wait for the keyboard to enter Bootloader Mode.

Action Required: Press the Reset Button on your Corne v4 twice quickly (or use your QK_BOOT key combination).

The script will detect the drive and copy the firmware automatically.

Repeat for the second half of the keyboard.

5. Script Details (flash.sh)
The flash.sh included in this repo is path-independent. It automatically finds your current directory and the QMK home directory to ensure a smooth build process regardless of where you cloned this project.

6. Security Audit
To verify what is being installed on your hardware:

Check rules.mk to ensure VIAL_ENABLE = no and VIA_ENABLE = no.

Review keymap.c for any unexpected macros.

Build the firmware and (optional) check the SHA256 hash of the resulting .uf2 file.
