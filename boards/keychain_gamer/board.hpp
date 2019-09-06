#pragma once
// left  button
// right button
// mid button

// i2c connectors

#include <avr/io.h>

#include <hal/gpio/gpio.hpp>
#include <avr/common/gpio/avr_gpio.hpp>
#include <avr/attiny85/gpio/ports.hpp>

namespace board
{
namespace gpio
{
using LEFT_BUTTON = hal::gpio::Gpio<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortB, 0>>;
}
}



// using LEFT_BUTTON