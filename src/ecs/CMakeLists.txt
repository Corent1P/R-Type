set(SRC_CLIENT
    ./Coordinator.cpp
    ./Entity.cpp
    ./IComponent.cpp
    ./ISystem.cpp
    ./ASystem.cpp
    ./Components/PositionComponent.cpp
    ./Components/HealthComponent.cpp
)

add_library(ecs ${SRC_CLIENT})

target_compile_options(ecs PRIVATE 
    -fPIC
    -Wall
    -Wextra
    -Werror
    -g
)
