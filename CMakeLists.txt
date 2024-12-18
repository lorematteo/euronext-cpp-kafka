# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project("Euronext Router")

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)  # Use C++17 or the desired version

# Specify the include directory for headers
include_directories(src/include)

# Specify the include directory for librdkafka
include_directories(/opt/homebrew/include)

# Specify the library directory for librdkafka
link_directories(/opt/homebrew/lib)

# Add the source file
add_executable(euronext-router src/main.cpp src/utils/producer.cpp)

# Link the librdkafka library
target_link_libraries(euronext-router rdkafka)
