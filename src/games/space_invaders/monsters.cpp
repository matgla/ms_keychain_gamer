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

#include "monsters.hpp"

#include <cmath>

#include <hal/time/time.hpp>

namespace space_invaders
{

Monsters::Monsters(io::Framebuffer& fb)
    : fb_(fb)
    , lines_{
        MonsterLine{{0, 10}, 0, 128},
        MonsterLine{{20, 18}, 0, 128},
        MonsterLine{{0, 26}, 0, 128},
        MonsterLine{{20, 34}, 0, 128}
    }
    , last_move_timestamp_{0}
    , move_speed_change_timestamp_{0}
    , direction_(Direction::right)
    , move_speed_(1100)
{
}

bool Monsters::move()
{
    if (hal::time::Time::milliseconds() - move_speed_change_timestamp_ >= std::chrono::seconds(5))
    {
        move_speed_change_timestamp_ = hal::time::Time::milliseconds();
        if (move_speed_ > 200)
        {
            move_speed_ -= 100;
        }
    }

    if (hal::time::Time::milliseconds() - last_move_timestamp_ < std::chrono::milliseconds(move_speed_))
    {
        return true;
    }
    last_move_timestamp_ = hal::time::Time::milliseconds();

    if (direction_ == Direction::left && get_left_edge().x - 4 < 0)
    {
        direction_ = Direction::right;
    }
    if (direction_ == Direction::right && get_right_edge().x + 4 > fb_.width() - monster_1.width())
    {
        direction_ = Direction::left;
    }

    msgui::Position position = {};

    if (direction_ == Direction::left)
    {
        position.x = -4;
    }
    else
    {
        position.x = 4;
    }

    for (auto& line : lines_)
    {
        line.move(position);
    }
    return true;
}

void Monsters::draw() const
{
    for (const auto& line : lines_)
    {
        line.draw(fb_);
    }
}

msgui::Position Monsters::get_left_edge() const
{
    msgui::Position edge{fb_.width(), 0};

    for (const auto& line : lines_)
    {
        auto position = line.get_left_edge();
        if (position)
        {
            if (position->x < edge.x)
            {
                edge = *position;
            }
        }
    }
    return edge;
}

msgui::Position Monsters::get_right_edge() const
{
    msgui::Position edge{0, 0};

    for (const auto& line : lines_)
    {
        auto position = line.get_right_edge();
        if (position)
        {
            if (position->x > edge.x)
            {
                edge = *position;
            }
        }
    }

    return edge;
}

int Monsters::has_collision(msgui::Position position)
{
    int line_index = 0;
    for (const auto& line : lines_)
    {
        int line_position = line.has_collision(position);
        if (line_position != -1)
        {
            return line_position + line_index;
        };
        line_index += 100;
    }
    return -1;
}

void Monsters::kill(int id)
{
    int line_index = std::floor(id / 100);
    lines_[line_index].kill(id - line_index*100);
}

bool Monsters::all_died() const
{
    for (const auto& line : lines_)
    {
        if (!line.empty())
        {
            return false;
        }
    }
    return true;
}

const std::array<MonsterLine, 4>& Monsters::get_monster_lines() const
{
    return lines_;
}

std::size_t Monsters::size() const
{
    std::size_t size = 0;
    for (const auto& line : lines_)
    {
        size += line.get_monsters().size();
    }
    return size;
}

const Monster1* Monsters::get_monster(int id) const
{
    int lines_sum = 0;
    for (const auto& line : lines_)
    {
        if (lines_sum + static_cast<int>(line.get_monsters().size()) > id)
        {
            return &(line.get_monsters()[id - lines_sum]);
        }
        lines_sum += line.get_monsters().size();
    }
    return nullptr;
}

} // namespace space_invaders
