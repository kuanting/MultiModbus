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
  modbus_server.configureCoils(0x00, 1);
  
  Serial.print("MultiModbus is ready! Device ID is ");
  Serial.println(MODBUS_DEVICE_ID);
  
}


void loop() {
  int packetReceived;

  // poll for Modbus RTU requests
  packetReceived = modbus_server.poll();
  if(packetReceived) {
    int coilValue = modbus_server.coilRead(0x00);
    Serial.println(coilValue);
  }
}