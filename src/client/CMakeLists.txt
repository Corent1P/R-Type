set(SRC_CLIENT
    ./main.cpp
)

add_executable(r-type_client ${SRC_CLIENT})

target_compile_options(r-type_client PRIVATE 
    -fPIC
    -Wall
    -Wextra
    -Werror
    -g
)