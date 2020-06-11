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

#include <array>
#include <chrono>

#include "io/framebuffer.hpp"
#include "monster_line.hpp"

namespace space_invaders
{

class Monsters
{
public:
    Monsters(io::Framebuffer& fb);

    bool move();

    void draw() const;

    int has_collision(msgui::Position position);
    void kill(int id);
    bool all_died() const;

    std::size_t size() const;

    const std::array<MonsterLine, 4>& get_monster_lines() const;
    const Monster1* get_monster(int id) const;

private:
    enum Direction
    {
        left,
        right
    };
    msgui::Position get_left_edge() const;
    msgui::Position get_right_edge() const;

    io::Framebuffer& fb_;
    std::array<MonsterLine, 4> lines_;
    std::chrono::milliseconds last_move_timestamp_;
    std::chrono::milliseconds move_speed_change_timestamp_;
    Direction direction_;
    int move_speed_;
};

} // namespace space_invaders
