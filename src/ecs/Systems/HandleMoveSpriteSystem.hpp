/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system used to handle entity sprite movement
*/

#ifndef HANDLEMOVESPRITESYTEM_HPP_
#define HANDLEMOVESPRITESYTEM_HPP_
#include "../ASystem.hh"
#include ".././Components/SFWindowComponent.hh"
#include ".././Components/EventComponent.hh"
#include ".././Components/DirectionComponent.hh"
#include ".././Components/EntityTypeComponent.hh"
#include ".././Components/SpriteComponent.hh"
#include ".././Components/DirectionPatternComponent.hh"
#include "../Components/VelocityComponent.hh"
#include "../../client/Game.hh"

#define GET_WINDOW_SET_ISOPEN entity->getComponent<RType::SFWindowComponent>()
#define GET_WINDOW_POLL_EVENT e->getComponent<RType::SFWindowComponent>()->getWindow()
#define EVENT_TYPE e->getComponent<RType::EventComponent>()->getEvent().type
#define ENTITY_SPRITE entity->getComponent<SpriteComponent>()->getSprite()
namespace RType {

    class HandleMoveSpriteSystem: public  RType::ASystem {
        public:
            HandleMoveSpriteSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity);
            ~HandleMoveSpriteSystem();
            void effects(std::vector<std::shared_ptr<RType::Entity>> entities);
            bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity);
        protected:
        private:

    };
}
#endif /* !HANDLEMOVESPRITESYTEM_HPP_ */
