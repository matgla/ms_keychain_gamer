#include <msos/apps/app_registry.hpp>

#include <msos/os/input/input.h>

#include "lib/envelope.hpp"

#include "sound_generator.hpp"
#include "lib/channel.hpp"
#include "lib/instruments/bell.hpp"

double frequency = 440.0;

synth::Channel channel(std::make_unique<synth::instruments::Bell>());

namespace
{
    constexpr uint32_t sample_rate = 8000;
}

uint32_t current_time = 0;
uint8_t generate_sound(uint32_t delta_time/* ticks */)
{
    // uint8_t val = env.process(delta_time * 1000) * (sin(delta_time * 2.0 * 3.14 * frequency) + 1) / 2;
    current_time = delta_time;

    auto val = channel.get_sound(current_time, sample_rate);
    return val;
}

// constexpr std::array<uint32_t, 32> notes{
 //     261, // C4
//     277, // C4#
//     293, // D4
//     311, // D4#
//     329, // E4
//     349, // F4
//     369, // F4#
//     392, // G4
//     415, // G4#
//     449, // A4
//     466, // A4#
//     493, // B4
//     523, // C5
//     554, // C5#
//     587, // D5
//     622, // D5#
//     659, // E5
//     698, // F5
//     739, // F5#
//     783, // G5
//     830, // G5#
//     880, // A5
//     932, // A5#
//     987, // B5
// };

uint32_t get_frequency(int id)
{
    return 256 * pow(1.0594630943592952645618252949463, id);
}

uint32_t get_key_frequency(input_event ev)
{
    uint32_t freq = 0;
    switch (ev.code)
    {
        case keys::KEY_Z: freq = 0; break;
        case keys::KEY_S: freq = 1; break;
        case keys::KEY_X: freq = 2; break;
        case keys::KEY_D: freq = 3; break;
        case keys::KEY_C: freq = 4; break;
        case keys::KEY_V: freq = 5; break;
        case keys::KEY_G: freq = 6; break;
        case keys::KEY_B: freq = 7; break;
        case keys::KEY_H: freq = 8; break;
        case keys::KEY_N: freq = 9; break;
        case keys::KEY_J: freq = 10; break;
        case keys::KEY_M: freq = 11; break;
        case keys::KEY_COMMA: freq = 12; break;
        case keys::KEY_L: freq = 13; break;
        case keys::KEY_DOT: freq = 14; break;
        case keys::KEY_SEMICOLON: freq = 15; break;
        case keys::KEY_SLASH: freq = 16; break;
    }
    return freq;
}

int synth_app()
{
    SoundGenerator<uint8_t> generator("/dev/dsp1", sample_rate, 1, 3, 512);

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
    // channel.get_note(1)->on(current_time);
    while (true)
    {
        read(keyboard, &ev, sizeof(input_event));
        if (ev.type == EV_KEY)
        {
            if (ev.value)
            {
                auto* note = channel.add_note(synth::Note(get_key_frequency(ev)));
                if (note)
                {
                    printf("On\n");
                    note->on(current_time);
                }
            }
            else
            {
                auto* note = channel.get_note(get_key_frequency(ev));
                if (note)
                {
                    printf("Off\n");
                    note->off(current_time);
                }
            }

        }
        generator.poll();
    }
}

REGISTER_APP_AUTOSTART(synth_app, &synth_app);
