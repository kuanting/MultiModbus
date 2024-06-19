#include <RS485.h> // ModbusUART depends on the ArduinoRS485 library
#include <ModbusUART.h>
#include <SoftwareSerial.h>

#define MODBUS_DEVICE_ID 1

const int ledPin = 8;
const uint8_t sendPin  = -1; // Some RS485 modules don't need sendPin

SoftwareSerial sw_serial(13, 12);  // NANO Industrial board

Stream *serial_ptr = &sw_serial; // Our class can use both Software & Hardware serial
//Stream *serial_ptr = &Serial1;
RS485 rs485(serial_ptr, sendPin);  //  uses default deviceID
ModbusRTUServer modbus_server(rs485);

void setup() {
  Serial.begin(9600);
  while (!Serial);
  sw_serial.begin(9600);
  while(!sw_serial);
  Serial.println("Modbus RTU Server");
  
  // start the Modbus RTU server, with (slave) id 1
  if (!modbus_server.begin(MODBUS_DEVICE_ID, 9600)) {
    Serial.println("Error! Failed to run Modbus RTU Server!");
    while (1);
  }

  // configure the LED
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // configure a single coil at address 0x00
  modbus_server.configureCoils(0x00, 1);
  Serial.print("Modbus device is ready! ID=");
  Serial.println(MODBUS_DEVICE_ID);
}


void loop() {
  // poll for Modbus RTU requests
  int packetReceived = modbus_server.poll();
  
  if(packetReceived) {
    // read the current value of the coil
    int coilValue = modbus_server.coilRead(0x00);
    Serial.print(coilValue);
    /*f (coilValue) {
      // coil value set, turn LED on
      digitalWrite(ledPin, HIGH);
    } else {
      // coil value clear, turn LED off
      digitalWrite(ledPin, LOW);
    }*/
  }
}