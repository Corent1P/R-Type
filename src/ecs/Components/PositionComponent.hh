/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Component related to the entity position
*/

#ifndef POSITIONCOMPONENT_HPP_
#define POSITIONCOMPONENT_HPP_
#include "../IComponent.hh"
#include <SFML/Graphics.hpp>

namespace RType {

    /**
     * @brief Component related to the entity position
     */
    class PositionComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new Position Component object
             *
             * @param x Initial x position
             * @param y Initial y position
             */
            PositionComponent(int x, int y);

            /**
             * @brief Destroy the Position Component object
             */
            ~PositionComponent();

            /**
             * @brief Set the Positions
             *
             * @param x New x position
             * @param y New y position
             */
            void setPositions(int x, int y);

            /**
             * @brief Set the X position
             *
             * @param x New x position
             */
            void setX(int x);

            /**
             * @brief Set the Y position
             *
             * @param y New y position
             */
            void setY(int y);

            /**
             * @brief Get the X position
             *
             * @return int Current x position
             */
            int getPositionX() const;

            /**
             * @brief Get the Y position
             *
             * @return int Current y position
             */
            int getPositionY() const;

            /**
             * @brief Get the Positions
             *
             * @return sf::Vector2f Current positions
             */
            sf::Vector2f getPositions() const;

            /**
             * @brief Get the Output as a string
             *
             * @return std::string Output string
             */
            std::string getOutput() const;

        private:
            /**
             * @brief X position
             */
            int _x;

            /**
             * @brief Y position
             */
            int _y;
    };
}
#endif /* !POSITIONCOMPONENT_HPP_ */
