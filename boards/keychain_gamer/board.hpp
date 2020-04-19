#pragma once
// left  button
// right button
// mid button

// i2c connectors

#include <devices/avr/attiny/attiny85/gpio.hpp>

namespace board
{
namespace gpio
{
using BUTTON_LEFT = hal::devices::gpio::PB1;
using LED_GREEN = hal::devices::gpio::PB3;
using BUTTON_RIGHT = hal::devices::gpio::PB4;
}
}



// using LEFT_BUTTON
