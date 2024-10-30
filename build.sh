#!/bin/bash

if [ $# -eq 1 ] && [ $1 == "clean" ]; then
    rm -rf r-type_client r-type_server unit_tests_* build
    exit 0
fi

cmake --preset=default
cmake --build build -- -j 4
