cmake_minimum_required(VERSION 3.20)
project(MemoryPoolLab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(memory_pool_lab
    src/fixed_block_memory_pool.cpp
)

target_include_directories(memory_pool_lab PUBLIC include)

add_executable(memory_pool_demo
    src/main.cpp
)

target_link_libraries(memory_pool_demo PRIVATE memory_pool_lab)
