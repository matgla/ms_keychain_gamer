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

#include "drivers/gamepad/gamepad_driver.hpp"

#include <memory>
#include <board.hpp>
#include <cstring>

#include <msos/libc/printf.hpp>

#include <hal/time/sleep.hpp>

#include <msos/drivers/device_fs.hpp>
#include <msos/kernel/process/spawn.hpp>
#include <msos/kernel/process/context_switch.hpp>

#include <msos/kernel/synchronization/mutex.hpp>

#include <eul/utils/unused.hpp>

#include "drivers/gamepad/gamepad_file.hpp"

namespace drivers
{

static msos::kernel::synchronization::Mutex mutex;

bool get_button_state(hal::gpio::DigitalInputOutputPin& pin)
{
    return pin.read();
}


GamepadDriver::GamepadDriver()
{
    state_.left.pressed =  get_button_state(board::gpio::LEFT_KEY::get());
    state_.mid.pressed =  get_button_state(board::gpio::MID_KEY::get());
    state_.right.pressed =  get_button_state(board::gpio::RIGHT_KEY::get());
}

void process_function(void* arg)
{
    UNUSED1(arg);
    while (true)
    {
        GamepadDriver::get().run();
        yield();
    }
}


void GamepadDriver::load()
{
    board::gpio::LEFT_KEY::get().init(hal::gpio::Input::InputPullUpDown);
    board::gpio::MID_KEY::get().init(hal::gpio::Input::InputPullUpDown);
    board::gpio::RIGHT_KEY::get().init(hal::gpio::Input::InputPullUpDown);

    spawn(process_function, NULL);
}

void GamepadDriver::unload()
{
}

GamepadDriver& GamepadDriver::get()
{
    static GamepadDriver d;
    return d;
}


void GamepadDriver::run()
{
    bool key_state = get_button_state(board::gpio::LEFT_KEY::get());
    if (state_.left.pressed != key_state)
    {
        state_.left.pressed = key_state;
        mutex.lock();
        events_.push(GamepadEvent{0, key_state ? static_cast<uint8_t>(0) : static_cast<uint8_t>(1), EventType::Button});
        mutex.unlock();
    }
    // mid
    key_state = get_button_state(board::gpio::MID_KEY::get());
    if (state_.mid.pressed != key_state)
    {
        state_.mid.pressed = key_state;
        mutex.lock();
        events_.push(GamepadEvent{1, key_state ? static_cast<uint8_t>(0) : static_cast<uint8_t>(1), EventType::Button});
        mutex.unlock();
    }
    // right
    key_state = get_button_state(board::gpio::RIGHT_KEY::get());
    if (state_.right.pressed != key_state)
    {
        state_.right.pressed = key_state;
        mutex.lock();
        events_.push(GamepadEvent{2, key_state ? static_cast<uint8_t>(0) : static_cast<uint8_t>(1), EventType::Button});
        mutex.unlock();
    }
}

GamepadEvent GamepadDriver::get_event()
{
    mutex.lock();
    if (events_.size() == 0)
    {
        events_.push(GamepadEvent{0, 0, EventType::Other});
    }
    GamepadEvent ev = events_.pop();
    mutex.unlock();
    return ev;
}

std::unique_ptr<msos::fs::IFile> GamepadDriver::file(std::string_view path, int flags)
{
    UNUSED1(flags);
    return std::make_unique<drivers::GamepadFile>(*this, path);
}

REGISTER_DRIVER(pad1, GamepadDriver::get());

} // namespace drivers

