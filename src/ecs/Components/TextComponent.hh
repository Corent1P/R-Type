/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Text component
*/

#pragma once

#include "../IComponent.hh"
#include <SFML/Graphics.hpp>

namespace RType {

    class TextComponent: public RType::IComponent {
        public:
            TextComponent(std::string text, std::size_t fontSize, std::shared_ptr<sf::Font> font);
            ~TextComponent();
            void setText(std::string text, std::size_t fontSize);
            std::shared_ptr<sf::Text> getText() const;
            std::string getOutput() const;
        private:
            std::shared_ptr<sf::Text> _text;
;
    };
}
