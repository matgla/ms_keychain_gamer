#include <hal/time/sleep.hpp>
#include <board.hpp>

#include <msos/drivers/displays/ssd1306/ssd1306.hpp>

int main()
{
    board::gpio::LED_GREEN::init(hal::gpio::Output::OutputPushPull, hal::gpio::Speed::Default);
    board::gpio::LED_GREEN::setHigh();
    msos::drivers::displays::SSD1306_I2C<board::interfaces::LCD_I2C> lcd;

    while (true)
    {
        board::gpio::LED_GREEN::setHigh();
        hal::time::sleep(std::chrono::seconds(1));
        board::gpio::LED_GREEN::setLow();
        hal::time::sleep(std::chrono::seconds(1));
    }
}