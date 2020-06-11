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

#include <msgui/Area.hpp>
#include <msgui/Position.hpp>

#include "io/framebuffer.hpp"


namespace space_invaders
{

template <typename Texture>
class Object
{
public:
    virtual ~Object() = default;
    Object(const msgui::Position& position, const msgui::Area& boundary, io::Framebuffer& fb);

    bool move(const msgui::Position& position);
    void draw();

    template <typename OtherTexture>
    bool has_collision(const Object<OtherTexture>& object)
    {
        const auto& other_bitmap = object.get_bitmap();
        const auto& bitmap = texture_.get_bitmap();
        for (int i )
        object.sprite_.
        return true;
    }


private:
    Texture sprite_;
    msgui::Area boundary_;
    io::Framebuffer fb_;
};

} // namespace space_invaders
