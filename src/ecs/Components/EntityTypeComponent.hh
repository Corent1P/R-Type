/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Component related to the entity position
*/

#ifndef TYPECOMPONENT_HPP_
#define TYPECOMPONENT_HPP_
#include "../IComponent.hh"
namespace RType {
    enum EntityType {
        E_OTHER,
        E_WINDOW,
        E_PLAYER,
        E_ALLIES,
        E_MOB,
        E_BOSS,
        E_BUTTON
    };

    class EntityTypeComponent: public RType::IComponent {
        public:
            EntityTypeComponent(EntityType entityType);
            ~EntityTypeComponent();
            void setEntityType(EntityType entityType);
            EntityType getEntityType() const;
            std::string getOutput() const;
        private:
            EntityType _entityType;
    };
}
#endif /* !TYPECOMPONENT_HPP_ */
