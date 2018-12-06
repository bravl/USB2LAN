file build/USB2LAN.elf
tar ext:3333
monitor halt
load build/USB2LAN.elf
monitor reset halt
mon arm semihosting enable
