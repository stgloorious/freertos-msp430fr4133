#!/bin/bash
# This script converts the MSP430 EFI binary produced by GCC to hex format
# which is then uploaded over serial to the target, using
# MSP430Flasher (https://www.ti.com/tool/MSP430-FLASHER)

INITIAL_EXECUTABLE="$1/app"
TARGET_EXECUTABLE="$1/app.hex"

OBJCOPY=/usr/msp430-gcc/bin/msp430-elf-objcopy

GREEN="\x1b[32m"
RESET="\x1b[0m"

echo -e "${GREEN}>>> Converting executable$RESET"
$OBJCOPY -O ihex $INITIAL_EXECUTABLE $TARGET_EXECUTABLE

echo -e "${GREEN}>>> Uploading $TARGET_EXECUTABLE to target$RESET"
MSP430Flasher  -e ERASE_ALL -w $TARGET_EXECUTABLE -v -z [VCC,RESET]

echo -e "${GREEN}>>> Deleting flasher log artifacts$RESET"
rm -rd $1/../Log
