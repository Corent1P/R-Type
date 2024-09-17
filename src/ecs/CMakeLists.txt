set(SRC_CLIENT
    ./Print.cpp
)

add_library(ecs ${SRC_CLIENT})

target_compile_options(ecs PRIVATE 
    -fPIC
    -Wall
    -Wextra
    -Werror
    -g
)
