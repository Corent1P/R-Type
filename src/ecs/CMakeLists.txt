set(SRC_CLIENT
    ./Coordinator.cpp
    ./Entity.cpp
    ./IComponent.cpp
    ./ISystem.cpp
    ./ASystem.cpp
)

set(SRC_COMPONENTS
    ./Components/PositionComponent.cpp
    ./Components/HealthComponent.cpp
    ./Components/EntityTypeComponent.cpp
)

set(SRC_SYSTEMS
)

add_library(ecs ${SRC_CLIENT} ${SRC_COMPONENTS} ${SRC_SYSTEMS})

target_compile_options(ecs PRIVATE 
    -fPIC
    -Wall
    -Wextra
    -Werror
    -g
)
