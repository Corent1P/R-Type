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

    /**
     * @brief Text component class
     */
    class TextComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new TextComponent object
             *
             * @param text Initial text
             * @param fontSize Font size
             * @param font Shared pointer to the font
             */
            TextComponent(std::string text, std::size_t fontSize, std::shared_ptr<sf::Font> font);

            /**
             * @brief Destroy the TextComponent object
             */
            ~TextComponent();

            /**
             * @brief Set the text
             *
             * @param text New text
             * @param fontSize Font size (default is 60)
             */
            void setText(std::string text, std::size_t fontSize = 60);

            /**
             * @brief Get the text
             *
             * @return std::shared_ptr<sf::Text> Shared pointer to the text
             */
            std::shared_ptr<sf::Text> getText() const;

            /**
             * @brief Get the text without variable
             *
             * @return const std::string& Text without variable
             */
            const std::string& getTextWithoutVariable() const;

            /**
             * @brief Set the text without variable
             *
             * @param text New text without variable
             */
            void setTextWithoutVariable(std::string text);

            /**
             * @brief Get the font size
             *
             * @return std::size_t Font size
             */
            std::size_t getFontSize() const;

            /**
             * @brief Set the font size
             *
             * @param fontSize New font size
             */
            void setFontSize(std::size_t fontSize);

            /**
             * @brief Get the output as a string
             *
             * @return std::string Output string
             */
            std::string getOutput() const;
        private:
            /**
             * @brief Shared pointer to the text
             */
            std::shared_ptr<sf::Text> _text;

            /**
             * @brief Text without variable
             */
            std::string _textWithoutVariable;

            /**
             * @brief Font size
             */
            std::size_t _fontSize;
    };
}
