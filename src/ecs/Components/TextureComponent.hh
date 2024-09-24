/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Texture component 
*/

#ifndef TEXTURECOMPONENT_HPP_
#define TEXTURECOMPONENT_HPP_

#include <SFML/Graphics.hpp>
#include "../IComponent.hh"

namespace RType {

    class TextureComponent: public RType::IComponent {
        public:
            TextureComponent(std::string path);
            ~TextureComponent();

            void setTexture(std::string path);
            sf::Texture getTexture() const;
            std::string getPath() const;
            std::string getOutput() const;
        private:
            std::string _path;
            sf::Texture _texture;

    };
}

#endif /* !TEXTURECOMPONENT_HPP_ */
