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

#include "drivers/gamepad_file.hpp"

#include <cstring>

#include <eul/utils/unused.hpp>


namespace drivers
{

GamepadFile::GamepadFile(GamepadDriver& driver, std::string_view path)
    : driver_(driver)
    , path_(path)
{
}

int number = 0;
ssize_t GamepadFile::read(DataType data)
{
    if (data.size() < sizeof(GamepadEvent))
    {
        return 0;
    }
    drivers::GamepadEvent ev = driver_.get_event();
    std::memcpy(data.data(), &ev, sizeof(GamepadEvent));
    return sizeof(GamepadEvent);
}
int GamepadFile::close()
{
    return 0;
}

std::string_view GamepadFile::name() const
{
    return path_;
}

std::unique_ptr<msos::fs::IFile> GamepadFile::clone() const
{
    return std::make_unique<GamepadFile>(*this);
}

} // namespace drivers

