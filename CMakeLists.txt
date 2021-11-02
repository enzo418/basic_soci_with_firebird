cmake_minimum_required(VERSION 3.12)
project(soci_firebird_cmake)

find_package(SOCI REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(soci_firebird_cmake main.cpp)

target_link_libraries(soci_firebird_cmake PUBLIC SOCI::soci_core SOCI::soci_firebird)