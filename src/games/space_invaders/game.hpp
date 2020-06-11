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

#include <cstdint>
#include <chrono>
#include <optional>
#include <string>
#include <vector>

#include <msgui/Text.hpp>
#include <msgui/fonts/Font5x7.hpp>

#include "io/framebuffer.hpp"

#include "bullet.hpp"
#include "monsters.hpp"
#include "player.hpp"


namespace space_invaders
{

class Game
{
public:
    Game(io::Framebuffer& fb);
    enum class Event
    {
        move_left_start,
        move_left_stop,
        move_right_start,
        move_right_stop,
        gunfire,
        game_step
    };

    void initialize();

    void process_event(Event event);
    void show();

    int finished() const;

private:
    void game_loop();

    io::Framebuffer& fb_;
    bool move_pad_left_;
    bool move_pad_right_;

    Player player_;
    std::optional<Bullet> bullet_;
    Monsters monsters_;
    bool finished_;
    int score_;
    msgui::Text<0, msgui::fonts::Font5x7::FontType> score_text_;
    char score_number_[6];
    msgui::Text<0, msgui::fonts::Font5x7::FontType> score_number_text_;
    int max_number_of_monster_bullets_;
    int current_number_of_monster_bullets_;
    std::array<std::optional<Bullet>, 25> monster_bullets_;
    std::chrono::milliseconds bullet_limit_timestamp_;
    std::chrono::milliseconds bullet_move_timestamp_;

};

} // namespace space_invaders
