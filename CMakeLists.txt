cmake_minimum_required(VERSION 3.20)

project(Euler-Solver-OpenMP
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

add_library(TypesLib
    src/Types/Vector.cpp
    src/Types/Matrix.cpp
    src/Types/VectorOfMatrix.cpp
    src/Types/MatrixOfMatrix.cpp
    src/Types/Function.cpp
    src/Types/VectorOfFunction.cpp
    src/Types/MatrixOfFunction.cpp
    src/Types/Conversion.cpp
    src/Types/Time.cpp
)

add_library(SolverLib
    src/Solver/Properties.cpp
    src/Solver/Equation.cpp
    src/Solver/Solver.cpp
    src/Solver/FileReader.cpp
    src/Solver/FileWriter.cpp
    src/Solver/Experiments.cpp
    src/Solver/IOHandler.cpp
    src/Solver/UI.cpp
)

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

add_executable(Main
    src/main.cpp
)

target_link_libraries(Main
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