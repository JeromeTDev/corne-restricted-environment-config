#!/bin/bash

# Get the directory where this script is located
REPO_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
QMK_DIR="$HOME/qmk_firmware"
KEYBOARD="crkbd/rev4_1/standard"
KEYMAP="restricted"
FIRMWARE_NAME="crkbd_rev4_1_standard_restricted.uf2"
FIRMWARE_PATH="$QMK_DIR/$FIRMWARE_NAME"
MOUNT_POINT="/run/media/$USER/RPI-RP2"

GREEN='\033[0;32m'
CYAN='\033[0;36m'
RED='\033[0;31m'
NC='\033[0m'

echo -e "${CYAN}--- QMK Build & Flash Tool ---${NC}"

cd "$QMK_DIR" || exit 1
if qmk compile -kb "$KEYBOARD" -km "$KEYMAP"; then
  echo -e "${GREEN}Status: Compilation successful.${NC}"
else
  echo -e "${RED}Error: Compilation failed.${NC}"
  exit 1
fi

echo -e "\n${CYAN}Waiting for Bootloader (RPI-RP2)...${NC}"
while [ ! -d "$MOUNT_POINT" ]; do
  sleep 1
  echo -n "."
done

echo -e "\n${GREEN}Status: Drive detected.${NC}"
if cp "$FIRMWARE_PATH" "$MOUNT_POINT"; then
  echo -e "${GREEN}Success: Flash complete.${NC}"
else
  echo -e "${RED}Error: Flash failed.${NC}"
  exit 1
fi
