/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system used to handle entity movement
*/

#ifndef HANDLEMOVESYSTEM_HPP_
#define HANDLEMOVESYSTEM_HPP_

#include "ISystem.hh"

class HandleMoveSystem: public ISystem {
    public:
        HandleMoveSystem();
        ~HandleMoveSystem();
        void effect(std::shared_ptr<Entity> entities);
        bool verifyRequiredComponent(Entity entity);
        SystemType getType() const;
    protected:
    private:
};

#endif /* !HANDLEMOVESYSTEM_HPP_ */
