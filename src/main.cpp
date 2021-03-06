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

#include "drivers/gamepad/event.hpp"
#include "io/gamepad.hpp"
#include "io/display.hpp"
#include "io/button_reader.hpp"

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
    const auto& font = msgui::fonts::Font5x7::data;
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
        }
        closedir(d);
    }

    int number_of_positions = 0;
    if (!path_1.empty())
    {
        exec_1.setText(path_1);
        number_of_positions = 1;
    }

    int current_position = 0;
    bool stop = false;
    while (!stop)
    {
        gamepad.read_event(&event);
        auto buttons = io::get_buttons(event);
        if (io::was_button_released(buttons.mid_button))
        {
            stop = true;
        }
        window.display();
    }
    std::string game_path = "/bin/space_invaders.bin";
    exec(game_path.c_str(), NULL, NULL, NULL);
    }
    gamepad.deinitialize();
    display.deinitialize();
    return 0;
}


} // namespace

REGISTER_APP(gamer, &app_start);
