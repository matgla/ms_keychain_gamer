#pragma once

#include <cstdint>

namespace space_invaders
{

class Game
{
public:
    void start();

private:
    void show_menu();
    void game_loop();

    enum class State : uint8_t
    {

    };
};

} // namespace space_invaders
