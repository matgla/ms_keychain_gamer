// This file is part of MSOS project. This is simple OS for embedded development devices.
// Copyright (C) 2019 Mateusz Stadnik
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

#include "board.hpp"

#include <stm32f10x.h>

#include <devices/arm/stm32/stm32f1/stm32f103c8t6/usart.hpp>
#include <devices/arm/stm32/stm32f1/stm32f103c8t6/gpio.hpp>

namespace board
{

namespace interfaces
{
    std::array<hal::interfaces::Usart*, 1>& usarts()
    {
        static hal::devices::interfaces::Usart1 usart1;
        static std::array<hal::interfaces::Usart*, 1> usarts_{&usart1};
        return usarts_;
    }

    hal::interfaces::I2C& LCD_I2C()
    {
        static hal::devices::interfaces::I2C_1 i2c;
        return i2c;
    }
}

void board_init()
{
    SystemInit();
}

}

