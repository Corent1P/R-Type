set(SRC_SERVER
    ./main.cpp
    ./Error.cpp
    ./server/Server.cpp
    ./clientServer/ClientServer.cpp
    ./command/ACommand.cpp
    ./command/factory/CommandFactory.cpp
    ./command/commands/MoveCommand.cpp
    ./command/commands/ShootCommand.cpp
    ./command/commands/StartCommand.cpp
)

add_executable(r-type_server ${SRC_SERVER})

target_compile_options(r-type_server PRIVATE
    -fPIC
    -Wall
    -Wextra
    # -Werror
    -g
)

target_link_libraries(r-type_server PRIVATE
    ecs
    Boost::boost
    sfml-system
    sfml-window
    sfml-graphics
    protocolHandler
)
