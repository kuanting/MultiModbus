# MultiModbus

MultiModbus is an Arduino library that supports multiple Modbus RTU servers and clients over RS485 on one board. RS485-to-UART ICs are required.

## Introduction

MultiModbus supports multiple Modbus servers/clients on one board. Modbus messages are exchanged over RS-485 wires, requiring a MAX485 IC for each channel to convert the RS485 signal to a UART. 

### Why another Modbus library?
The official [ArduinoModbus](https://github.com/arduino-libraries/ArduinoModbus) is a powerful and intuitive library based on ArduinoRS485 and [libmodbus](https://libmodbus.org/). However, it is designed for MKR boards only and fixed to use hardware Serial1. MultiModbus leverages ArduinoModbus RTU class and [Robert Tillaart's RS485](https://github.com/RobTillaart/RS485) to enable using different hardware/software serial ports. In this way, our library can run multiple Modbus servers/clients on one board. 


### Supported Boards
We have successfully run our library on MEGA, UNO, and NANO using SoftwareSerial. However, keep in mind that SoftwareSerial library may conflict with other comminucation libraries such as Wire, so our library is best run on a board with multiple hardware serial ports.

<img src="./img/4_arduino_modbus_test.jpg">

## Example

We provide a [Modbus server example](sketch/sketch_multi_modbus_server/sketch_multi_modbus_server.ino). You can use the [EasyModbus](https://github.com/rossmann-engineering/EasyModbusTCP.NET) to read/write the coil of the server. The code has been tested on various boards including Arduino NANO, MEGA, and UNO. The maximum number of servers/clients depends on the target boards.

<img src="./img/EasyModbusTest.jpg">
