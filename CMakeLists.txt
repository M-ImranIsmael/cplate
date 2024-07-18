cmake_minimum_required(VERSION 3.10)
project(cplate)

# Set C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This will create compile_commands.json.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add your .exe target
add_executable(cplate main.cpp)
