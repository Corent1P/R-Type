/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Component related to the entity position
*/

#ifndef POSITIONCOMPONENT_HPP_
#define POSITIONCOMPONENT_HPP_
#include "../IComponent.hpp"

class PositionComponent: public IComponent {
    public:
        PositionComponent(int x, int y);
        ~PositionComponent();
        void setPositions(int x, int y);
        int getPositionX();
        int getPositionY();
        void setType();
        ComponentType getType() const;
    protected:
        ComponentType _type;
    private:
        int _x;
        int _y;
};

#endif /* !POSITIONCOMPONENT_HPP_ */
