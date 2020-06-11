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

#include "drivers/sfml_simulator/keyboard_driver_file.hpp"

#include <eul/utils/unused.hpp>

#include <cstring>

#include "msos/libc/printf.hpp"
#include "msos/os/input/input.h"

#include "drivers/sfml_simulator/keyboard_driver.hpp"

namespace drivers
{

KeyboardDriverFile::KeyboardDriverFile(std::string_view path)
    :  path_(path)
{
}

ssize_t KeyboardDriverFile::read(DataType data)
{
    if (data.size() < sizeof(input_event))
    {
        return 0;
    }
    std::memset(data.data(), 0, sizeof(input_event));

    std::optional<input_event> ev = drivers::KeyboardDriver::get().get_event();
    if (ev)
    {
        std::memcpy(data.data(), &(*ev), sizeof(*ev));
    }

    return 0;
}

int KeyboardDriverFile::close()
{
    return 0;
}


std::string_view KeyboardDriverFile::name() const
{
    return path_;
}


std::unique_ptr<msos::fs::IFile> KeyboardDriverFile::clone() const
{
    return std::make_unique<KeyboardDriverFile>(*this);
}

int KeyboardDriverFile::sync()
{
    KeyboardDriver::get().clear();
    return 1;
}

} // namespace drivers
