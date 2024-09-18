set(SRC_CLIENT
    ./Coordinator.cpp
    ./Entity.cpp
    ./IComponent.cpp
    ./AComponent.cpp
    ./ISystem.cpp
    ./ASystem.cpp
)

add_library(ecs ${SRC_CLIENT})

target_compile_options(ecs PRIVATE 
    -fPIC
    -Wall
    -Wextra
    -Werror
    -g
)
