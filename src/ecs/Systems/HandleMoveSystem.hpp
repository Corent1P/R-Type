/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system used to handle entity movement
*/

#ifndef HANDLEMOVESYSTEM_HPP_
#define HANDLEMOVESYSTEM_HPP_

#include "../ASystem.hh"

class HandleMoveSystem: public  RType::ASystem {
    public:
        HandleMoveSystem();
        ~HandleMoveSystem();
        void effect(std::shared_ptr<RType::Entity> entity);
        bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity);
        RType::SystemType getType() const;
    protected:
    private:
        RType::SystemType _type;
};

#endif /* !HANDLEMOVESYSTEM_HPP_ */
