# CMAKE minimum version
cmake_minimum_required(VERSION 3.17)

# Setup project
project("ADCS Math")

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(POLICY CMP0091)
    # https://stackoverflow.com/a/56490614
    cmake_policy(SET CMP0091 NEW)
endif()

# The options need to be the same as Open3D's default
# If Open3D is configured and built with custom options, you'll also need to
# specify the same custom options.
option(STATIC_WINDOWS_RUNTIME "Use static (MT/MTd) Windows runtime" ON)
# This needs cmake_policy(SET CMP0091 NEW)
if (STATIC_WINDOWS_RUNTIME)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

# Find required libraries
find_package(glm CONFIG REQUIRED)
find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)
find_path(MATPLOTLIB_CPP_INCLUDE_DIRS "matplotlibcpp.h")
include_directories(${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})

# Find installed Open3D, which exports Open3D::Open3D
if(WIN32)
    find_package(Open3D HINTS ${CMAKE_INSTALL_PREFIX}/CMake)
else()
    find_package(Open3D HINTS ${CMAKE_INSTALL_PREFIX}/lib/cmake)
endif()

# Clump source files from src
file(GLOB ADCS_SRC "src/*.cpp" "src/**/*.cpp")

# Specify include directories
include_directories(include)

# Add source to this project's executable.
add_executable("ADCS" ${ADCS_SRC} src/adcs/KalmanFilter.cpp)

# Extra target linking
target_link_libraries("ADCS" PRIVATE glm ${Python3_LIBRARIES} Python3::NumPy Open3D::Open3D)
target_include_directories("ADCS" PRIVATE ${MATPLOTLIB_CPP_INCLUDE_DIRS})

# On Windows, when BUILD_SHARED_LIBS, copy .dll to the executable directory
if(WIN32)
    get_target_property(open3d_type Open3D::Open3D TYPE)
    if(open3d_type STREQUAL "SHARED_LIBRARY")
        message(STATUS "Will copy Open3D.dll to ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>")
        add_custom_command(TARGET TestVisualizer POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_INSTALL_PREFIX}/bin/Open3D.dll
                ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>)
    endif()
endif()

file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/assets)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/assets)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})