#include <hal/time/sleep.hpp>
#include <board.hpp>

int main()
{
    while (true)
    {
        board::gpio::LEFT_BUTTON::init(hal::gpio::Output::OutputPushPull, hal::gpio::Speed::Default);
        board::gpio::LEFT_BUTTON::setHigh();
    }
}