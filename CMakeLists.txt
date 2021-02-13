# CMAKE minimum version
cmake_minimum_required(VERSION 3.17)

# Setup project
project("ADCS Math")

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find required libraries
find_package(glm CONFIG REQUIRED)
find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)
find_path(MATPLOTLIB_CPP_INCLUDE_DIRS "matplotlibcpp.h")
include_directories(${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})

# Clump source files from src
file(GLOB ADCS_SRC "src/*.cpp")

# Specify include directories
include_directories(include)

# Add source to this project's executable.
add_executable("ADCS" ${ADCS_SRC})

# Extra target linking
target_link_libraries("ADCS" PRIVATE glm ${Python3_LIBRARIES} Python3::NumPy)
target_include_directories("ADCS" PRIVATE ${MATPLOTLIB_CPP_INCLUDE_DIRS})