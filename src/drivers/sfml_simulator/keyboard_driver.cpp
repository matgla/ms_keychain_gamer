// This file is part of MSOS project.
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

#include "drivers/sfml_simulator/keyboard_driver.hpp"

#include "drivers/sfml_simulator/keyboard_driver_file.hpp"


namespace drivers
{

void KeyboardDriver::load()
{

}

void KeyboardDriver::unload()
{

}

KeyboardDriver& KeyboardDriver::get()
{
    static KeyboardDriver driver;
    return driver;
}

void KeyboardDriver::clear()
{
    std::queue<input_event> empty{};
    std::swap(events_, empty);
}

bool KeyboardDriver::get_key_state(int key)
{
    return keyboard_status_.test(key);
}

void KeyboardDriver::set_key_state(int key, bool state)
{
    if (state)
    {
        if (keyboard_status_.test(key) != state)
        {
            input_event ev;
            ev.code = key;
            ev.type = EV_KEY;
            ev.value = 1;
            events_.push(ev);
        }
        keyboard_status_.set(key);
    }
    else
    {
        if (keyboard_status_.test(key) != state)
        {
            input_event ev;
            ev.code = key;
            ev.type = EV_KEY;
            ev.value = 0;
            events_.push(ev);
        }
        keyboard_status_.reset(key);
    }
}


std::optional<input_event> KeyboardDriver::get_event()
{
    if (events_.size())
    {
        input_event ev = events_.front();
        events_.pop();
        return ev;
    }
    return {};
}


KeyboardDriver::KeyboardDriver()
{
}

std::unique_ptr<msos::fs::IFile> KeyboardDriver::file(std::string_view path, int flags)
{
    static_cast<void>(flags);

    return std::make_unique<KeyboardDriverFile>(path);
}

} // namespace drivers
