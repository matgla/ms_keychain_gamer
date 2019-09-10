#pragma once
// left  button
// right button
// mid button

// i2c connectors

#include <devices/avr/atmega/atmega8/atmega8.hpp>

namespace board
{
namespace gpio
{
using BUTTON_LEFT = hal::devices::gpio::PD6::InputType;
using BUTTON_MID = hal::devices::gpio::PD7::InputType;
using BUTTON_RIGHT = hal::devices::gpio::PB0::InputType;
using LED_GREEN = hal::devices::gpio::PC2::OutputType;
using LED_RED = hal::devices::gpio::PC1::OutputType;
using LED_YELLOW = hal::devices::gpio::PC0::OutputType;
using LED_BLUE = hal::devices::gpio::PB1::OutputType;
}
namespace interfaces
{
using LCD_I2C = hal::devices::interfaces::I2C_1;
using SERIAL = hal::devices::interfaces::USART;
}
}



// using LEFT_BUTTON