/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Mode
*/

#pragma once

#include "Client.hpp"

class Mode {
    public:
        Mode() = default;
        ~Mode() = default;
    
        sf::Sprite m_background_mode;
        sf::Texture m_texture_background_mode;
        sf::Sprite m_solo, m_multi;
        sf::Texture m_texture_solo, m_texture_multi;
    protected:
    private:
};
