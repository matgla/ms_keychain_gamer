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

class Oscillator
{
public:
    Oscillator(uint32_t sample_rate)
        : sample_rate_(sample_rate)
    {
    }

    virtual ~Oscillator() = default;
    virtual uint8_t value(uint32_t frequency, uint32_t time) const = 0;

protected:
    uint32_t sample_rate_;
};


} // namespace synth
