/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** ECS Components & systems Coordinator
*/

#ifndef COORDINATOR_HPP_
#define COORDINATOR_HPP_

#include "ASystem.hh"
#include "Entity.hpp"
namespace RType {

    class Coordinator {
        public:
            /**
             * @brief Construct a new Coordinator object
             *
             */
            Coordinator();
            /**
             * @brief Destroy the Coordinator object
             *
             */
            ~Coordinator() = default;
            /**
             * @brief a method generating a new entity.
             *
             * @param serverId id of the server.
             * @return std::shared_ptr<Entity>
             */
            std::shared_ptr<Entity> generateNewEntity(uint16_t serverId = -1);
            /**
             * @brief a method generating a new system.
             *
             * @param sys
             */
            void generateNewSystem(std::shared_ptr<ISystem> sys);
            /**
             * @brief get all entities contained in the coordinator.
             *
             * @return const std::vector<std::shared_ptr<Entity>>&
             */
            const std::vector<std::shared_ptr<Entity>> &getEntities() const;
            const std::vector<std::shared_ptr<ISystem>> &getSystems() const;
            /**
             * @brief a method adding a new entity to the coordinator entity vector.
             *
             * @return std::shared_ptr<Entity>
             */
            std::shared_ptr<Entity> addEntity(void);
            /**
             * @brief a method destroying a specific entity from the coordinator entity vector.
             *
             * @param entityToDestroy the target entity.
             * @param lock
             */
            void deleteEntity(std::shared_ptr<Entity> entityToDestroy, bool lock = true);

        private:
            /**
             * @brief Get the Next Entity Id
             *
             * @return std::size_t
             */
            std::size_t getNextEntityId(void);
            /**
             * @brief a vector of std::mutex
             *
             */
            std::shared_ptr<std::mutex> _mtx;
            /**
             * @brief a vector that contains each entity stored in the coordinator.
             *
             */
            std::vector<std::shared_ptr<Entity>> _entities;
            /**
             * @brief a vector that contains each system stored in the coordinator.
             *
             */
            std::vector<std::shared_ptr<ISystem>> _systems;
    };
}
std::ostream &operator<<(std::ostream &s, const RType::Coordinator &coordinator);
#endif /* !COORDINATOR_HPP_ */
