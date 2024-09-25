/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system about all components drawing 
*/

#ifndef HANDLEDRAWSYSTEM_HPP_
#define HANDLEDRAWSYSTEM_HPP_
#include "../ASystem.hh"

#define GET_WINDOW_FOR_DRAW w->getComponent<RType::SFWindowComponent>()
namespace RType {
    class HandleDrawSystem: public ASystem {
        public:
            HandleDrawSystem();
            ~HandleDrawSystem();
            void effect(std::shared_ptr<RType::Entity> entity);
            void effects(std::vector<std::shared_ptr<RType::Entity>> entities);
            bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity);
        protected:
        private:
            RType::SystemType _type;
            std::vector<std::shared_ptr<RType::Entity>> _entities;
    };
}

#endif /* !HANDLEDRAWSYSTEM_HPP_ */
