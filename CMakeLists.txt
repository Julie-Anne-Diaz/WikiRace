cmake_minimum_required(VERSION 3.30)
project(WikiRace)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This will have to be changed to link to your SFML directory.
set(SFML_DIR "C:/Users/Bradley Cederholm/CLionProjects/WikiRace/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)
add_executable(WikiRace main.cpp)
target_link_libraries(WikiRace sfml-system sfml-window sfml-graphics sfml-audio)