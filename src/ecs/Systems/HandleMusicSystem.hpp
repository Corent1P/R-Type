/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** System handling direction sound for any entity
*/

#ifndef HANDLEMUSICSYSTEM_HPP_
#define HANDLEMUSICSYSTEM_HPP_

#include "../ASystem.hh"
#include ".././Components/MusicComponent.hh"

namespace RType {
    /**
     * @brief a system that play sound.
     *
     */
    class HandleMusicSystem: public ASystem {
        public:
            /**
             * @brief Construct a new Handle Music System object
             *
             * @param addEntity method used to add a new Entity to the coordinator.
             * @param deleteEntity method used to delete a Entity from the coordinator.
             */
            HandleMusicSystem(std::function<std::shared_ptr<Entity>(void)> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity);
            /**
             * @brief Destroy the Handle Music System object
             *
             */
            ~HandleMusicSystem();
            /**
             * @brief a method to handle the System action on the right entity.
             *
             * @param entity entity required in order to process a action.
             */
            void effect(std::shared_ptr<RType::Entity> entity);
            /**
             * @brief a method to verify if a entity has the right components to process the system effect.
             *
             * @param entity
             * @return true
             * @return false
             */
            bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity);
    };
}

#endif /* !HANDLEMUSICSYSTEM_HPP_ */
