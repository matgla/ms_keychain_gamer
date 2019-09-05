#include <hal/time/sleep.hpp>
#include <board.hpp>

int main()
{
    while (true)
    {
        board::gpio::LEFT_BUTTON::setHigh();
    }
}