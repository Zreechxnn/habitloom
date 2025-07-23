cmake_minimum_required(VERSION 3.15)
project(HabitLoom VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt configuration
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Core Concurrent Gui REQUIRED)

# Include directories
include_directories(
    src
    thirdparty
)

# Resources
file(GLOB_RECURSE QRC_FILES "resources/*.qrc")
qt_add_resources(RESOURCE_RCC ${QRC_FILES})
# Source files
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/UI/*.cpp"
    "src/HabitLoom/*.cpp"
)

add_executable(HabitLoom
    ${SOURCES}
    ${RESOURCE_RCC}
)

# Link Qt libraries
target_link_libraries(HabitLoom PRIVATE
    Qt5::Widgets
    Qt5::Core
    Qt5::Concurrent
    Qt5::Gui
)

# Install target
install(TARGETS HabitLoom DESTINATION bin)
install(DIRECTORY data/ DESTINATION data)