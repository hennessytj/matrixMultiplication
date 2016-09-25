cmake_minimum_required(VERSION 3.6)
project(MatrixMultiplication)
find_package(Threads)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

include_directories(sequential parallel)
set(SEQUENTIAL_SOURCES sequential/2DArray.c sequential/main.c sequential/matrix.c)
set(PTHREAD_SOURCES parallel/2DArray.c parallel/main.c parallel/matrix.c)

add_executable(MatrixMultiplicationSequential ${SEQUENTIAL_SOURCES})
target_link_libraries(MatrixMultiplicationSequential ${CMAKE_THREAD_LIBS_INIT})

add_executable(MatrixMultiplicationParallel ${PTHREAD_SOURCES})
target_link_libraries(MatrixMultiplicationParallel ${CMAKE_THREAD_LIBS_INIT})