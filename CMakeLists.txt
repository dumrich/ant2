cmake_minimum_required(VERSION 3.10)
set(EXECUTABLE_NAME ant)
project(ant2)

set(CMAKE_CXX_COMPILER clang++)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

# Add all source files in the 'src' directory
file(GLOB_RECURSE SOURCES "src/*.cc" "src/*.hh")

# Create the executable from the source files
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Find Boost components
find_package(Boost COMPONENTS system filesystem REQUIRED)

# Add include directories for Boost
include_directories(${Boost_INCLUDE_DIRS})

# Find NCurses
find_package(Curses REQUIRED)

# Add include directories for NCurses
# Link the executable with Boost and NCurses libraries
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} ${Boost_LIBRARIES} ${CURSES_LIBRARIES})
