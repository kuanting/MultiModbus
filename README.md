# MultiMobus

MultiMobus is an Arduino library that supports multiple Modbus RTU servers and clients over RS485 on one board. RS485-to-UART ICs are required.

## Introduction

MultiMobus supports full duplex and multiple servers/clients on one board. Modbus messages are exchanged over RS-485 wires, requiring an AISC like the MAX485 to convert the RS485 signal to a UART for each channel. We leverage [ArduinoMobus](https://github.com/arduino-libraries/ArduinoModbus) RTU class and [Robert Tillaart's RS485](https://github.com/RobTillaart/RS485). The original ArduinoModbus is based on ArduinoRS485, which is fixed to using Serial1. We replace the ArduinoRS485 with Rob's RS485, which can use different hardware/software serial ports. We have successfully adopted SoftwareSerial for Modbus communiction. However, SoftwareSerial library may conflict with other comminucation libraries such as Wire. As a result, we recommend using hardware UARTs for stability..

## Test

The code has been tested on various boards including Arduino NANO, MEGA, UNO, and MKR. The maximum number of servers/clients depends on the target boards.

<img src="./img/4_arduino_modbus_test.jpg">
