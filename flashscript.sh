#!/bin/bash

# Konfiguration der Pfade
REPO_DIR="/home/woodz/dev/corne-restricted-environment-config"
QMK_DIR="$HOME/qmk_firmware"
KEYBOARD="crkbd/rev4_0/standard"
KEYMAP="restricted"
FIRMWARE_NAME="crkbd_rev4_0_standard_restricted.uf2"
FIRMWARE_PATH="$QMK_DIR/$FIRMWARE_NAME"
MOUNT_POINT="/run/media/$USER/RPI-RP2"

# Farbdefinitionen für die Konsole
GREEN='\033[0;32m'
CYAN='\033[0;36m'
RED='\033[0;31m'
NC='\033[0m' # No Color

echo -e "${CYAN}--- QMK Build & Flash Tool (Restricted Environment) ---${NC}"

# 1. Schritt: Kompilieren der Firmware
echo "Status: Starte Kompiliervorgang..."
cd "$QMK_DIR" || {
  echo -e "${RED}Fehler: QMK Verzeichnis nicht gefunden.${NC}"
  exit 1
}

if qmk compile -kb "$KEYBOARD" -km "$KEYMAP"; then
  echo -e "${GREEN}Status: Kompilierung erfolgreich abgeschlossen.${NC}"
else
  echo -e "${RED}Fehler: Kompilierung fehlgeschlagen.${NC}"
  exit 1
fi

# 2. Schritt: Überprüfung der Firmware-Datei
if [ ! -f "$FIRMWARE_PATH" ]; then
  echo -e "${RED}Fehler: Firmware-Datei $FIRMWARE_NAME wurde nicht erstellt.${NC}"
  exit 1
fi

# 3. Schritt: Warten auf die Hardware
echo -e "\n${CYAN}Warten auf Bootloader-Mount: $MOUNT_POINT${NC}"
echo "Aktion: Bitte den Reset-Knopf der Tastatur (Corne v4) zweimal schnell drücken."

while [ ! -d "$MOUNT_POINT" ]; do
  sleep 1
  echo -n "."
done

echo -e "\n${GREEN}Status: Laufwerk erkannt.${NC}"

# 4. Schritt: Kopieren der Firmware (Flash-Vorgang)
echo "Status: Übertragung der UF2-Datei..."
if cp "$FIRMWARE_PATH" "$MOUNT_POINT"; then
  echo -e "${GREEN}Erfolg: Flash-Vorgang abgeschlossen. Die Tastatur startet neu.${NC}"
else
  echo -e "${RED}Fehler: Kopnervorgang fehlgeschlagen.${NC}"
  exit 1
fi

# Zurück zum Ursprungsverzeichnis
cd "$REPO_DIR" || exit
