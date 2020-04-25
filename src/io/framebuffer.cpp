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

#include "io/framebuffer.hpp"

#include <cstdio>
#include <cstring>
#include <cmath>

#include <unistd.h>

namespace io
{

FbDevice::FbDevice(int fd)
    : fd_(fd)
{
    std::memset(buffer_, 0, sizeof(buffer_));
}

void FbDevice::write()
{
    ::write(fd_, &buffer_, sizeof(buffer_));
}

void FbDevice::set_pixel(int x, int y)
{
    if (y >= height() || x >= width() || x < 0 || y < 0)
    {
        return;
    }
    int position_in_buffer = x + std::floor(y / 8) * 128;
    buffer_[position_in_buffer] |= 1 << (y % 8);
}

void FbDevice::sync()
{
    write();
    std::memset(buffer_, 0, sizeof(buffer_));
}

int FbDevice::fd() const
{
    return fd_;
}

} // namespace io
