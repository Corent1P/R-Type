/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system used to handle entity shoot
*/

#ifndef HANDLESHOOTSYTEM_HPP_
#define HANDLESHOOTSYTEM_HPP_
#include "../ASystem.hh"
#include ".././Components/SFWindowComponent.hh"
#include ".././Components/EventComponent.hh"
#include ".././Components/DirectionComponent.hh"
#include ".././Components/EntityTypeComponent.hh"
#include ".././Components/SpriteComponent.hh"
#include ".././Components/ActionComponent.hh"
#include ".././Components/PositionComponent.hh"
#include ".././Components/DirectionPatternComponent.hh"
#include ".././Components/TextureComponent.hh"
#include ".././Components/ClockComponent.hh"
#include ".././Components/VelocityComponent.hh"
#include "../../client/Game.hh"

namespace RType {

    class HandleShootSystem: public  RType::ASystem {
        public:
            HandleShootSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity, std::shared_ptr<RType::Client> client);
            ~HandleShootSystem();
            void effects(std::vector<std::shared_ptr<RType::Entity>> entities);
            void effect(std::shared_ptr<RType::Entity> entity);
            bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity);
        protected:
        private:
            std::shared_ptr<RType::Client> _client;
    };
}
#endif /* !HANDLESHOOTSYTEM_HPP_ */
