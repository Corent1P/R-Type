set(SRC_CLIENT
    ./Coordinator.cpp
    ./Entity.cpp
    ./ISystem.cpp
    ./ASystem.cpp
    ./Error.cpp
)

set(SRC_COMPONENTS
    ./Components/PositionComponent.cpp
    ./Components/HealthComponent.cpp
    ./Components/EntityTypeComponent.cpp
    ./Components/SFWindowComponent.cpp
    ./Components/EventComponent.cpp
    ./Components/TextureComponent.cpp
)

set(SRC_SYSTEMS
    ./Systems/HandleEventSystem.cpp
)

add_library(ecs ${SRC_CLIENT} ${SRC_COMPONENTS} ${SRC_SYSTEMS})

target_compile_options(ecs PRIVATE 
    -fPIC
    -Wall
    -Wextra
    -Werror
    -g
)

find_package(SFML COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(ecs sfml-system sfml-window sfml-graphics sfml-network sfml-audio)