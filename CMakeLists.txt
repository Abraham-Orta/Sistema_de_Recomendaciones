cmake_minimum_required(VERSION 3.14)

project(sistema_de_recomendaciones LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontrar Qt6 y activar automoc
find_package(Qt6 COMPONENTS Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Incluir directorio de headers
include_directories(include)

# Incluir archivos .h y .hpp como headers (opcional, útil para IDEs)
file(GLOB_RECURSE HEADERS "include/*.h" "include/*.hpp")

# Archivos fuente de la aplicación principal (excluyendo test_filtros.cpp)
file(GLOB SRC_FILES "src/*.cpp")
list(REMOVE_ITEM SRC_FILES "${CMAKE_SOURCE_DIR}/src/test_filtros.cpp")

# Ejecutable principal
add_executable(sistema_de_recomendaciones ${SRC_FILES} ${HEADERS})
target_link_libraries(sistema_de_recomendaciones Qt6::Widgets)

# Ejecutable para pruebas unitarias
add_executable(test_filtros src/test_filtros.cpp)
target_include_directories(test_filtros PRIVATE include)
# Si tus pruebas usan Qt, descomenta la siguiente línea:
# target_link_libraries(test_filtros Qt6::Widgets)