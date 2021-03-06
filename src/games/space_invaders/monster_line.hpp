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
// along with this program. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <vector>

#include <optional>

#include "monster1.hpp"

namespace space_invaders
{

class MonsterLine
{
public:
    MonsterLine(msgui::Position position, uint16_t left_boundary, uint16_t right_boundary)
        : left_boundary_(left_boundary)
        , right_boundary_(right_boundary)
        , line_{
            Monster1({0 + position.x, 0 + position.y}, 0, 128),
            Monster1({15 + position.x, 0 + position.y}, 0, 128),
            Monster1({30 + position.x, 0 + position.y}, 0, 128),
            Monster1({45 + position.x, 0 + position.y}, 0, 128),
            Monster1({60 + position.x, 0 + position.y}, 0, 128)
        }
    {
    }

    bool move(const msgui::Position& position)
    {
        msgui::Position left_current_position = line_.front().position();
        msgui::Position right_current_position = line_.back().position();
        if (left_current_position.x + position.x >= left_boundary_ && right_current_position.x + position.x < (right_boundary_ - 8))
        {
            for (auto& monster : line_)
            {
                monster.move(position);
            }
            return true;
        }
        return false;
    }

    std::optional<msgui::Position> get_left_edge() const
    {
        if (line_.size())
        {
            return line_.front().position();
        }

        return std::optional<msgui::Position>();
    }

    std::optional<msgui::Position> get_right_edge() const
    {
        if (line_.size())
        {
            return line_.back().position();
        }

        return std::optional<msgui::Position>();
    }

    template <typename DriverType>
    void draw(DriverType& driver) const
    {
        for (auto& monster : line_)
        {
            monster.draw(driver);
        }
    }

    bool empty() const
    {
        return line_.empty();
    }

    int has_collision(const msgui::Position& position) const
    {
        int i = 0;
        for (auto& monster : line_)
        {
            if (monster.has_collision(position))
            {
                return i;
            }
            ++i;
        }
        return -1;
    }

    void kill(int id)
    {
        line_.erase(line_.begin() + id);
    }

    const std::vector<Monster1>& get_monsters() const
    {
        return line_;
    }


private:
    uint16_t left_boundary_;
    uint16_t right_boundary_;

    std::vector<Monster1> line_;
};

} // namespace space_invaders
