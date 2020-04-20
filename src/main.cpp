#include <msos/apps/app_registry.hpp>

#include <msos/libc/printf.hpp>

#include <stm32f10x_dma.h>

#include <cstring>
#include <cmath>

#include <hal/time/sleep.hpp>

#include <msgui/Factory.hpp>
#include <msgui/policies/chunk/SSD1308ChunkPolicy.hpp>
#include <msgui/policies/data/DefaultMemoryPolicy.hpp>
#include "msgui/fonts/Font5x7.hpp"

#include <fcntl.h>

#include "drivers/event.hpp"

namespace
{

bool read_event(int fd, drivers::GamepadEvent* event)
{
    std::size_t bytes;
    bytes = read(fd, event, sizeof(drivers::GamepadEvent));
    if (bytes == sizeof(drivers::GamepadEvent))
    {
        return true;
    }
    return false;
}

class FbDevice
{
public:
    FbDevice(int fd)
        : fd_(fd)
    {
        std::memset(buffer_, 0, sizeof(buffer_));
    }

    int height()
    {
        return 128;
    }

    int width()
    {
        return 64;
    }

    void write()
    {
        ::write(fd_, &buffer_, sizeof(buffer_));
    }

    void set_pixel(int x, int y)
    {
        if (x >= height() || y >= width() || x < 0 || y < 0)
        {
            return;
        }
        int position_in_buffer = x + std::floor(y / 8) * 64;
        buffer_[position_in_buffer] |= 1 << (y % 8);
    }

    // void clear_pixel(int x, int y)
    // {
    //     if (x >= height() || y >= width() || x < 0 || y < 0)
    //     {
    //         return;
    //     }
    //     int position_in_buffer = std::floor(x / 8) + y * (128/8);
    //     buffer_[position_in_buffer] &= ~(1 << (x % 8));
    // }

    void sync()
    {
        write();
        std::memset(buffer_, 0, sizeof(buffer_));
    }
private:
    uint8_t buffer_[(128 * 64)/8];
    int fd_;
};

int app_start()
{
    printf("Hello in keychain gamer\n");
    int pad = open("/dev/pad1", O_RDONLY);
    int fb = open("/dev/fb0", O_RDONLY);
    printf("Pad FD %d\n", pad);
    FbDevice fb_dev(fb);
    msgui::Factory<decltype(fb_dev)> factory(fb_dev);
    const auto font = factory.make_font<msgui::fonts::Font5x7>();

    const auto text = factory.make_text("Select game: ", font, {0, 0});
    auto text_left = factory.make_text("L: ", font, {0, 40});
    auto text_right = factory.make_text("R: ", font, {40, 40});

    text_left.hide();
    text_right.hide();

    const auto window = factory.configure_window()
                            .width(128)
                            .height(64)
                            .make(text, text_left, text_right);

    drivers::GamepadEvent event;

    // uint8_t some_data[] = { 0xa, 0x1, 0x2, 0x3, 0xff, 0xff};
    window.draw();

    while (read_event(pad, &event))
    {
        switch (event.type)
        {
            case drivers::EventType::Button:
            {
                if (event.value)
                {
                    printf("Button pressed: %d\n", event.button_number);

                    if (event.button_number == 1)
                    {
                        return 0;
                    }
                    if (event.button_number == 0)
                    {
                        text_left.show();
                    }
                    if (event.button_number == 2)
                    {
                        text_right.show();
                    }
                }
                else
                {
                    if (event.button_number == 0)
                    {
                        text_left.hide();
                    }
                    if (event.button_number == 2)
                    {
                        text_right.hide();
                    }
                    printf("Button released: %d\n", event.button_number);
                }
            } break;
            default:
            {
            }
        }
        window.draw();
    }

    return 0;
}

} // namespace

REGISTER_APP_AUTOSTART(gamer, &app_start);
