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

#include "bullet.hpp"

namespace space_invaders
{

Bullet::Bullet(const msgui::Position& position, uint16_t upper_boundary)
    : upper_boundary_(upper_boundary)
    ,texture_(position, bullet)

{
}

bool Bullet::move(const msgui::Position& position)
{
    if (texture_.get_position().y + position.y >= 0)
    {
        texture_.move(position);
        return true;
    }
    return false;
}

} // namespace space_invaders
