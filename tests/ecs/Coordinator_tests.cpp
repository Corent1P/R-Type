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

Test(main, TestCoordinatorOutput) {
    
    RType::Coordinator coord;
    std::shared_ptr<RType::Entity> ent = coord.generateNewEntity();
    
    ent->pushComponent(std::make_shared<RType::PositionComponent>(10, 10));

    std::ostringstream output_stream;

    std::streambuf *old_out = std::cout.rdbuf(output_stream.rdbuf());

    std::cout << coord << std::endl;

    std::cout.rdbuf(old_out);

    std::string expected_output = "Coordinator:\n\tEntity[0]:\n\t\tPosition Component (x: 10, y: 10)\n\n";

    std::string actual_output = output_stream.str();

    cr_assert_eq(actual_output, expected_output, "Expected: %s, Got: %s", expected_output.c_str(), actual_output.c_str());
}
