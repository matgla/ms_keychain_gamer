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
#include <msgui/AnimatedSprite.hpp>
#include <msgui/BitMap.hpp>

namespace space_invaders
{

template <typename BitmapType>
class MonsterBase
{
public:
    MonsterBase(const msgui::Position& position, uint16_t left_boundary, uint16_t right_boundary, const BitmapType& bitmap)
        : left_boundary_(left_boundary)
        , right_boundary_(right_boundary)
        , texture_(position, bitmap, 8, 1000)
    {
    }

    void move(const msgui::Position& position)
    {
        msgui::Position current_position = texture_.get_position();
        if (current_position.x + position.x >= left_boundary_ && current_position.x + position.x < (right_boundary_ - 8))
        {
            texture_.move(position);
        }
    }

    template <typename DriverType>
    void draw(DriverType& driver) const
    {
        texture_.draw(driver);
    }

    msgui::Position position() const
    {
        return texture_.get_position();
    }

    bool has_collision(const msgui::Position& pos) const
    {
        auto position = texture_.get_position();
        position.x = pos.x - position.x;
        position.y = pos.y - position.y;

        return texture_.has_pixel(position);
    }

    MonsterBase<BitmapType>& operator=(const MonsterBase<BitmapType>& other)
    {
        left_boundary_ = other.left_boundary_;
        right_boundary_ = other.right_boundary_;
        texture_ = other.texture_;
        return *this;
    }

    msgui::Position shot() const
    {
        auto bullet_position = texture_.get_position();

        bullet_position.x += texture_.sprite_width() / 2;
        bullet_position.y += texture_.bitmap().height() - 1;
        return bullet_position;
    }

private:
    short int left_boundary_;
    short int right_boundary_;
    msgui::AnimatedSprite<BitmapType> texture_;
};

} // namespace space_invaders
