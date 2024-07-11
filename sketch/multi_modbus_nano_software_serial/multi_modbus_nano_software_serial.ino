// This example shows how to use MultiModbus with SoftwareSerial on Arduino NANO
// It creates a server with 10 Coils, 10 Discrete Inputs, 10 Holding Registers and 10 Input Registers
// A user can use other Modbus tools to communicate with the server
// Author: Kuan-Ting Lai

#include <RS485.h>    // https://github.com/RobTillaart/RS485
#include <MultiModbus.h>
#include <SoftwareSerial.h>

// This sketch uses Arduino NANO 485 industrial control board as an example. 
// You can find the board's information below:
// https://www.aliexpress.com/item/1005003710057347.html
// Pinout diagram:
//https://ae01.alicdn.com/kf/Sdf186ca8d45649cd8bef91bf5d6d2f16T.jpg
// 
// 中文相關訊息
// https://www.ruten.com.tw/item/show?22023652957564
// https://ruten-proteus.blogspot.com/2020/06/1try-vtscada-arduino-nano-485-modbus-rtu.html

#define RS485_BAUD_RATE 19200
#define MODBUS_DEVICE_ID 1

const uint8_t sendPin  = -1;  // Our board has auto-direction

SoftwareSerial sw_serial(13, 12); // D13/D12 for RX/TX
RS485 rs485(&sw_serial, sendPin);

ModbusRTUServer modbus_server(rs485);


void setup() {
  Serial.begin(19200);  // Debug
  //while (!Serial);    // Avoid endless loop when running without USB COM port
  
  sw_serial.begin(RS485_BAUD_RATE);
  
  if (!modbus_server.begin(MODBUS_DEVICE_ID, RS485_BAUD_RATE)) {
    Serial.println("Failed to start Modbus RTU Server !");
    while (1);
  }

  // configure a single coil at address 0x00, Modbus client will start to read/write from 0x01
  // Create 10 data write serial numbers for Coils, Discrete Inputs, Registers, 
  modbus_server.configureCoils(0x00, 10); // 1-bit, read/write
  for (int i=0; i<10; i++) {
    modbus_server.coilWrite(i, 0);
  }
  modbus_server.configureDiscreteInputs(0x00, 10); // 1-bit, read only
  for (int i=0; i<10; i++) {
    modbus_server.discreteInputWrite(i, i % 2);
  }
  modbus_server.configureHoldingRegisters(0, 10); // 16-bit, read only
  for (int i=0; i<10; i++) {
    modbus_server.holdingRegisterWrite(i, i);
  }
  modbus_server.configureInputRegisters(0, 10); // 16-bit read/write
  for (int i=0; i<10; i++) {
    modbus_server.inputRegisterWrite(i, i);
  }
  
  Serial.print("MultiModbus is ready! Device ID is ");
  Serial.println(MODBUS_DEVICE_ID);
  
}


void loop() {
  int packetReceived;

  // poll for Modbus RTU requests
  packetReceived = modbus_server.poll();
  if(packetReceived) {
    int value;
    Serial.println("Coil values:");
    for (int i=0; i<10; i++) {
      value = modbus_server.coilRead(i);
      Serial.print(value);
      Serial.print(", ");
    }
    Serial.println("\nRegister values");
    for (int i=0; i<10; i++) {
      value = modbus_server.inputRegisterRead(i);
      Serial.print(value);
      Serial.print(", ");
    }
    Serial.println("");
  }
}