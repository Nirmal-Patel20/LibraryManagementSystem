cmake_minimum_required(VERSION 3.23)
project(LibraryManagementSystem)

# C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Collect source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Optional: Collect headers for IDEs (not used for compilation)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS include/*.hpp include/*.h)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include path
target_include_directories(${PROJECT_NAME} PRIVATE include)
