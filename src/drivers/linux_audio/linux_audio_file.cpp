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

#include "drivers/linux_audio/linux_audio_file.hpp"

#include <fcntl.h>

#include <eul/utils/unused.hpp>

#include "msos/libc/printf.hpp"

#include "drivers/linux_audio/linux_audio.hpp"

#include <cstdio>

extern "C"
{
extern int __real_open(const char*, int);
extern int __real_ioctl(int fd, uint32_t cmd, ...);
extern int __real_write(int fd, const char* data, uint32_t size);
}

namespace drivers
{

LinuxAudioFile::LinuxAudioFile(LinuxAudio& driver, std::string_view path, int flags)
    : driver_(driver)
    , path_(path)
{
    fd_ = __real_open("/dev/dsp1", flags);
}

ssize_t LinuxAudioFile::read(DataType data)
{
    UNUSED1(data);
    return 0;
}

ssize_t LinuxAudioFile::write(const ConstDataType data)
{
    return __real_write(fd_, data.data(), data.size());
}

int LinuxAudioFile::close()
{
    return 0;
}


std::string_view LinuxAudioFile::name() const
{
    return path_;
}


std::unique_ptr<msos::fs::IFile> LinuxAudioFile::clone() const
{
    return std::make_unique<LinuxAudioFile>(*this);
}

int LinuxAudioFile::ioctl(uint32_t cmd, void* arg)
{
    return __real_ioctl(fd_, cmd, arg);
}



} // namespace drivers
