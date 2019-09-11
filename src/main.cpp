#include <hal/time/sleep.hpp>
#include <board.hpp>

#include <msos/drivers/displays/ssd1306/ssd1306.hpp>
#include <msgui/Factory.hpp>
#include <msgui/FrameBuffer.hpp>
#include <msgui/fonts/Font5x7.hpp>

int main()
{
    board::gpio::LED_GREEN::init(hal::gpio::Output::OutputPushPull, hal::gpio::Speed::Default);
    board::gpio::LED_GREEN::setHigh();
    using Serial = board::interfaces::SERIAL;
    Serial::template init<hal::devices::interfaces::USART_1_RX, hal::devices::interfaces::USART_1_TX>(9600);
    Serial::write("Staring LCD initialization\n");
    msos::drivers::displays::SSD1306_I2C<board::interfaces::LCD_I2C> lcd;
    msgui::FrameBuffer<decltype(lcd), 128, 64> frame_buffer(lcd);
    Serial::write("Created frame buffer\n");

    msgui::Factory<decltype(frame_buffer)> factory(frame_buffer);
    Serial::write("Created factory\n");

    const auto text   = factory.make_text("Hello World!", msgui::fonts::Font5x7, {10, 0});
    const auto window = factory.configure_window()
                            .width(lcd.width())
                            .height(lcd.height())
                            .make(text);
    Serial::write("Created window\n");

    window.draw();
    Serial::write("Windown drawn\n");

    frame_buffer.draw();
    Serial::write("Frame drawn\n");

    while (true)
    {
        board::gpio::LED_GREEN::setHigh();
        hal::time::sleep(std::chrono::seconds(1));
        board::gpio::LED_GREEN::setLow();
        hal::time::sleep(std::chrono::seconds(1));
    }
}