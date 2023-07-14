cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(cache_monitor)

add_executable(cache_monitor
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/redis_handler.cpp
    ${CMAKE_SOURCE_DIR}/src/cache_value.cpp
    ${CMAKE_SOURCE_DIR}/src/topic_manager.cpp
    ${CMAKE_SOURCE_DIR}/src/topic.cpp
)

target_include_directories(cache_monitor PUBLIC ${CMAKE_SOURCE_DIR}/include)

find_path(HIREDIS_HEADER hiredis)
target_include_directories(cache_monitor PUBLIC ${HIREDIS_HEADER})

find_library(HIREDIS_LIB hiredis)
target_link_libraries(cache_monitor ${HIREDIS_LIB})

find_path(REDIS_PLUS_PLUS_HEADER sw)
target_include_directories(cache_monitor PUBLIC ${REDIS_PLUS_PLUS_HEADER})

find_library(REDIS_PLUS_PLUS_LIB redis++)
target_link_libraries(cache_monitor ${REDIS_PLUS_PLUS_LIB})

target_link_libraries(cache_monitor gtest)
include(CTest)
enable_testing()

