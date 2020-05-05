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

#include <msos/drivers/i_driver.hpp>

#include <eul/container/ring_buffer.hpp>

#include <vector>

#include "drivers/gamepad/event.hpp"

namespace drivers
{

struct ButtonState
{
    uint8_t pressed;
    uint8_t number;
};

struct GamepadState
{
    ButtonState left;
    ButtonState mid;
    ButtonState right;
};

// Probably this should work on different thread, or maybe use interrupts
class GamepadDriver : public msos::drivers::IDriver
{
public:
    void load() override;
    void unload() override;

    static GamepadDriver& get();

    void run();

    GamepadEvent get_event();


    std::unique_ptr<msos::fs::IFile> file(std::string_view path) override;
private:
    GamepadDriver();
    GamepadState state_;
    eul::container::ring_buffer<GamepadEvent, sizeof(GamepadEvent) * 6> events_;
};

} // namespace drivers

