// This example shows how to re-map input register 1001 ~ 1000 to 1 ~ 100.
// Author: Kuan-Ting Lai

#include <RS485.h>    // https://github.com/RobTillaart/RS485
#include <MultiModbus.h>

#define RS485_BAUD_RATE 19200
#define MODBUS_DEVICE_ID 1

// Inherit class ModbusRTUServer and overwrite addrMapping()F
class ModbusRTUSlave: public ModbusRTUServer 
{
public:
  ModbusRTUSlave(RS485& rs485) : ModbusRTUServer(rs485) {};

  // Overwrite
  virtual void addrMapping(unsigned char request[]) {
    int slaveID = request[0];
    int function = request[1];
    uint16_t address = (request[2] << 8) + request[3];
    int nb = (request[4] << 8) + request[5];
    Serial.print("Function: ");
    Serial.print(function);
    Serial.print("\tAddress: ");
    Serial.print(address);
    Serial.print("\tLen: ");
    Serial.println(nb);

    // internal address == Modbus address - 1
    if (address >= 1000 && address < 1100) {
      address -= 1000;
      request[2] = address >> 8;
      request[3] = address & 0x00FF;
    }
  }
};

RS485 rs485(&Serial1, -1); // TTL 485 v2.0 module doesn't need send enable pin 
ModbusRTUSlave modbus_server(rs485); // Server is listening on Serial1

void setup() {
  Serial.begin(115200);  // Debug
  //while (!Serial);    // Avoid endless loop when running without USB COM port
  
  Serial1.begin(RS485_BAUD_RATE);
  while(!Serial1);
  
  if (!modbus_server.begin(MODBUS_DEVICE_ID, RS485_BAUD_RATE)) {
    Serial.println("Failed to start Modbus RTU Server !");
    while (1);
  }

  // Create 1000 registers and write serial numbers
  modbus_server.configureInputRegisters(0, 100);
  for (int i=0; i < 100; i++) {
    modbus_server.inputRegisterWrite(i, i);
  }

  // Enable address mapping
  modbus_server.setAddrMapping(true);

  Serial.print("MultiModbus Address re-mapping example! Device ID is ");
  Serial.println(MODBUS_DEVICE_ID);
}

void loop() {
  // poll for Modbus RTU requests
  modbus_server.poll();
}