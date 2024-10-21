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
            Entity(uint16_t id, std::shared_ptr<std::mutex> mtx, int serverId = -1);
            ~Entity() = default;

            std::vector<std::shared_ptr<IComponent>> getComponents(void) const;
            uint16_t getId(void) const;
            int getServerId(void) const;
            void setServerId(int serverId);

            template <typename T>
            std::shared_ptr<T> pushComponent(std::shared_ptr<T> component) {
                std::unique_lock<std::mutex> lock(*_mtx);
                this->_components.push_back(component);
                return component;
            }

            template <typename T>
            std::shared_ptr<T> getComponent() const {
                std::unique_lock<std::mutex> lock(*_mtx);
                for (const auto& component : _components) {
                    std::shared_ptr<T> castedComponent = std::dynamic_pointer_cast<T>(component);
                    if (castedComponent) {
                        return castedComponent;
                    }
                }
                return nullptr;
            }

            void clearComponents(void);
            bool operator<(const Entity &other) const;
            bool operator==(const Entity &other) const;
            Entity &operator=(const Entity &other);
            static bool compareEntity(const std::shared_ptr<RType::Entity> &entity1, const std::shared_ptr<RType::Entity> &entity2);
        private:
            std::vector<std::shared_ptr<IComponent>> _components;
            uint16_t _id;
            std::shared_ptr<std::mutex> _mtx;
            int _serverId;

    };
}
std::ostream &operator<<(std::ostream &s, const RType::Entity &entity);

#endif /* !ENTITY_HPP_ */
