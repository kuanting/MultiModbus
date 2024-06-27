// Author: Kuan-Ting Lai
#include <RS485.h>    // https://github.com/RobTillaart/RS485
#include <MultiModbus.h>

#define RS485_BAUD_RATE 19200
#define MODBUS_DEVICE_ID 1

const uint8_t sendPin  = -1;  // TTL 485 module don't need sendPin

RS485 rs485(&Serial1, sendPin);  // Server
ModbusRTUServer modbus_server(rs485); // Server is listening on Serial1


void setup() {
  Serial.begin(19200);  // Debug
  //while (!Serial);    // Avoid endless loop when running without USB COM port
  
  Serial1.begin(RS485_BAUD_RATE);
  while(!Serial1);
  
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