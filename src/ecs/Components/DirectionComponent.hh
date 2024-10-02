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

    class DirectionComponent: public RType::IComponent {
        public:
            DirectionComponent(Direction Direction);
            DirectionComponent();
            ~DirectionComponent();
            void setDirection(Direction entityType);
            Direction getDirection() const;
            void setDirections(Direction direction, bool newBool);
            bool getDirections(Direction direction) const;
            std::string getOutput() const;
        private:
            Direction _direction;
            std::vector<bool> _directions;
    };
}
#endif /* !DIRECTIONCOMPONENT_HPP_ */
