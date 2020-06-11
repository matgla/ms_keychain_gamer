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

#include "bullet.hpp"

namespace space_invaders
{

constexpr static auto pad = msgui::factory::make_bitmap<9, 5>(
    0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 1, 1, 1, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1
);

class Player
{
public:
    Player(const msgui::Position& position, uint16_t left_boundary, uint16_t right_boundary);
    void move(const msgui::Position& position);

    template <typename DriverType>
    void draw(DriverType& driver)
    {
        texture_.draw(driver);
    }

    msgui::Position position() const;
    msgui::Position shot() const;

private:
    short int left_boundary_;
    short int right_boundary_;
    short int upper_boundary_;
    msgui::Image<decltype(pad)> texture_;
};

} // namespace space_invaders
