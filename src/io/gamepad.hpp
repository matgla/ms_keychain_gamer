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

#pragma once

#include <string_view>

namespace drivers
{
class GamepadEvent;
} // namespace drivers

namespace io
{

class Gamepad
{
public:
    static Gamepad& get();

    bool initialize(std::string_view device_path);
    void deinitialize();
    bool read_event(drivers::GamepadEvent* event);
private:
    Gamepad() = default;
    int fd_ = -1;
};

} // namespace io
