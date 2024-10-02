/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system used to handle entity movement
*/

#ifndef HANDLEMOVESYTEM_HPP_
#define HANDLEMOVESYTEM_HPP_
#include "../ASystem.hh"
#include ".././Components/SFWindowComponent.hh"
#include ".././Components/EventComponent.hh"
#include ".././Components/DirectionComponent.hh"
#include ".././Components/EntityTypeComponent.hh"
#include ".././Components/SpriteComponent.hh"
#include ".././Components/DirectionPatternComponent.hh"

#define GET_WINDOW_SET_ISOPEN entity->getComponent<RType::SFWindowComponent>()
#define GET_WINDOW_POLL_EVENT e->getComponent<RType::SFWindowComponent>()->getWindow()
#define EVENT_TYPE e->getComponent<RType::EventComponent>()->getEvent().type

namespace RType {

    class HandleMoveSystem: public  RType::ASystem {
        public:
            HandleMoveSystem(std::function<void(std::shared_ptr<Entity>)> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity);
            ~HandleMoveSystem();
            void effects(std::vector<std::shared_ptr<RType::Entity>> entities);
            bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity);
        protected:
        private:
    };
}
#endif /* !HANDLEMOVESYTEM_HPP_ */
