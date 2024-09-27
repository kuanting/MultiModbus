# MultiModbus Library

MultiModbus supports multiple Modbus servers/clients on one board. Modbus messages are exchanged over RS-485 wires, requiring a MAX485 IC for each channel to convert the RS485 signal to a UART. 
MultiModbus leverages the ArduinoModbus RTU class in [ArduinoModbus](https://github.com/arduino-libraries/ArduinoModbus) and [Robert Tillaart's RS485](https://github.com/RobTillaart/RS485) to enable using different hardware/software serial ports. In this way, our library can run multiple Modbus servers/clients on one board. 

To use this library, install [Robert Tillaart's RS485](https://github.com/RobTillaart/RS485) first, and then include the files below:
```
#include <RS485.h>
#include <MultiModbus.h>
```
More examples can be found on []()

## Further readings

- [Modbus Tutorial from Control Solutions](https://www.csimn.com/CSI_pages/Modbus101.html)
- [Modbus Application Protocol (PDF)](http://www.modbus.org/docs/Modbus_Application_Protocol_V1_1b3.pdf)
- [Modbus FAQ](https://modbus.org/faq.php)
