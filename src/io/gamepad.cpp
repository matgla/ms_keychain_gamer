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
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "io/gamepad.hpp"

#include <cstdlib>

#include <fcntl.h>
#include <unistd.h>

#include "drivers/event.hpp"

namespace io
{

Gamepad& Gamepad::get()
{
    static Gamepad g;
    return g;
}

bool Gamepad::initialize(std::string_view device_path)
{
    if (fd_ < 0)
    {
        fd_ = open(device_path.data(), O_RDONLY);
    }
    return fd_ < 0 ? false : true;
}

void Gamepad::deinitialize()
{
    if (fd_ >= 0)
    {
        close(fd_);
        fd_ = -1;
    }
}

bool Gamepad::read_event(drivers::GamepadEvent* event)
{
    std::size_t bytes;
    bytes = read(fd_, event, sizeof(drivers::GamepadEvent));
    if (bytes == sizeof(drivers::GamepadEvent))
    {
        return true;
    }
    return false;
}


} // namespace io
