cmake_minimum_required(VERSION 3.20)
project(6502-emu LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(6502-emu
    main.cpp
    vm/Opcodes.cpp
    instructions/Arithmetic.cpp
    instructions/Branches.cpp
    instructions/IncrementsDecrements.cpp
    instructions/JumpsCalls.cpp
    instructions/LoadStore.cpp
    instructions/Logical.cpp
    instructions/Shifts.cpp
    instructions/StackOperations.cpp
    instructions/StatusFlagChanges.cpp
    instructions/SystemFunctions.cpp
    instructions/Transfers.cpp
)
