/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system used to handle entity movement
*/

#ifndef HANDLEMOVESYSTEM_HPP_
#define HANDLEMOVESYSTEM_HPP_

#include "../ISystem.hh"

class HandleMoveSystem: public  RType::ISystem {
    public:
        HandleMoveSystem();
        ~HandleMoveSystem();
        void effect(std::vector<std::shared_ptr<RType::Entity>> entities);
        bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity);
        RType::SystemType getType() const;
    protected:
    private:
        RType::SystemType _type;
};

#endif /* !HANDLEMOVESYSTEM_HPP_ */
