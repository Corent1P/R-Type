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

    /**
     * @brief Sprite component class
     */
    class SpriteComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new SpriteComponent object
             *
             * @param texture Shared pointer to the texture
             * @param pos Position of the sprite
             */
            SpriteComponent(std::shared_ptr<sf::Texture> texture, sf::Vector2f pos);

            /**
             * @brief Construct a new SpriteComponent object
             *
             * @param texture Shared pointer to the texture
             * @param pos Position of the sprite
             * @param scale Scale of the sprite
             */
            SpriteComponent(std::shared_ptr<sf::Texture> texture, sf::Vector2f pos, sf::Vector2f scale);

            /**
             * @brief Construct a new SpriteComponent object
             *
             * @param texture Shared pointer to the texture
             * @param pos Position of the sprite
             * @param scale Scale of the sprite
             * @param rect Texture rectangle
             */
            SpriteComponent(std::shared_ptr<sf::Texture> texture, sf::Vector2f pos, sf::Vector2f scale, sf::IntRect rect);

            /**
             * @brief Destroy the SpriteComponent object
             */
            ~SpriteComponent() = default;

            /**
             * @brief Set the sprite
             *
             * @param texture Shared pointer to the texture
             * @param pos Position of the sprite
             */
            void setSprite(std::shared_ptr<sf::Texture> texture, sf::Vector2f pos);

            /**
             * @brief Set the sprite
             *
             * @param texture Shared pointer to the texture
             * @param pos Position of the sprite
             * @param scale Scale of the sprite
             */
            void setSprite(std::shared_ptr<sf::Texture> texture, sf::Vector2f pos, sf::Vector2f scale);

            /**
             * @brief Set the sprite
             *
             * @param texture Shared pointer to the texture
             * @param pos Position of the sprite
             * @param scale Scale of the sprite
             * @param rect Texture rectangle
             */
            void setSprite(std::shared_ptr<sf::Texture> texture, sf::Vector2f pos, sf::Vector2f scale, sf::IntRect rect);

            /**
             * @brief Get the sprite
             *
             * @return std::shared_ptr<sf::Sprite> Shared pointer to the sprite
             */
            std::shared_ptr<sf::Sprite> getSprite() const;

            /**
             * @brief Get the output as a string
             *
             * @return std::string Output string
             */
            std::string getOutput() const;

        private:
            /**
             * @brief Shared pointer to the sprite
             */
            std::shared_ptr<sf::Sprite> _sprite;
    };
}

#endif /* !SPRITECOMPONENT_HPP_ */
