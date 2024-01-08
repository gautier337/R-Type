/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Options
*/

#pragma once

#ifndef OPTIONS_HPP
    #define OPTIONS_HPP

#include "Client.hpp"

class Options {
    public:
        Options() = default;
        ~Options() = default;

        sf::Sprite m_background_options;
        sf::Texture m_texture_background_options;
        sf::Sprite m_30fps, m_60fps, m_off_sound, m_on_sound;
        sf::Texture m_texture_30fps, m_texture_60fps, m_texture_off_sound, m_texture_on_sound;
    private:
};

#endif //OPTIONS_HPP