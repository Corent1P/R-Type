set(SRC_SERVER
    ./main.cpp
)

add_executable(r-type_server ${SRC_SERVER})

target_compile_options(r-type_server PRIVATE 
    -fPIC
    -Wall
    -Wextra
    -Werror
    -g
)