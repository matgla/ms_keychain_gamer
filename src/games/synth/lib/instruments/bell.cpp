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

#include "synth/lib/instruments/bell.hpp"

#include "synth/lib/oscillators/sine.hpp"
#include "synth/lib/note_frequency.hpp"

#include <cstdio>

namespace synth
{
namespace instruments
{

Bell::Bell()
{
    envelope_.attack_time = 100;
    envelope_.max_amplitude = 255;
    envelope_.sustain_amplitude = 200;
    envelope_.decay_time = 50;
    envelope_.release_time = 100;
}

std::optional<uint8_t> Bell::sound(Note note, uint32_t time, uint32_t sample_rate)
{
    auto note_volume = Envelope(envelope_).process(note.start_time(), note.stop_time(), time);
    if (note_volume.has_value())
    {
        uint8_t value = *note_volume * Sine{sample_rate}.value(get_note_frequency(note.id()), time) / 255;
        return value;
    }
    return {};
}

} // namespace instruments
} // namespace synth
