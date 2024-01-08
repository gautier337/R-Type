/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Texture
*/

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class TextureManager {
    public:
        void loadTexture(const std::string& name, const std::string& filename) {
            sf::Texture tex;
            if (tex.loadFromFile(filename)) {
                this->textures[name] = tex;
            }
        }

        const sf::Texture& getTexture(const std::string& name) const {
            return this->textures.at(name);
        }

        void setTextureRepeated(const std::string& name, bool repeated) {
            auto it = textures.find(name);
            if (it != textures.end()) {
                it->second.setRepeated(repeated);
            }
        }

    private:
        std::map<std::string, sf::Texture> textures;
        sf::Texture textureBackground, textureStartGame, textureExit, textureOptions;
};

#endif /* !TEXTURE_HPP_ */
