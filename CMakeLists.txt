cmake_minimum_required(VERSION 3.6)
project(MatrixMultiplication)
find_package(Threads)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

include_directories(sequential/sequential)
set(SOURCE_FILES sequential/2DArray.c sequential/main.c sequential/matrix.c)
add_executable(MatrixMultiplication ${SOURCE_FILES})
target_link_libraries(MatrixMultiplication ${CMAKE_THREAD_LIBS_INIT})