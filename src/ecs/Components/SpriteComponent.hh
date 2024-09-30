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

    class SpriteComponent: public RType::IComponent {
        public:
            SpriteComponent(std::shared_ptr<sf::Texture> texture, sf::Vector2f pos);
            SpriteComponent(std::shared_ptr<sf::Texture> texture, sf::Vector2f pos, sf::Vector2f scale);
            SpriteComponent(std::shared_ptr<sf::Texture> texture, sf::Vector2f pos, sf::Vector2f scale, sf::IntRect rect);
            ~SpriteComponent() = default;

            void setSprite(std::shared_ptr<sf::Texture> texture, sf::Vector2f pos);
            void setSprite(std::shared_ptr<sf::Texture> texture, sf::Vector2f pos, sf::Vector2f scale);
            void setSprite(std::shared_ptr<sf::Texture> texture, sf::Vector2f pos, sf::Vector2f scale, sf::IntRect rect);
            std::shared_ptr<sf::Sprite> getSprite() const;
            std::string getOutput() const;
        private:
            std::shared_ptr<sf::Sprite> _sprite;

    };
}

#endif /* !SPRITECOMPONENT_HPP_ */
