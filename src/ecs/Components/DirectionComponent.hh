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
     * @brief 
     * 
     */
    class DirectionComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new Direction Component object
             *
             * @param Direction 
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
             * @brief Set the Direction object
             * 
             * @param entityType 
             */
            void setDirection(Direction entityType);
            /**
             * @brief Get the Direction object
             * 
             * @return Direction 
             */
            Direction getDirection() const;
            /**
             * @brief Set the Directions object
             * 
             * @param direction 
             * @param newBool 
             */
            void setDirections(Direction direction, bool newBool);
            /**
             * @brief Get the Directions object
             * 
             * @param direction 
             * @return true 
             * @return false 
             */
            bool getDirections(Direction direction) const;
            /**
             * @brief Get the Output object
             * 
             * @return std::string 
             */
            std::string getOutput() const;
        private:
            Direction _direction;
            std::vector<bool> _directions;
    };
}
#endif /* !DIRECTIONCOMPONENT_HPP_ */
