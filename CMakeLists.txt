cmake_minimum_required(VERSION 3.20)

project("Euler-Solver-OpenMP"
    VERSION 1.0
    LANGUAGES CXX
)

find_package(OpenMP REQUIRED)
find_package(Python3 REQUIRED COMPONENTS 
    Interpreter 
    Development
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O3")

file(GLOB TYPES_SOURCE_FILES src/Types/*.cpp)
add_library(TypesLib ${TYPES_SOURCE_FILES})

file(GLOB SOLVER_SOURCE_FILES src/Solver/*.cpp)
add_library(SolverLib ${SOLVER_SOURCE_FILES})

target_include_directories(TypesLib
    PUBLIC
        include/Types
)

target_include_directories(SolverLib 
    PUBLIC 
        include/Solver
)

target_link_libraries(SolverLib
    PUBLIC  
        TypesLib
    PRIVATE 
        OpenMP::OpenMP_CXX
)

if(UNIX)
    target_link_libraries(SolverLib
        PUBLIC
            ncurses
    )
endif()

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        SolverLib
)

enable_testing()

SET(TESTS
    TestVector
    TestMatrix
)

foreach(TEST ${TESTS})
    add_executable(${TEST} 
        tests/${TEST}.cpp
    )

    target_link_libraries(${TEST}
        PRIVATE
            TypesLib
            SolverLib
    )

    add_test(
        NAME ${TEST}
        COMMAND ${TEST}
    )
endforeach()