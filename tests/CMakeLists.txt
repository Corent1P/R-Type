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

add_executable(unit_tests ${SRC_SERVER_TESTS})

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
