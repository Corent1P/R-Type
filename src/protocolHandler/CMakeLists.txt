set(SRC_ENCODER
    ./Encoder.cpp
    ./Decoder.cpp
)

add_library(protocolHandler ${SRC_ENCODER})

target_compile_options(protocolHandler PRIVATE
    -fPIC
    -Wall
    -Wextra
    -Werror
    -g
)

target_link_libraries(protocolHandler)
