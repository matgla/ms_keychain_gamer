#include <hal/time/sleep.hpp>
#include <board.hpp>

#include <msos/drivers/displays/ssd1306/ssd1306.hpp>
#include <msgui/Factory.hpp>
#include <msgui/FrameBuffer.hpp>
#include <msgui/fonts/Font5x7.hpp>
#include <msgui/policies/chunk/SSD1308ChunkPolicy.hpp>
#include <msgui/policies/data/FlashMemoryPolicy.hpp>
#include <avr/pgmspace.h>

constexpr msgui::fonts::Font5x7Type PROGMEM font = msgui::fonts::createFont();

int freeRam () {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

int main()
{
    board::gpio::LED_GREEN::init(hal::gpio::Output::OutputPushPull, hal::gpio::Speed::Default);
    board::gpio::LED_GREEN::setHigh();
    using Serial = board::interfaces::SERIAL;
    Serial::template init<hal::devices::interfaces::USART_1_RX, hal::devices::interfaces::USART_1_TX>(9600);
    Serial::write("Staring LCD initialization\n");
    msos::drivers::displays::SSD1306_I2C<board::interfaces::LCD_I2C> lcd;

    lcd.clear();
    char data[20];
    itoa(freeRam(), data, 10);
    Serial::write("Free ram: ");
    Serial::write(data);
    Serial::write("\n");

    // msgui::FrameBuffer<decltype(lcd), 128, 64> frame_buffer(lcd);

    Serial::write("Created frame buffer\n");

    msgui::Factory<decltype(lcd), msgui::policies::data::FlashMemoryPolicy<uint8_t>, msgui::policies::chunk::ChunkPolicy, msgui::policies::chunk::SSD1308ChunkPolicyParameters> factory(lcd);
    Serial::write("Created factory\n");

    const auto text = factory.make_text("To kiedys", font, {0, 0});
    const auto text2 = factory.make_text("bedzie brelokiem", font, {10, 4});
    const auto text3 = factory.make_text("mojej Asi   :*", font, {18, 8});
    // const auto text2 = factory.make_text("My World!", font, {50, 0});
    // const auto text3 = factory.make_text("Maybe positioning not!", font, {50, 0});

    // const auto h_bitmap = factory.make_bitmap<5, 7>(
    //     1, 0, 0, 0, 1,
    //     1, 0, 0, 0, 1,
    //     1, 0, 0, 0, 1,
    //     1, 1, 1, 1, 1,
    //     1, 0, 0, 0, 1,
    //     1, 0, 0, 0, 1,
    //     1, 0, 0, 0, 1
    // );

    constexpr static auto heart PROGMEM = factory.make_bitmap<15, 12>(
        0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
        0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
        0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
    );
    // constexpr auto heart = factory.make_bitmap<15, 4>(
    //     0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0,
    //     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    //     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    //     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    // );
    // const auto h_image = factory.make_image(msgui::Position{0, 0}, font.get('H'));
    // const auto image2 = factory.make_image(msgui::Position{32, 32}, bitmap);
    const auto heart_image = factory.make_image(msgui::Position{72, 32}, heart);

    const auto window = factory.configure_window()
                            .width(lcd.width())
                            .height(lcd.height())
                            .make(text, text2, text3, heart_image);
    (void)(window);
    itoa(freeRam(), data, 10);
    Serial::write("Free ram: ");
    Serial::write(data);
    Serial::write("\n");
    Serial::write("Created window\n");
    window.draw();
    Serial::write("Windown drawn\n");

    // frame_buffer.draw();
    Serial::write("Frame drawn\n");

    while (true)
    {
        board::gpio::LED_GREEN::setHigh();
        hal::time::sleep(std::chrono::seconds(1));
        board::gpio::LED_GREEN::setLow();
        hal::time::sleep(std::chrono::seconds(1));
    }
}