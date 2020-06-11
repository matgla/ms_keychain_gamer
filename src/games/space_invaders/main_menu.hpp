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

#pragma once

#include <msgui/Image.hpp>

#include "assets/main_menu_title.hpp"
#include "assets/main_menu_monster.hpp"
#include "assets/main_menu_press_key.hpp"
#include "io/framebuffer.hpp"

namespace space_invaders
{

class MainMenu
{
public:
    enum class Event
    {
        StartGame
    };

    MainMenu(io::Framebuffer& fb);

    void show();
    void process_event(Event ev);

private:
    io::Framebuffer& fb_;
    msgui::Image<decltype(main_menu_title)> title_;
    msgui::Image<decltype(main_menu_monster)> monster_;
    msgui::Image<decltype(main_menu_press_key)> press_key_;

};

} // namespace space_invaders
