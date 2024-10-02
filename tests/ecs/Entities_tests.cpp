/*
** EPITECH PROJECT, 2024
** rType
** File description:
** Entities_tests
*/

#include "../Criterion.hh"

#include "../../src/ecs/Components/PositionComponent.hh"
#include "../../src/ecs/Components/HealthComponent.hh"
#include "../../src/ecs/Components/EntityTypeComponent.hh"
#include "../../src/ecs/Coordinator.hh"

Test(main, TestEntities) {
    RType::Coordinator coord;
    std::shared_ptr<RType::Entity> ent = coord.generateNewEntity();
    
    ent->pushComponent(std::make_shared<RType::PositionComponent>(42, 21));
    std::vector<std::shared_ptr<RType::IComponent>> components = ent->getComponents();
    std::string expected = "Position Component (x: 42, y: 21)";
    for (auto component: components) {
        std::string output = component->getOutput();

        cr_assert_eq(output, expected, "Expected: %s, Got: %s", output, expected);
    }

    std::shared_ptr<RType::IComponent> component = ent->getComponent<RType::PositionComponent>();

    std::string output = component->getOutput();

    cr_assert_eq(output, expected, "Expected: %s, Got: %s", output, expected);
    
    std::shared_ptr<RType::IComponent> componentNull = ent->getComponent<RType::HealthComponent>();

    cr_assert_eq(componentNull, nullptr, "Expected: %s, Got: %s", componentNull, nullptr);

    cr_assert_eq(ent->getId(), 0, "Expected: %d, Got: %d", ent->getId(), 0);
}
