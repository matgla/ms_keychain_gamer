#include <msos/apps/app_registry.hpp>

#include <msos/os/input/input.h>

#include "sound_generator.hpp"

double frequency = 440.0;

uint8_t generate_sound(double delta_time)
{
    double val = (sin(delta_time * 2.0 * 3.14 * frequency) + 1) / 2;
    uint8_t out = 255 * val;

    return out;
}

constexpr std::array<uint32_t, 32> notes{
    261, // C4
    277, // C4#
    293, // D4
    311, // D4#
    329, // E4
    349, // F4
    369, // F4#
    392, // G4
    415, // G4#
    449, // A4
    466, // A4#
    493, // B4
    523, // C5
    554, // C5#
    587, // D5
    622, // D5#
    659, // E5
    698, // F5
    739, // F5#
    783, // G5
    830, // G5#
    880, // A5
    932, // A5#
    987, // B5
};

uint32_t get_key_frequency(input_event ev)
{
    uint32_t freq = 0;
    switch (ev.code)
    {
        case keys::KEY_Z: freq = notes[0]; break;
        case keys::KEY_S: freq = notes[1]; break;
        case keys::KEY_X: freq = notes[2]; break;
        case keys::KEY_D: freq = notes[3]; break;
        case keys::KEY_C: freq = notes[4]; break;
        case keys::KEY_V: freq = notes[5]; break;
        case keys::KEY_G: freq = notes[6]; break;
        case keys::KEY_B: freq = notes[7]; break;
        case keys::KEY_H: freq = notes[8]; break;
        case keys::KEY_N: freq = notes[9]; break;
        case keys::KEY_J: freq = notes[10]; break;
        case keys::KEY_M: freq = notes[11]; break;
        case keys::KEY_COMMA: freq = notes[12]; break;
        case keys::KEY_L: freq = notes[13]; break;
        case keys::KEY_DOT: freq = notes[14]; break;
        case keys::KEY_SEMICOLON: freq = notes[15]; break;
        case keys::KEY_SLASH: freq = notes[16]; break;
    }
    return freq;
}

int synth_app()
{
    SoundGenerator<uint8_t> generator("/dev/dsp1", 8000, 1, 2, 512);

    printf("  C4  c4# D  D#   E    F    F#  G  G#  A  A#  H     C   C#  D  D#  E \n");
    printf(" _____________________________________________________________________\n");
    printf("|    |   |  |   |    |    |   |  |   |  |   |    |    |   |  |   |    |\n");
    printf("|    |   |  |   |    |    |   |  |   |  |   |    |    |   |  |   |    |\n");
    printf("|    | S |  | D |    |    | G |  | H |  | J |    |    | L |  | ; |    |\n");
    printf("|    |   |  |   |    |    |   |  |   |  |   |    |    |   |  |   |    |\n");
    printf("|    |___|  |___|    |    |___|  |___|  |___|    |    |___|  |___|    |\n");
    printf("|      |      |      |      |      |      |      |      |      |      |\n");
    printf("|      |      |      |      |      |      |      |      |      |      |\n");
    printf("|  Z   |  X   |  C   |  V   |  B   |  N   |  M   |  ,   |  .   |  /   |\n");
    printf("|      |      |      |      |      |      |      |      |      |      |\n");
    printf("|______|______|______|______|______|______|______|______|______|______|\n");

    int code = generator.open();
    if (code != 0)
    {
        printf("Can't open: %d\n", code);
        return -1;
    }
    generator.set_function(&generate_sound);

    int keyboard = open("/dev/keyboard", O_RDONLY | O_NONBLOCK);

    if (keyboard < 0)
    {
        printf("Can't find /dev/keyboard\n");
        return -1;
    }
    fsync(keyboard);
    input_event ev;
    while (true)
    {
        read(keyboard, &ev, sizeof(input_event));
        if (ev.type == EV_KEY)
        {
            if (ev.value)
            {
                frequency = get_key_frequency(ev);
            }
            else
            {
                if (frequency == get_key_frequency(ev))
                {
                    frequency = 0;
                }
            }

        }
        generator.poll();
    }
}

REGISTER_APP(synth_app, &synth_app);
