// This file is part of MSOS project. This is simple OS for embedded development devices.
// Copyright (C) 2020 Mateusz Stadnik
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

#include "drivers/sfml_simulator/sfml_simulator.hpp"

#include <cstring>

#include <iostream>
#include <thread>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <board.hpp>

#include <hal/time/sleep.hpp>

#include "msos/usart_printer.hpp"
#include "drivers/sfml_simulator/sfml_simulator_file.hpp"

namespace drivers
{

static UsartWriter writer;

SfmlSimulator::SfmlSimulator()
{
    screen_.create(128, 64);
}

void SfmlSimulator::load()
{
    thread_ = std::make_unique<std::thread>([this]{
        sf::RenderWindow window(sf::VideoMode(148, 128), "MsKeychainGamer");
        sf::RectangleShape device;


        device.setSize(sf::Vector2f(140, 120));
        device.setOutlineColor(sf::Color::Blue);
        device.setFillColor(sf::Color::Green);
        device.setOutlineThickness(4);
        device.setPosition(4, 4);

        sf::CircleShape left_button;
        sf::CircleShape mid_button;
        sf::CircleShape right_button;

        int button_size = 10;
        left_button.setRadius(button_size);
        int button_offset = (device.getSize().x + device.getOutlineThickness() - button_size * 3) / 4;
        left_button.setPosition(button_offset, device.getSize().y - button_offset);

        mid_button.setRadius(button_size);
        mid_button.setPosition(button_offset * 2 + button_size, device.getSize().y - button_offset);

        right_button.setRadius(button_size);
        right_button.setPosition(button_offset * 3 + button_size * 2, device.getSize().y - button_offset);

        std::cout << window.getSize().x << ", " << window.getSize().y << std::endl;
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(device);
            window.draw(left_button);
            window.draw(mid_button);
            window.draw(right_button);
            buffer_mutex_.lock();
            sf::Texture tex;
            tex.loadFromImage(screen_);
            sf::Sprite spr;
            auto device_size = device.getSize();
            int screen_offset = (device_size.x + device.getOutlineThickness() * 2- tex.getSize().x)/2;
            spr.setPosition(screen_offset, screen_offset);
            spr.setTexture(tex);
            window.draw(spr);
            buffer_mutex_.unlock();
            window.display();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                board::gpio::LEFT_KEY::get().setHigh();
            }
            else
            {
                board::gpio::LEFT_KEY::get().setLow();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                board::gpio::MID_KEY::get().setHigh();
            }
            else
            {
                board::gpio::MID_KEY::get().setLow();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                board::gpio::RIGHT_KEY::get().setHigh();
            }
            else
            {
                board::gpio::RIGHT_KEY::get().setLow();
            }
        }
    });
}

bool SfmlSimulator::busy()
{
    return false;
}

void SfmlSimulator::unload()
{
}

void SfmlSimulator::clear()
{
}

void SfmlSimulator::display(const gsl::span<uint8_t>& buffer)
{
    UNUSED1(buffer);
}

void SfmlSimulator::write(const uint8_t byte)
{

    UNUSED1(byte);
}

void SfmlSimulator::write(gsl::span<const char> buffer)
{
    UNUSED1(buffer);
    int x = 0;
    int y = 0;
    buffer_mutex_.lock();
    for (auto byte : buffer)
    {
        if (x == 128)
        {
            y += 8;
            x = 0;
        }
        for (int bit = 0; bit < 8; ++bit)
        {

            if (byte & (1 << bit))
            {
                screen_.setPixel(x, y+bit, sf::Color::White);
            }
            else
            {
                screen_.setPixel(x, y+bit, sf::Color::Black);
            }
        }
        x++;
    }
    buffer_mutex_.unlock();
}

std::unique_ptr<msos::fs::IFile> SfmlSimulator::file(std::string_view path)
{
    return std::make_unique<SfmlFile>(*this, path);
}

} // namespace drivers
