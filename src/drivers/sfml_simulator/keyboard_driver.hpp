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

#include <bitset>
#include <queue>
#include <optional>

#include "msos/drivers/i_driver.hpp"

#include "msos/os/input/input.h"

namespace drivers
{

class KeyboardDriver : public msos::drivers::IDriver
{
public:
    static KeyboardDriver& get();

    void load() override;
    void unload() override;

    bool get_key_state(int key);

    void set_key_state(int key, bool state);

    std::unique_ptr<msos::fs::IFile> file(std::string_view path, int flags) override;

    std::optional<input_event> get_event();

    void clear();
private:
    KeyboardDriver();

    std::bitset<1024> keyboard_status_;
    std::queue<input_event> events_;
};

inline KeyboardDriver& create_keyboard_driver()
{
    return KeyboardDriver::get();
}

} // namespace drivers
