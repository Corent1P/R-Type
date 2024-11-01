/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** IntRect component
*/

#ifndef INTRECTCOMPONENT_HPP_
#define INTRECTCOMPONENT_HPP_

#include <SFML/Graphics.hpp>
#include "../IComponent.hh"

namespace RType {

    /**
     * @brief IntRect component class
     */
    class IntRectComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new IntRect Component object
             *
             * @param left Initial left position
             * @param top Initial top position
             * @param width Initial width
             * @param height Initial height
             */
            IntRectComponent(int left, int top, int width, int height);

            /**
             * @brief Set the IntRect
             *
             * @param left New left position
             * @param top New top position
             * @param width New width
             * @param height New height
             */
            void setIntRect(int left, int top, int width, int height);

            /**
             * @brief Get the IntRect Left position
             *
             * @return int Current left position
             */
            int getIntRectLeft() const;

            /**
             * @brief Get the IntRect Top position
             *
             * @return int Current top position
             */
            int getIntRectTop() const;

            /**
             * @brief Get the IntRect Width
             *
             * @return int Current width
             */
            int getIntRectWidth() const;

            /**
             * @brief Get the IntRect Height
             *
             * @return int Current height
             */
            int getIntRectHeight() const;

            /**
             * @brief Get the Output as a string
             *
             * @return std::string Output string
             */
            std::string getOutput() const;

        private:
            /**
             * @brief Left position
             */
            int _left;

            /**
             * @brief Top position
             */
            int _top;

            /**
             * @brief Width
             */
            int _width;

            /**
             * @brief Height
             */
            int _height;
    };
}

#endif /* !INTRECTCOMPONENT_HPP_ */
