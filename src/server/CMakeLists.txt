set(SRC_SERVER
    ./main.cpp
    ./server/Server.cpp
    ./client/Client.cpp
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
    Boost::boost
    sfml-system
    sfml-window
    sfml-graphics
)
