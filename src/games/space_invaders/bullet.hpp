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

#include <msgui/Position.hpp>
#include <msgui/Factory.hpp>
#include <msgui/Image.hpp>
#include <msgui/BitMap.hpp>

namespace space_invaders
{

constexpr static auto bullet = msgui::factory::make_bitmap<1, 3>(
    1,
    1,
    1
);

class Bullet
{
public:
    Bullet(const msgui::Position& position, uint16_t upper_boundary);
    bool move(const msgui::Position& position);

    template <typename DriverType>
    void draw(DriverType& driver)
    {
        texture_.draw(driver);
    }

    msgui::Position position() const
    {
        return texture_.get_position();
    }
private:
    short int upper_boundary_;
    msgui::Image<decltype(bullet)> texture_;
};

} // namespace space_invaders
