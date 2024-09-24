/*
** EPITECH PROJECT, 2024
** rType
** File description:
** components_tests
*/

#include "../Criterion.hh"

#include "../../src/ecs/Components/PositionComponent.hh"
#include "../../src/ecs/Components/HealthComponent.hh"
#include "../../src/ecs/Components/EntityTypeComponent.hh"

Test(main, TestPositionComponent) {
    RType::PositionComponent position(1, 2);
    cr_assert_eq(position.getPositionX(), 1, "Expected: %d, Got: %d", position.getPositionX(), 1);
    cr_assert_eq(position.getPositionY(), 2, "Expected: %d, Got: %d", position.getPositionY(), 1);

    position.setX(12);
    position.setY(25);
    cr_assert_eq(position.getPositionX(), 12, "Expected: %d, Got: %d", position.getPositionX(), 12);
    cr_assert_eq(position.getPositionY(), 25, "Expected: %d, Got: %d", position.getPositionY(), 25);

    position.setPositions(42, 21);
    cr_assert_eq(position.getPositionX(), 42, "Expected: %d, Got: %d", position.getPositionX(), 42);
    cr_assert_eq(position.getPositionY(), 21, "Expected: %d, Got: %d", position.getPositionY(), 21);

    std::string output = position.getOutput();
    std::string expected = "Position Component (x: 42, y: 21)";

    cr_assert_eq(output, expected, "Expected: %s, Got: %s", output, expected);
}

Test(main, TestHealthComponent) {
    RType::HealthComponent health(25);
    cr_assert_eq(health.getHealth(), 25, "Expected: %d, Got: %d", health.getHealth(), 25);
    health.setHealth(12);
    cr_assert_eq(health.getHealth(), 12, "Expected: %d, Got: %d", health.getHealth(), 12);

    std::string output = health.getOutput();
    std::string expected = "Health Component (health: 12)";

    cr_assert_eq(output, expected, "Expected: %s, Got: %s", output, expected);
}

Test(main, TestEntityTypeComponent) {
    RType::EntityTypeComponent entityType(RType::PLAYER);
    cr_assert_eq(entityType.getEntityType(), RType::PLAYER, "Expected: %d, Got: %d", entityType.getEntityType(), RType::PLAYER);

    std::string output = entityType.getOutput();
    std::string expected = "Entity Type Component (entity type: player)";
    cr_assert_eq(output, expected, "Expected: %s, Got: %s", output, expected);
    
    entityType.setEntityType(RType::BOSS);
    cr_assert_eq(entityType.getEntityType(), RType::BOSS, "Expected: %d, Got: %d", entityType.getEntityType(), RType::BOSS);

    output = entityType.getOutput();
    expected = "Entity Type Component (entity type: boss)";
    cr_assert_eq(output, expected, "Expected: %s, Got: %s", output, expected);

    entityType.setEntityType(RType::MOB);
    output = entityType.getOutput();
    expected = "Entity Type Component (entity type: mob)";
    cr_assert_eq(output, expected, "Expected: %s, Got: %s", output, expected);

    entityType.setEntityType(RType::BUTTON);
    output = entityType.getOutput();
    expected = "Entity Type Component (entity type: button)";
    cr_assert_eq(output, expected, "Expected: %s, Got: %s", output, expected);
    
    entityType.setEntityType(RType::OTHER);
    output = entityType.getOutput();
    expected = "Entity Type Component (entity type: unknown)";
    cr_assert_eq(output, expected, "Expected: %s, Got: %s", output, expected);
}
