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

#include "io/button_reader.hpp"

namespace io
{

ButtonsState get_buttons(const drivers::GamepadEvent& event)
{
    ButtonsState states {Button::State::no_action, Button::State::no_action, Button::State::no_action};

    switch (event.type)
    {
        case drivers::EventType::Button:
        {
            switch (event.button_number)
            {
                case 0:
                {
                    states.left_button.state = event.value == 1 ? Button::State::pressed : Button::State::released;
                } break;
                case 1:
                {
                    states.mid_button.state = event.value == 1 ? Button::State::pressed : Button::State::released;
                } break;
                case 2:
                {
                    states.right_button.state = event.value == 1 ? Button::State::pressed : Button::State::released;
                } break;
            }
        }
        default:
        {
        }
    }
    return states;
}

bool was_button_released(Button button)
{
    return button.state == Button::State::released;
}

bool was_button_pressed(Button button)
{
    return button.state == Button::State::pressed;
}

} // namespace io
