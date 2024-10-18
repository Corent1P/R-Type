set(SRC_SERVER
    ./main.cpp
    ./Error.cpp
    ./server/Server.cpp
    ./clientServer/ClientServer.cpp
    ./command/ACommand.cpp
    ./command/factory/CommandFactory.cpp
    ./command/commands/ConnexionCommand.cpp
    ./command/commands/DisconnexionCommand.cpp
    ./command/commands/NewEntityCommand.cpp
    ./command/commands/DeleteEntityCommand.cpp
    ./command/commands/MoveEntityCommand.cpp
    ./command/commands/InfoLevelCommand.cpp
    ./command/commands/InfoEntityCommand.cpp
    ./command/commands/MovePlayerCommand.cpp
    ./command/commands/ActionPlayerCommand.cpp
    ./command/commands/GameStartCommand.cpp
    ./command/commands/GameEndCommand.cpp
)

add_executable(r-type_server ${SRC_SERVER})

if (NOT WIN32)
    target_compile_options(r-type_server PRIVATE
        -fPIC
        -g
    )
endif()

target_link_libraries(r-type_server PRIVATE
    ecs
    Boost::boost
    protocolHandler
)
