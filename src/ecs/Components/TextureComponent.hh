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

    /**
     * @brief Texture component class
     */
    class TextureComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new TextureComponent object
             *
             * @param path Path to the texture file
             */
            TextureComponent(std::string path);

            /**
             * @brief Default destructor
             */
            ~TextureComponent() = default;

            /**
             * @brief Set the texture
             *
             * @param path Path to the texture file
             */
            void setTexture(std::string path);

            /**
             * @brief Get the texture
             *
             * @return std::shared_ptr<sf::Texture> Shared pointer to the texture
             */
            std::shared_ptr<sf::Texture> getTexture() const;

            /**
             * @brief Get the path to the texture file
             *
             * @return std::string Path to the texture file
             */
            std::string getPath() const;

            /**
             * @brief Get the output as a string
             *
             * @return std::string Output string
             */
            std::string getOutput() const;
        private:
            /**
             * @brief Shared pointer to the texture
             */
            std::shared_ptr<sf::Texture> _texture;

            /**
             * @brief Path to the texture file
             */
            std::string _path;
    };
}

#endif /* !TEXTURECOMPONENT_HPP_ */
