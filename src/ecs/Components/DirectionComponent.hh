/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** direction component asign to a entity movement 
*/

#ifndef DIRECTIONCOMPONENT_HPP_
#define DIRECTIONCOMPONENT_HPP_
#include "../IComponent.hh"

namespace RType {
    enum Direction {
        NOMOVE,
        UP,
        DOWN,
        LEFT,
        RIGHT,
    };
    /**
     * @brief DirectionComponent class for handling the direction of an entity
     *
     */
    class DirectionComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new Direction Component object
             *
             * @param entityType The direction to set
             */
            DirectionComponent(Direction Direction);

            /**
             * @brief Construct a new Direction Component object
             *
             */
            DirectionComponent();

            /**
             * @brief Destroy the Direction Component object
             *
             */
            ~DirectionComponent();

            /**
             * @brief Set the direction of the entity
             *
             * @param entityType The direction to set
             */
            void setDirection(Direction entityType);

            /**
             * @brief Get the direction of the entity
             *
             * @return Direction The direction
             */
            Direction getDirection() const;

            /**
             * @brief Set the directions of the entity
             *
             * @param direction The direction to set
             * @param newValue The new value of the direction
             */
            void setDirections(Direction direction, int newValue);

            /**
             * @brief Get the directions of the entity
             *
             * @param direction The direction to get
             *
             * @return int The value of the direction
             */
            int getDirections(Direction direction) const;

            /**
             * @brief Get the output of the component
             *
             * @return std::string The output of the component
             */
            std::string getOutput() const;

        private:
            /**
             * @brief The direction of the entity
             *
             */
            Direction _direction;

            /**
             * @brief The vector of directions of the entity
             *
             */
            std::vector<int> _directions;
    };
}
#endif /* !DIRECTIONCOMPONENT_HPP_ */
