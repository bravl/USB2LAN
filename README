# USB2LAN

## Intro
The main goal is to create a PoC of an USB2LAN device which exposes a network device over the a USB interface. Code is split in 2 parts.
- MCU: Which contains the MCU code for the USB2LAN functionallity. Currently running/implemented on a STM32F746-Disco board.
- linux-driver: A Linux USB driver which exposes a networking device. This driver communicates to the STM using USB-HID

## Details

### MCU
The MCU uses the following main components
- STM32Cube-F7 
	- HAL
	- USB-Device stack which exposes an HID-Device
- FreeRTOS (Scheduler / Realtime operating system)
- LwIP (Lightweight IP Stack)
