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

#include "synth/lib/envelope.hpp"

namespace synth
{

Envelope::Envelope(EnvelopeParameters params)
    : start_time_(0)
    , stop_time_(0)
    , params_(params)
    , state_(State::Off)
{
}

Envelope::Envelope()
    : start_time_(0)
    , stop_time_(0)
    , state_(State::Off)
{
}

void Envelope::on()
{

    if (state_ != State::Off)
    {
        return;
    }
    start_time_ = 0;
    stop_time_ = 0;
    state_ = State::StartTriggered;
}

bool Envelope::is_idle() const
{
    return state_ == State::Off;
}


void Envelope::off()
{
    if (stop_time_ != 0)
    {
        return;
    }
    prev_state_ = state_;
    state_ = State::ReleaseTriggered;
}

int Envelope::process(int time)
{
    int lifetime = time - start_time_;
    int out = 0;

    switch (state_)
    {
        case State::StartTriggered:
        {
            start_time_ = time;
            lifetime = time - start_time_;
            state_ = State::Attack;
            [[fallthrough]];
        }
        case State::Attack:
        {
            if (lifetime <= params_.attack_time)
            {
                if (params_.attack_time == 0)
                {
                    return params_.max_amplitude;
                }
                out = (lifetime * params_.max_amplitude) / params_.attack_time;
                break;
            }
            state_ = State::Decay;
            [[fallthrough]];
        }
        case State::Decay:
        {
            if (lifetime <= params_.attack_time + params_.decay_time)
            {
                if (params_.decay_time == 0)
                {
                    return params_.sustain_amplitude;
                }
                out = (lifetime - params_.attack_time) * (params_.sustain_amplitude - params_.max_amplitude) / params_.decay_time + params_.max_amplitude;
                break;
            }
            state_ = State::Sustain;
            [[fallthrough]];
        }
        case State::Sustain:
        {
            if (stop_time_ != 0)
            {
                stop_time_ = lifetime;
                state_ = State::Release;
            }

            return params_.sustain_amplitude;

        }
        case State::ReleaseTriggered:
        {
            if (prev_state_ != State::Sustain)
            {
                state_ = prev_state_;
            }
            else
            {
                state_ = State::Release;
            }
            stop_time_ = lifetime;

            [[fallthrough]];
        }
        case State::Release:
        {
            if (lifetime <= stop_time_ + params_.release_time)
            {
                out = (lifetime - stop_time_) * -1 * params_.sustain_amplitude / params_.release_time + params_.sustain_amplitude;
                break;
            }
            state_ = State::Off;
            [[fallthrough]];
        }
        case State::Off:
        {
            return 0;
        }
    }
    if (out < 0)
    {
        return 0;
    }
    return out;
}

std::optional<int> Envelope::process(uint32_t start_time, uint32_t stop_time, uint32_t time)
{
    uint32_t lifetime = time - start_time;
    int out = 0;
    // uint32_t stop = 0;

    if (lifetime <= params_.attack_time)
    {
        if (params_.attack_time == 0)
        {
            return params_.max_amplitude;
        }
        out = (lifetime * params_.max_amplitude) / params_.attack_time;
    }
    else if (lifetime <= params_.attack_time + params_.decay_time)
    {
        if (params_.decay_time == 0)
        {
            return params_.sustain_amplitude;
        }
        out = (lifetime - params_.attack_time) * (params_.sustain_amplitude - params_.max_amplitude) / params_.decay_time + params_.max_amplitude;
    }
    else if (stop_time == 0)
    {
        if (stop_time)
        {
        }
        return params_.sustain_amplitude;
    }
    else if (lifetime <= stop_time + params_.release_time)
    {
        out = 0;//(lifetime - stop_time) * -1 * params_.sustain_amplitude / params_.release_time + params_.sustain_amplitude;
    }
    else
    {
        return {};
    }
    return out < 0 ? 0 : out;
}

bool Envelope::is_finished(Note note, uint32_t time) const
{
    if (note.stop_time() != 0)
    {
        uint32_t lifetime = time - note.start_time();
        uint32_t envelope_time = params_.attack_time + params_.decay_time + params_.release_time;
        if (lifetime < envelope_time)
        {
            return false;
        }
        return true;
    }
    return false;
}



} // namespace synth
