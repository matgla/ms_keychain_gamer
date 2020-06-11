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

#include "game.hpp"

#include <cstdio>

#include <eul/utils/string.hpp>

#include <hal/time/time.hpp>

namespace space_invaders
{

Game::Game(io::Framebuffer& fb)
    : fb_(fb)
    , move_pad_left_(false)
    , move_pad_right_(false)
    , player_(msgui::Position{(fb.width() - space_invaders::pad.width()) / 2, fb.height() - space_invaders::pad.height()}, 0 , fb.width())
    , monsters_(fb)
    , finished_(false)
    , score_(0)
    , score_text_("score: ", {-1, -1}, msgui::fonts::Font5x7::data, msgui::colors::black())
    , score_number_{'0'}
    , score_number_text_(score_number_, {40, 0}, msgui::fonts::Font5x7::data, msgui::colors::black())
    , max_number_of_monster_bullets_(1)
    , current_number_of_monster_bullets_(0)
    , bullet_limit_timestamp_(hal::time::Time::milliseconds())
    , bullet_move_timestamp_(hal::time::Time::milliseconds())
{
    srand(time(NULL));
}

void Game::initialize()
{

}

void Game::process_event(Event event)
{
    switch (event)
    {
        case Event::move_left_start:
        {
            move_pad_left_ = true;
        } break;
        case Event::move_right_start:
        {
            move_pad_right_ = true;
        } break;
        case Event::move_left_stop:
        {
            move_pad_left_ = false;
        } break;
        case Event::move_right_stop:
        {
            move_pad_right_ = false;
        } break;
        case Event::gunfire:
        {
            if (!bullet_)
            {
                bullet_.emplace(player_.shot(), fb_.height());
            }
        } break;
        case Event::game_step:
        {
            game_loop();
        } break;
    }
}

void Game::show()
{
    player_.draw(fb_);
}

int Game::finished() const
{
    if (finished_)
    {
        return score_;
    }
    return 0;
}

void Game::game_loop()
{
    if (hal::time::Time::milliseconds() - bullet_limit_timestamp_ >= std::chrono::seconds(10))
    {
        bullet_limit_timestamp_ = hal::time::Time::milliseconds();
        ++max_number_of_monster_bullets_;
    }

    if (monsters_.all_died())
    {
        finished_ = true;
    }

    if (current_number_of_monster_bullets_ < max_number_of_monster_bullets_)
    {
        if (rand() % 1000 < 20)
        {
            int monster_number = rand() % monsters_.size();

            const auto* monster = monsters_.get_monster(monster_number);
            if (monster)
            {
                for (auto& bullet : monster_bullets_)
                {
                    if (!bullet)
                    {
                        bullet.emplace(monster->shot(), fb_.height());
                        ++current_number_of_monster_bullets_;
                        break;
                    }
                }
            }
        }
    }

    if (move_pad_left_)
    {
        player_.move({-1, 0});
    }
    if (move_pad_right_)
    {
        player_.move({1, 0});
    }
    if (bullet_)
    {
        if (bullet_->move({0, -1}))
        {
            bullet_->draw(fb_);
            int killed_monster = monsters_.has_collision(bullet_->position());
            if (killed_monster != -1)
            {
                monsters_.kill(killed_monster);
                if (score_ < 999999)
                {
                    score_ += 10;
                }
                eul::utils::itoa(score_, score_number_);
                score_number_text_.setText(score_number_);
                bullet_.reset();
            }
        }
        else
        {
            bullet_.reset();
        }
    }
    if (hal::time::Time::milliseconds() - bullet_move_timestamp_ > std::chrono::milliseconds(300))
    {
        for (auto& bullet : monster_bullets_)
        {
            if (bullet)
            {
                if (bullet->move({0, 1}))
                {
                    // int killed_player = player_.
                }
                else
                {
                    --current_number_of_monster_bullets_;
                    bullet.reset();
                }
            }
        }
        bullet_move_timestamp_ = hal::time::Time::milliseconds();
    }

    for (auto& bullet : monster_bullets_)
    {
        if (bullet)
        {
            bullet->draw(fb_);
        }
    }

    monsters_.move();
    monsters_.draw();
    score_number_text_.draw(fb_);
    score_text_.draw(fb_);
}

} // namespace space_invaders
