# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project("Euronext Router")

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)  # Use C++17 or the desired version

# Add the source file
add_executable(euronext-router main.cpp)
