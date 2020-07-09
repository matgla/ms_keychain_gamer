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
#include <memory>
#include <vector>

#include "synth/lib/note.hpp"
#include "synth/lib/instrument.hpp"

namespace synth
{

class Instrument;

class Channel
{
public:
    Channel(std::unique_ptr<Instrument>&& instrument);
    Note* add_note(Note note);
    Note* get_note(uint8_t id);

    uint8_t get_sound(uint32_t time, uint32_t sample_rate);
private:
    std::vector<Note> notes_;
    std::unique_ptr<Instrument> instrument_;
};

} // namespace synth
