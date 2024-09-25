set(SRC_CLIENT
    ./main.cpp
    ./Game.cpp
    ./Error.cpp
)

add_executable(r-type_client ${SRC_CLIENT})

target_compile_options(r-type_client PRIVATE 
    -fPIC
    -Wall
    -Wextra
    -Werror
    -g
)
target_link_libraries(r-type_client PRIVATE
    ecs
    Boost::boost
    sfml-system
    sfml-window
    sfml-graphics
)
