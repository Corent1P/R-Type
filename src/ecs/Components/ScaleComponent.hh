/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Scale component
*/

#ifndef SCALECOMPONENT_HPP_
#define SCALECOMPONENT_HPP_

#include <SFML/Graphics.hpp>
#include "../IComponent.hh"

namespace RType {

    /**
     * @brief Scale component class
     */
    class ScaleComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new ScaleComponent object
             *
             * @param x Scale factor in the x direction
             * @param y Scale factor in the y direction
             */
            ScaleComponent(float x, float y);

            /**
             * @brief Default destructor
             */
            ~ScaleComponent() = default;

            /**
             * @brief Set the scale factors
             *
             * @param x Scale factor in the x direction
             * @param y Scale factor in the y direction
             */
            void setScale(float x, float y);

            /**
             * @brief Get the scale factor in the x direction
             *
             * @return float Scale factor in the x direction
             */
            float getScaleX() const;

            /**
             * @brief Get the scale factor in the y direction
             *
             * @return float Scale factor in the y direction
             */
            float getScaleY() const;

            /**
             * @brief Get the scale factors as a vector
             *
             * @return sf::Vector2f Vector containing the scale factors
             */
            sf::Vector2f getScales() const;

            /**
             * @brief Get the output as a string
             *
             * @return std::string Output string
             */
            std::string getOutput() const;
        private:
            /**
             * @brief Scale factor in the x direction
             */
            float _scaleX;

            /**
             * @brief Scale factor in the y direction
             */
            float _scaleY;
    };
}

#endif /* !SCALECOMPONENT_HPP_ */
