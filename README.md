# MultiMobus

MultiMobus is an Arduino library that supports multiple Modbus RTU servers and clients over RS485 on one board. RS485-to-UART ICs are required.

## Introduction

MultiMobus supports full duplex and multiple servers/clients on one board, which leverages [ArduinoMobus](https://github.com/arduino-libraries/ArduinoModbus) RTU class and [Robert Tillaart's RS485](https://github.com/RobTillaart/RS485). Modbus messages are exchanged over RS-485 wires, requiring an AISC like the MAX485 to convert the RS485 signal to a UART for each channel. We recommend using hardware UARTs. The code has been tested on various boards i including Arduino NANO, MEGA, UNO, and MKR. The maximum number of servers/clients depends on the target boards.
