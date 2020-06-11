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

#include "drivers/sfml_simulator/sfml_simulator_file.hpp"

#include <eul/utils/unused.hpp>

#include "msos/libc/printf.hpp"

#include "drivers/sfml_simulator/sfml_simulator.hpp"

namespace drivers
{

SfmlFile::SfmlFile(SfmlSimulator& driver, std::string_view path)
    : driver_(driver)
    , path_(path)
{
}

ssize_t SfmlFile::read(DataType data)
{
    UNUSED1(data);
    return 0;
}

ssize_t SfmlFile::write(const ConstDataType data)
{
    driver_.write(data);
    return 0;
}

int SfmlFile::close()
{
    return 0;
}


std::string_view SfmlFile::name() const
{
    return path_;
}


std::unique_ptr<msos::fs::IFile> SfmlFile::clone() const
{
    return std::make_unique<SfmlFile>(*this);
}


} // namespace drivers
