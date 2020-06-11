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
// along with this program. If not, see <https://www.gnu.org/licenses/>.

#include <gtest/gtest.h>

#include "synth/lib/envelope.hpp"

TEST(EnvelopeShould, DoNothingWhenAllParamsAreZero)
{
    synth::Envelope sut;
    EXPECT_EQ(sut.process(0), 0);
    EXPECT_EQ(sut.process(1), 0);
    EXPECT_EQ(sut.process(10), 0);
    EXPECT_EQ(sut.process(100), 0);
}

TEST(EnvelopeShould, DoAttack)
{
    synth::Envelope sut;
    sut
        .max_amplitude(10)
        .attack_time(100)
        .sustain_amplitude(7);

    EXPECT_EQ(sut.process(0), 0);
    sut.on();
    EXPECT_EQ(sut.process(0), 0);
    EXPECT_EQ(sut.process(50), 5);
    EXPECT_EQ(sut.process(100), 10);
    EXPECT_EQ(sut.process(100), 10);
    EXPECT_EQ(sut.process(101), 7);
}

TEST(EnvelopeShould, DoDecay)
{
    synth::Envelope sut;
    sut
        .max_amplitude(10)
        .decay_time(20)
        .sustain_amplitude(5);

    EXPECT_EQ(sut.process(0), 0);
    sut.on();
    EXPECT_EQ(sut.process(0), 10);
    EXPECT_EQ(sut.process(10), 8);
    EXPECT_EQ(sut.process(20), 5);
    EXPECT_EQ(sut.process(25), 5);
}

TEST(EnvelopeShould, DoSustain)
{
    synth::Envelope sut;
    sut
        .sustain_amplitude(5);

    EXPECT_EQ(sut.process(0), 0);
    sut.on();
    EXPECT_EQ(sut.process(0), 0);
    EXPECT_EQ(sut.process(10), 5);
    EXPECT_EQ(sut.process(20), 5);
    EXPECT_EQ(sut.process(25), 5);
}

TEST(EnvelopeShould, DoRelease)
{
    synth::Envelope sut;
    sut
        .sustain_amplitude(5)
        .release_time(10);

    EXPECT_EQ(sut.process(0), 0);
    sut.on();
    EXPECT_EQ(sut.process(0), 0);
    EXPECT_EQ(sut.process(1), 5);
    sut.off();
    EXPECT_EQ(sut.process(1), 5);
    EXPECT_EQ(sut.process(3), 4);
    EXPECT_EQ(sut.process(5), 3);
    EXPECT_EQ(sut.process(7), 2);
    EXPECT_EQ(sut.process(9), 1);
    EXPECT_EQ(sut.process(11), 0);
}

TEST(EnvelopeShould, PerformAdsr)
{
    synth::Envelope sut;
    sut
        .attack_time(10)
        .max_amplitude(10)
        .decay_time(5)
        .sustain_amplitude(5)
        .release_time(20);

    EXPECT_EQ(sut.process(0), 0);
    sut.on();
    EXPECT_EQ(sut.process(0), 0);
    EXPECT_EQ(sut.process(5), 5);
    EXPECT_EQ(sut.process(10), 10);
    EXPECT_EQ(sut.process(13), 7);
    EXPECT_EQ(sut.process(15), 5);
    EXPECT_EQ(sut.process(20), 5);
    sut.off();
    EXPECT_EQ(sut.process(20), 5);
    EXPECT_EQ(sut.process(25), 4);
    EXPECT_EQ(sut.process(30), 3);
    EXPECT_EQ(sut.process(35), 2);
    EXPECT_EQ(sut.process(45), 0);
}
