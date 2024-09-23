/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Component related to the entity position
*/

#ifndef POSITIONCOMPONENT_HPP_
#define POSITIONCOMPONENT_HPP_
#include "../IComponent.hpp"
namespace RType {

    class PositionComponent: public RType::IComponent {
        public:
            PositionComponent(int x, int y);
            ~PositionComponent();
            void setPositions(int x, int y);
            void setX(int x);
            void setY(int y);
            int getPositionX() const;
            int getPositionY() const;
            ComponentType getType() const;
            std::string getOutput() const;
        protected:
            ComponentType _type;
        private:
            int _x;
            int _y;
    };
}
#endif /* !POSITIONCOMPONENT_HPP_ */
