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

#include "synth/lib/note.hpp"

namespace synth
{

    Note::Note(int id)
        : id_(id)
        , start_time_(0)
        , stop_time_(0)
    {

    }

    void Note::on(uint32_t start_time)
    {
        start_time_ = start_time;
    }

    void Note::off(uint32_t stop_time)
    {
        stop_time_ = stop_time;
    }

    uint32_t Note::start_time() const
    {
        return start_time_;
    }

    uint32_t Note::stop_time() const
    {
        return stop_time_;
    }

    uint32_t Note::id() const
    {
        return id_;
    }

} // namespace synth
