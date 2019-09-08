#include <hal/time/sleep.hpp>
#include <board.hpp>

int main()
{
    while (true)
    {
        board::gpio::LED_GREEN::init(hal::gpio::Output::OutputPushPull, hal::gpio::Speed::Default);
        board::gpio::LED_GREEN::setHigh();
    }
}