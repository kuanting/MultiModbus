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

#include <errno.h>

extern "C" {
#include "libmodbus/modbus.h"
#include "libmodbus/modbus-rtu.h"
}

#include "ModbusRTUClient.h"


ModbusRTUClient::ModbusRTUClient(RS485& rs485) :
  ModbusClient(1000),  _rs485(&rs485)
{
}

ModbusRTUClient::~ModbusRTUClient()
{
}

int ModbusRTUClient::begin(unsigned long baudrate, uint16_t config)
{
  modbus_t* mb = modbus_new_rtu(_rs485, baudrate, config);

  if (!ModbusClient::begin(mb, 0x00)) {
    return 0;
  }

  return 1;
}

int ModbusRTUClient::begin(RS485& rs485, unsigned long baudrate, uint16_t config)
{
  _rs485 = &rs485;
  return begin(baudrate, config);
}