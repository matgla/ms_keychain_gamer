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

Envelope::Envelope()
    : start_time_(0)
    , stop_time_(0)
    , start_amplitude_(0)
    , sustain_amplitude_(0)
    , attack_(0)
    , decay_(0)
    , sustain_(0)
    , release_(0)
    , state_(State::Off)
{

}

void Envelope::on()
{
    state_ = State::StartTriggered;
}

void Envelope::off()
{
    state_ = State::ReleaseTriggered;
}

int Envelope::process(int time)
{
    int lifetime = time - start_time_;

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
            if (lifetime <= attack_)
            {
                if (attack_ == 0)
                {
                    return start_amplitude_;
                }
                return (lifetime * start_amplitude_) / attack_;
            }
            state_ = State::Decay;
            [[fallthrough]];
        }
        case State::Decay:
        {
            if (lifetime <= attack_ + decay_)
            {
                if (decay_ == 0)
                {
                    return sustain_amplitude_;
                }
                return (lifetime - attack_) * (sustain_amplitude_ - start_amplitude_) / decay_ + start_amplitude_;
            }
            state_ = State::Sustain;
            [[fallthrough]];
        }
        case State::Sustain:
        {
            return sustain_amplitude_;
        }
        case State::ReleaseTriggered:
        {
            state_ = State::Release;
            stop_time_ = time;

            [[fallthrough]];
        }
        case State::Release:
        {
            if (lifetime <= stop_time_ + release_)
            {
                return (lifetime - stop_time_) * -1 * sustain_amplitude_ / release_ + sustain_amplitude_;
            }
            state_ = State::Off;
            [[fallthrough]];
        }
        case State::Off:
        {
            return 0;
        }
    }
    return 0;
}

} // namespace synth
