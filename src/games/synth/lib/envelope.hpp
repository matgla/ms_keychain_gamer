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
#include <optional>

#include "synth/lib/note.hpp"

namespace synth
{

struct EnvelopeParameters
{
public:
    EnvelopeParameters()
        : sustain_amplitude(0)
        , max_amplitude(0)
        , attack_time(0)
        , decay_time(0)
        , release_time(0)
    {
    }

    uint8_t sustain_amplitude;
    uint8_t max_amplitude;

    uint16_t attack_time;
    uint16_t decay_time;
    uint16_t release_time;
};

class Envelope
{
public:
    Envelope(EnvelopeParameters params);
    Envelope();

    void on();
    void off();

    constexpr Envelope& attack_time(int time)
    {
        params_.attack_time = time;
        return *this;
    }

    constexpr Envelope& max_amplitude(int amplitude)
    {
        params_.max_amplitude = amplitude;
        return *this;
    }

    constexpr Envelope& sustain_amplitude(int amplitude)
    {
        params_.sustain_amplitude = amplitude;
        return *this;
    }

    constexpr Envelope& decay_time(int time)
    {
        params_.decay_time = time;
        return *this;
    }

    constexpr Envelope& release_time(int time)
    {
        params_.release_time = time;
        return *this;
    }

    bool is_idle() const;
    bool is_finished(Note note, uint32_t time) const;

    int process(int time);
    std::optional<int> process(uint32_t start_time, uint32_t stop_time, uint32_t time);
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
    EnvelopeParameters params_;

    State state_;
    State prev_state_;
};

} // namespace synth
