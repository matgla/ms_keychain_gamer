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

#include "player.hpp"

namespace space_invaders
{

Player::Player(const msgui::Position& position, uint16_t left_boundary, uint16_t right_boundary)
    : left_boundary_(left_boundary)
    , right_boundary_(right_boundary)
    , texture_(position, pad)
{

}

void Player::move(const msgui::Position& position)
{
    msgui::Position current_position = texture_.get_position();
    if (current_position.x + position.x >= left_boundary_ && current_position.x + position.x < (right_boundary_ - texture_.bitmap().width()))
    {
        texture_.move(position);
    }
}

msgui::Position Player::position() const
{
    return texture_.get_position();
}

} // namespace space_invaders
