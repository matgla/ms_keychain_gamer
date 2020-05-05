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

#include <optional>

#include <msgui/fonts/Font5x7.hpp>

#include <msos/libc/printf.hpp>

#include <hal/time/time.hpp>
#include <hal/time/sleep.hpp>

#include <time.h>
#include <sys/time.h>

#include "drivers/gamepad/event.hpp"

#include "io/display.hpp"
#include "io/gamepad.hpp"

#include "player.hpp"
#include "monster_line.hpp"
#include "bullet.hpp"

#include "assets/main_menu_title.hpp"
#include "assets/main_menu_monster.hpp"
#include "assets/main_menu_press_key.hpp"

static int app()
{
    constexpr int window_height = 64;
    constexpr int window_width = 128;

    auto& gamepad = io::Gamepad::get();
    auto& display = io::Display::get();
    drivers::GamepadEvent event;

    auto factory = display.window_factory();

    // space_invaders::Player player(msgui::Position{(window_width - space_invaders::pad.width()) / 2, window_height - space_invaders::pad.height()}, 0 , window_width);

    auto window = factory.configure_window()
                        .width(window_width)
                        .height(window_height)
                        .make();

    msgui::Image menu_image({0, 0}, space_invaders::main_menu_title);
    msgui::Image menu_monster_image({100, 0}, space_invaders::main_menu_monster);
    msgui::Image menu_press_key_image({42, 50}, space_invaders::main_menu_press_key);

    // bool left_pressed = false;
    // bool right_pressed = false;
    // int fps = 0;

    // std::optional<space_invaders::Bullet> bullet;

    // std::array<space_invaders::MonsterLine, 4> monster_lines{
    //     space_invaders::MonsterLine({0, 10}, 0, 128),
    //     space_invaders::MonsterLine({20, 18}, 0, 128),
    //     space_invaders::MonsterLine({0, 26}, 0, 128),
    //     space_invaders::MonsterLine({20, 34}, 0, 128)};
    // std::chrono::milliseconds tt = hal::time::Time::milliseconds();
    // int move_position = 4;
    while (gamepad.read_event(&event))
    {
        // // printf("Loop\n");
        // switch (event.type)
        // {
        //     case drivers::EventType::Button:
        //     {
        //         if (event.value)
        //         {
        //             if (event.button_number == 1)
        //             {
        //                 if (!bullet)
        //                 {
        //                     auto bullet_position = player.position();
        //                     bullet_position.x += space_invaders::pad.width() / 2;
        //                     bullet_position.y += space_invaders::pad.height() - 1;

        //                     bullet.emplace(bullet_position, window_height);
        //                 }
        //             }
        //             if (event.button_number == 0)
        //             {
        //                 left_pressed = true;
        //             }
        //             if (event.button_number == 2)
        //             {
        //                 right_pressed = true;
        //             }
        //         }
        //         else
        //         {
        //             if (event.button_number == 0)
        //             {
        //                 left_pressed = false;
        //             }
        //             if (event.button_number == 2)
        //             {
        //                 right_pressed = false;
        //             }
        //         }
        //     } break;
        //     case drivers::EventType::Other:
        //     {

        //     } break;
        // }
        // if (left_pressed)
        // {
        //     player.move({-1, 0});
        // }
        // if (right_pressed)
        // {
        //     player.move({1, 0});
        // }
        // player.draw(display.get_fb());
        // if (bullet)
        // {
        //     if (bullet->move({0, -1}))
        //     {
        //         bullet->draw(display.get_fb());
        //         auto bullet_position = bullet->position();
        //         for (auto& monsters : monster_lines)
        //         {
        //             int killed_monster = monsters.has_collision({bullet_position.x, bullet_position.y + 2});
        //             if (killed_monster != -1)
        //             {
        //                 monsters.kill(killed_monster);
        //                 bullet.reset();
        //             }
        //         }

        //     }
        //     else
        //     {
        //         bullet.reset();
        //     }
        // }

        // for (auto& monsters : monster_lines)
        // {
        //     monsters.draw(display.get_fb());
        // }
        menu_image.draw(display.get_fb());
        menu_monster_image.draw(display.get_fb());
        menu_press_key_image.draw(display.get_fb());
        window.display();

        // if (hal::time::Time::milliseconds() - tt >= std::chrono::seconds(1))
        // {
        //     for (auto& monsters : monster_lines)
        //     {
        //         if (!monsters.move({move_position, 0}))
        //         {
        //             if (move_position > 0)
        //             {
        //                 move_position = -4;
        //             }
        //             else
        //             {
        //                 move_position = 4;
        //             }
        //         }
        //     }

        //     printf("FPS: %d\n", fps);
        //     fps = 0;
        //     tt = hal::time::Time::milliseconds();
        // }
        // else
        // {
        //     ++fps;
        // }
    }
    return 0;
}

REGISTER_APP(space_invaders, &app);
