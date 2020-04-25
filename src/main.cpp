// This file is part of MS keychain gamer project. This is tiny game console.
// Copyright (C) 2020 Mateusz Stadnik
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <msos/apps/app_registry.hpp>

#include <msos/libc/printf.hpp>

#include <cstring>
#include <cmath>
#include <unistd.h>
#include <dirent.h>

#include <hal/time/sleep.hpp>

#include <msgui/Factory.hpp>
#include <msgui/policies/chunk/SSD1308ChunkPolicy.hpp>
#include <msgui/policies/data/DefaultMemoryPolicy.hpp>
#include "msgui/fonts/Font5x7.hpp"

#include <fcntl.h>

#include <msos/kernel/process/spawn.hpp>

#include "drivers/event.hpp"
#include "io/gamepad.hpp"
#include "io/display.hpp"

namespace
{

int app_start()
{
    io::Gamepad& gamepad = io::Gamepad::get();
    io::Display& display = io::Display::get();

    gamepad.initialize("/dev/pad1");
    display.initialize("/dev/fb0");
    {
    auto factory = display.window_factory();
    const auto font = factory.make_font<msgui::fonts::Font5x7>();

    const auto text = factory.make_text("Select game: ", font, {0, 0});
    auto exec_1 = factory.make_text("", font, {7, 8});
    // auto exec_2 = factory.make_text("", font, {7, 16});
    // auto exec_3 = factory.make_text("", font, {7, 24});
    // auto exec_4 = factory.make_text("", font, {7, 32});

    constexpr static auto arrow = factory.make_bitmap<5, 7>(
        0, 0, 0, 0, 0,
        0, 1, 0, 0, 0,
        0, 1, 1, 0, 0,
        0, 1, 1, 1, 0,
        0, 1, 1, 0, 0,
        0, 1, 0, 0, 0,
        0, 0, 0, 0, 0
    );

    auto arrow_image = factory.make_image({0, 9}, arrow);

    auto window = factory.configure_window()
                            .width(128)
                            .height(64)
                            .make(text, exec_1, arrow_image);

    drivers::GamepadEvent event;

    // uint8_t some_data[] = { 0xa, 0x1, 0x2, 0x3, 0xff, 0xff};

    DIR *d;
    struct dirent *dir;
    char path[]="/bin";
    d = opendir(path);
    std::string path_1;
    std::string path_2;
    // std::string path_3;
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (path_1 == "")
            {
                path_1 = dir->d_name;
            }
            // else if (path_2 == "")
            // {
            //     path_2 = dir->d_name;
            // }
            // else if (path_3 == "")
            // {
            //     path_3 = dir->d_name;
            // }
        }
        closedir(d);
    }

    int number_of_positions = 0;
    if (!path_1.empty())
    {
        exec_1.setText(path_1);
        number_of_positions = 1;
    }

    // if (!path_2.empty())
    // {
    //     exec_2.setText(path_2);
    //     number_of_positions = 2;
    // }

    // if (!path_3.empty())
    // {
    //     exec_3.setText(path_3);
    //     number_of_positions = 3;
    // }

    int current_position = 0;
    bool stop = false;
    while (gamepad.read_event(&event) && !stop)
    {
        switch (event.type)
        {
            case drivers::EventType::Button:
            {
                if (event.value)
                {

                    if (event.button_number == 1)
                    {
                        stop = true;
                    }
                    if (event.button_number == 0)
                    {
                        auto pos = arrow_image.get_position();

                        if (current_position < number_of_positions - 1)
                        {
                            pos.y += 8;
                            ++current_position;
                        }
                        else
                        {
                            pos.y = 9;
                            current_position = 0;
                        }

                        arrow_image.set_position(pos);
                    }
                    if (event.button_number == 2)
                    {
                        auto pos = arrow_image.get_position();

                        if (current_position > 0)
                        {
                            pos.y -= 8;
                            --current_position;
                        }
                        else
                        {
                            pos.y = (number_of_positions - 1) * 9 + 9;
                            current_position = number_of_positions - 1;
                        }

                        arrow_image.set_position(pos);
                    }
                }
                else
                {
                }
            } break;
            default:
            {
            }
        }
        window.display();
    }
    }
    std::string path = "/bin/space_invaders.bin";
    exec(path.c_str(), NULL, NULL, NULL);

    gamepad.deinitialize();
    display.deinitialize();
    return 0;
}


} // namespace

REGISTER_APP_AUTOSTART(gamer, &app_start);
