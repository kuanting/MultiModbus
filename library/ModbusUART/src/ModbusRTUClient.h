/*
  This file is part of the ArduinoModbus library.
  Copyright (c) 2018 Arduino SA. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _MODBUS_RTU_CLIENT_H_INCLUDED
#define _MODBUS_RTU_CLIENT_H_INCLUDED

#include "ModbusClient.h"
#include <RS485.h>

class ModbusRTUClient : public ModbusClient {
public:
  ModbusRTUClient(RS485& rs485);
  virtual ~ModbusRTUClient();

  /**
   * Start the Modbus RTU client with the specified parameters
   *
   * @param baudrate Baud rate to use
   * @param config serial config. to use defaults to SERIAL_8N1
   *
   * Return 1 on success, 0 on failure
   */
  int begin(unsigned long baudrate, uint16_t config = SERIAL_8N1);
  int begin(RS485& rs485, unsigned long baudrate, uint16_t config = SERIAL_8N1);

private:
  RS485* _rs485;
};

#endif
