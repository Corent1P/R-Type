/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system about all components drawing 
*/

#ifndef HANDLEDRAWSYSTEM_HPP_
#define HANDLEDRAWSYSTEM_HPP_
#include "../ISystem.hpp"

#define GET_WINDOW w->getComponent<RType::SFWindowComponent>()->getWindow()

class HandleDrawSystem: public ISystem {
    public:
        HandleDrawSystem();
        ~HandleDrawSystem();
        void effect(std::vector<std::shared_ptr<RType::Entity>> entities);
        void effects(std::vector<std::shared_ptr<RType::Entity>> entities);
        bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity);
    protected:
    private:
        RType::SystemType _type;
        std::vector<std::shared_ptr<RType::Entity>> _entities;
};

#endif /* !HANDLEDRAWSYSTEM_HPP_ */
