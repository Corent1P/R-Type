/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Sprite component 
*/

#ifndef SPRITECOMPONENT_HPP_
#define SPRITECOMPONENT_HPP_

#include <SFML/Graphics.hpp>
#include "../IComponent.hh"

namespace RType {

    class SpriteComponent: public RType::IComponent, public sf::Drawable {
        public:
            SpriteComponent(sf::Texture texture, sf::Vector2f pos);
            SpriteComponent(sf::Texture texture, sf::Vector2f pos, sf::Vector2f scale);
            ~SpriteComponent() = default;

            void setSprite(sf::Texture texture, sf::Vector2f pos);
            void setSprite(sf::Texture texture, sf::Vector2f pos, sf::Vector2f scale);
            sf::Sprite getSprite() const;
            void draw(sf::RenderTarget& target, sf::RenderStates states) const;
            std::string getOutput() const;
        private:
            sf::Sprite _sprite;

    };
}

#endif /* !SPRITECOMPONENT_HPP_ */
