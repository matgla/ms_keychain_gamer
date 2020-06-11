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

class Envelope
{
public:
    Envelope();

    void on();
    void off();

    constexpr Envelope& attack_time(int time)
    {
        attack_ = time;
        return *this;
    }

    constexpr Envelope& max_amplitude(int amplitude)
    {
        start_amplitude_ = amplitude;
        return *this;
    }

    constexpr Envelope& sustain_amplitude(int amplitude)
    {
        sustain_amplitude_ = amplitude;
        return *this;
    }

    constexpr Envelope& decay_time(int time)
    {
        decay_ = time;
        return *this;
    }

    constexpr Envelope& release_time(int time)
    {
        release_ = time;
        return *this;
    }


    int process(int time);
private:
    enum class State
    {
        StartTriggered,
        Attack,
        Decay,
        Sustain,
        Release,
        ReleaseTriggered,
        Off
    };

    int start_time_;
    int stop_time_;
    int start_amplitude_;
    int sustain_amplitude_;
    int attack_;
    int decay_;
    int sustain_;
    int release_;

    State state_;
};

} // namespace synth
