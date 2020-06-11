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

#include "main_menu.hpp"

namespace space_invaders
{

MainMenu::MainMenu(io::Framebuffer& fb)
    : fb_(fb)
    , title_({0, 0}, space_invaders::main_menu_title)
    , monster_({100, 0}, space_invaders::main_menu_monster)
    , press_key_({42, 50}, space_invaders::main_menu_press_key)
{

}

void MainMenu::show()
{
    title_.draw(fb_);
    monster_.draw(fb_);
    press_key_.draw(fb_);
}

void MainMenu::process_event(Event ev)
{
    static_cast<void>(ev);
}

} // namespace space_invaders
