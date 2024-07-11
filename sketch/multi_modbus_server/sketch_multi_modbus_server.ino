// Author: Kuan-Ting Lai
#include <RS485.h>    // https://github.com/RobTillaart/RS485
#include <MultiModbus.h>

#define RS485_BAUD_RATE 19200
#define MODBUS_DEVICE_ID 1

// TTL 485 v2.0 module don't need sendPin (enablePin) 
// https://jin-hua.com.tw/webc/html/product/show.aspx?num=35141
const uint8_t sendPin  = -1;  
// The TTL to RS485 module needs to assign an enable pin
// https://www.taiwaniot.com.tw/product/ttl-to-rs485rs422-max485-module/
// const uint8_t sendPin  = 9;

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