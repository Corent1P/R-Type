set(SRC_ENCODER
    ./Encoder.cpp
    ./Decoder.cpp
)

add_library(protocolHandler ${SRC_ENCODER})

if (NOT WIN32)
    target_compile_options(protocolHandler PRIVATE
        -fPIC
        -g
    )
endif()

target_link_libraries(protocolHandler)
