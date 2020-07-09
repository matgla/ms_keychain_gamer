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

#include "synth/lib/channel.hpp"

#include <algorithm>

#include "synth/lib/instrument.hpp"

#include <cstdio>

namespace synth
{

Channel::Channel(std::unique_ptr<Instrument>&& instrument)
    : instrument_(std::move(instrument))
{
}

Note* Channel::add_note(Note note)
{
    if (std::find_if(notes_.begin(), notes_.end(), [&note] (const Note& n) {
        return note.id() == n.id();
    }) != notes_.end())
    {
        return nullptr;
    }

    notes_.push_back(note);
    return &notes_.back();
}

Note* Channel::get_note(uint8_t id)
{
    auto note = std::find_if(notes_.begin(), notes_.end(), [id] (const Note& n) {
        return id == n.id();
    });

    if (note == notes_.end())
    {
        return nullptr;
    }
    return &(*note);
}

uint8_t Channel::get_sound(uint32_t time, uint32_t sample_rate)
{
    uint8_t sound = 0;

    for (auto it = notes_.begin(); it != notes_.end(); ++it)
    {
        auto part = instrument_->sound(*it, time, sample_rate);
        if (!part)
        {
            printf("erase\n");
            notes_.erase(it--);
        }
        else
        {
            sound += *part;
        }
    }

    return sound;
}

} // namespace synth
