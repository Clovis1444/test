#!/bin/bash
# This script builds project

# Args:
# --release - release build(program will be build in debug mode without this argument)
# --run - run program after build

SCRIPT_DIR="$(dirname "$(realpath "$0")")"
cd "$SCRIPT_DIR" || exit 1

BUILD_TYPE=Debug
RUN=false
# CXX_COMP="x86_64-w64-mingw32-g++"
# C_COMP="x86_64-w64-mingw32-gcc"
CXX_COMP="clang++"
C_COMP="clang"

for arg in "$@"; do
    if [ "$arg" = "--release" ]; then
        BUILD_TYPE=Release
    fi
    if [ "$arg" = "--run" ]; then
        RUN=true
    fi
done

# Configure
cmake --no-warn-unused-cli -DCMAKE_BUILD_TYPE:STRING=${BUILD_TYPE} -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=${C_COMP} -DCMAKE_CXX_COMPILER:FILEPATH=${CXX_COMP} -S${SCRIPT_DIR} -B${SCRIPT_DIR}\\build -G Ninja || exit 1
# Build
cmake --build ${SCRIPT_DIR}/build --config ${BUILD_TYPE} --target Program || exit 1

# Run
if [ $RUN = true ]; then
    ./build/Program || exit 1
fi
