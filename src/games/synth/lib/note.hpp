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

#include <cstdint>

namespace synth
{

class Note
{
public:
    Note(int id);

    void on(uint32_t start_time);
    void off(uint32_t stop_time);

    uint32_t start_time() const;
    uint32_t stop_time() const;

    uint32_t id() const;
    void process(uint32_t time);

private:
    uint32_t id_;
    uint32_t start_time_;
    uint32_t stop_time_;
};

} // namespace synth
