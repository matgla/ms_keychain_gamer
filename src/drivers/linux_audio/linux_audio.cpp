// This file is part of MSOS project. This is simple OS for embedded development devices.
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

#include "drivers/linux_audio/linux_audio.hpp"

#include <unistd.h>
#include <fcntl.h>

#include "drivers/linux_audio/linux_audio_file.hpp"

namespace drivers
{

void LinuxAudio::load()
{
}

void LinuxAudio::unload()
{

}

std::unique_ptr<msos::fs::IFile> LinuxAudio::file(std::string_view path, int flags)
{
    return std::make_unique<LinuxAudioFile>(*this, path, flags);
}

} // namespace drivers
