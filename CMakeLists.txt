cmake_minimum_required(VERSION 3.14)

project(sistema_de_recomendaciones LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

add_executable(sistema_de_recomendaciones ${SOURCES} ${HEADERS})

target_link_libraries(sistema_de_recomendaciones Qt6::Core Qt6::Gui Qt6::Widgets)