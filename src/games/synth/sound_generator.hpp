#pragma once

#include <cstdint>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <string_view>
#include <cmath>

#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sound/soundcard.h>

template <typename SampleType>
class SoundGenerator
{
public:
    SoundGenerator(std::string_view output_device, std::size_t sample_rate, uint8_t number_of_channels, int number_of_blocks, int block_size)
    : sample_rate_(sample_rate)
    , number_of_channels_(number_of_channels)
    , number_of_blocks_(number_of_blocks)
    , block_size_(block_size)
    , number_of_writes_(0)
    , sound_function_(nullptr)
    , time_(0)
    , output_device_(output_device)
    {
        buffer_.resize(block_size);
    }

    int open()
    {
        fd_ = ::open(output_device_.data(), O_WRONLY | O_NONBLOCK);
        printf("Sound generator has fd: %d\n", fd_);
        if (fd_ < 0)
        {
            return -1;
        }
        int bits = AFMT_U8;
        if (ioctl(fd_, SNDCTL_DSP_SETFMT, &bits) == -1)
        {
            return -2;
        }

        if (ioctl(fd_, SNDCTL_DSP_CHANNELS, &number_of_channels_) == -1)
        {
            return -3;
        }
        if (ioctl(fd_, SNDCTL_DSP_SPEED, &sample_rate_) == -1)
        {
            return -4;
        }

        int i = 1;
        for (i = 1; i < 16; i++)
        {
            if (block_size_ >> (i + 1) == 0)
            {
                break;
            }
        }

        int fragment_size = number_of_blocks_ << 16 | i;
        ioctl(fd_, SNDCTL_DSP_SETFRAGMENT, &fragment_size);

        int info = 0;
        ioctl(fd_, SNDCTL_DSP_GETBLKSIZE, &info);
        audio_buf_info buffer_info;

        if (ioctl(fd_, SNDCTL_DSP_GETOSPACE, &buffer_info) == -1)
        {
            printf("error\n");
            return -1;
        }
        ioctl(fd_, SNDCTL_DSP_NONBLOCK, NULL);
        return 0;
    }

    void poll()
    {
        audio_buf_info buffer_info;
        ioctl(fd_, SNDCTL_DSP_GETOSPACE, &buffer_info);
        if (0 == buffer_info.fragments)
        {
            return;
        }

        if (sound_function_ == nullptr)
        {
            return;
        }
        for (std::size_t i = 0; i < buffer_.size(); ++i)
        {
            buffer_[i] = sound_function_(time_);
            time_ += 1/(double)(sample_rate_);
        }

        write(fd_, buffer_.data(), buffer_.size());

    }

    void set_function(SampleType (*sound_fun)(double))
    {
        sound_function_ = sound_fun;
    }

private:
    int sample_rate_;
    int number_of_channels_;
    int number_of_blocks_;
    int block_size_;
    int number_of_writes_;
    std::vector<SampleType> buffer_;
    int fd_;
    SampleType (*sound_function_)(double);
    double time_;
    std::string_view output_device_;
};
