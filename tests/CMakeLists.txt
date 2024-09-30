set(SRC_CLIENTS_TESTS
    ./client/Client_tests.cpp
)

set(SRC_ECS_TESTS
    ./ecs/Components_tests.cpp

    ../../src/ecs/Components/PositionComponent.cpp
    ../../src/ecs/Components/HealthComponent.cpp
    ../../src/ecs/Components/EntityTypeComponent.cpp
)

set(SRC_SERVER_TESTS
    ./server/Server_tests.cpp
    ./server/Command_tests.cpp

    ../../src/server/Error.cpp
    ../../src/server/server/Server.cpp
    ../../src/server/client/Client.cpp
    ../../src/server/command/ACommand.cpp
    ../../src/server/command/commands/MoveCommand.cpp
    ../../src/server/command/commands/ShootCommand.cpp
    ../../src/server/command/commands/StartCommand.cpp
    ../../src/server/command/factory/CommandFactory.cpp
)

target_link_libraries(unit_tests PRIVATE
    criterion
    gcov
    Boost::boost
    sfml-system
    sfml-window
    sfml-graphics
)

target_compile_options(unit_tests PRIVATE
    -std=c++20
    --coverage
)

target_link_options(unit_tests PRIVATE --coverage)
