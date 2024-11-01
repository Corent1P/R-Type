/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Entity file
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "IComponent.hh"

#define GET_ENTITY_TYPE(x) x->getComponent<RType::EntityTypeComponent>()->getEntityType()

namespace RType {

    class Entity {
        public:
            /**
             * @brief Construct a new entity.
             *
             * @param id the entity id.
             * @param mtx the entity mutex.
             * @param serverId the server id.
             */
            Entity(uint16_t id, std::shared_ptr<std::mutex> mtx, int serverId = -1);
            /**
             * @brief Destroy the entity.
             *
             */
            ~Entity() = default;
            /**
             * @brief Get the entity components.
             *
             * @return const std::unordered_map<std::type_index, std::shared_ptr<RType::IComponent>>&
             */
            const std::unordered_map<std::type_index, std::shared_ptr<RType::IComponent>> &getComponents(void) const;
            /**
             * @brief Get the entity id.
             *
             * @return uint16_t
             */
            uint16_t getId(void) const;
            /**
             * @brief Get the server id.
             *
             * @return int
             */
            int getServerId(void) const;
            /**
             * @brief a method setting the server id.
             *
             * @param serverId the server id.
             */
            void setServerId(int serverId);

            template <typename T>
            /**
             * @brief a method pushing a new component to the entity components.
             *
             * @param component the target component.
             * @return std::shared_ptr<T> 
             */
            std::shared_ptr<T> pushComponent(std::shared_ptr<T> component) {
                std::unique_lock<std::mutex> lock(*_mtx);
                _typedComponents[typeid(T)] = component;
                return component;
            }

            template <typename T>
            /**
             * @brief a method getting a specific component in the entity components.
             *
             * @return std::shared_ptr<T>
             */
            std::shared_ptr<T> getComponent() const {
                std::unique_lock<std::mutex> lock(*_mtx);
                auto it = _typedComponents.find(typeid(T));
                if (it != _typedComponents.end()) {
                    return std::static_pointer_cast<T>(it->second);
                }
                return nullptr;
            }
            /**
             * @brief a method clearing a entity components.
             *
             */
            void clearComponents(void);
            bool operator<(const Entity &other) const;
            bool operator==(const Entity &other) const;
            Entity &operator=(const Entity &other);
            /**
             * @brief a method comparing two entities
             *
             * @param entity1 first entity to compare.
             * @param entity2 second entity to compare.
             * @return true
             * @return false
             */
            static bool compareEntity(const std::shared_ptr<RType::Entity> &entity1, const std::shared_ptr<RType::Entity> &entity2);
        private:
            std::unordered_map<std::type_index, std::shared_ptr<IComponent>> _typedComponents;
            uint16_t _id;
            std::shared_ptr<std::mutex> _mtx;
            int _serverId;

    };
}
std::ostream &operator<<(std::ostream &s, const RType::Entity &entity);

#endif /* !ENTITY_HPP_ */
