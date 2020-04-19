// This file is part of MS Keychain Gamer project. This is tiny game console.
// Copyright (C) 2020 Mateusz Stadnik
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

/* This file describes hardware configuration, existing input and output peripherals */

#include <array>

#include <hal/interfaces/usart.hpp>
#include <hal/gpio/digital_input_output_pin.hpp>

#include <devices/arm/stm32/stm32f1/stm32f103c8t6/gpio.hpp>
#include <devices/arm/stm32/stm32f1/stm32f103c8t6/usart.hpp>
#include <devices/arm/stm32/stm32f1/stm32f103c8t6/i2c.hpp>

namespace board
{

void board_init();

namespace gpio
{

// extern hal::gpio::DigitalOutputPin LED_GREEN; = hal::devices::gpio::PB1::OutputType;

/* Console has 3 buttons */

using RIGHT_KEY = hal::devices::gpio::PA15;
using MID_KEY = hal::devices::gpio::PB14;
using LEFT_KEY = hal::devices::gpio::PA12;

}

namespace interfaces
{

/* Usart interface exists for debugging purposes, in future maybe usb will be available ? */
extern std::array<hal::interfaces::Usart*, 1> usarts;

/* SSD OLED screen will be connected via I2C interface */
extern hal::interfaces::I2C* LCD_I2C;
// std::array<hal::interfaces::I2C, 1> i2cs;

}

}
