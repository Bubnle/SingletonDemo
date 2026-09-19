cmake_minimum_required(VERSION 3.16)

project(SingletonDemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

add_executable(SingletonDemo
    src/main.cpp
    src/EagerSingleton.cpp
    src/LazySingleton.cpp
    src/MeyersSingleton.cpp
)

target_include_directories(SingletonDemo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(SingletonDemo PRIVATE
    Threads::Threads
)
