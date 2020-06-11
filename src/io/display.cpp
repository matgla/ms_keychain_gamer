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

#include "io/display.hpp"

#include <fcntl.h>
#include <unistd.h>

namespace io
{

Display::Display()
    : fb_(nullptr)
{

}

Display& Display::get()
{
    static Display d;
    return d;
}

bool Display::initialize(std::string_view device)
{
    if (fb_ == nullptr)
    {
        int fd = open(device.data(), O_RDONLY);
        if (fd >= 0)
        {
            static io::Framebuffer fb(fd);
            fb_ = &fb;
        }
    }

    return fb_ == nullptr ? false : true;
}

void Display::deinitialize()
{
    if (fb_ != nullptr)
    {
        close(fb_->fd());
    }
}

Framebuffer& Display::get_fb()
{
    return *fb_;
}

msgui::Factory<io::Framebuffer> Display::window_factory()
{
    return msgui::Factory<io::Framebuffer>(*fb_);
}

} // namespace io

