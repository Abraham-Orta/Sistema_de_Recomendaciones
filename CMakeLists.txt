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
set(SRC_FILES
    src/main.cpp
    src/ventana_principal.cpp
    src/registro_dialog.cpp
    src/ventana_perfil.cpp
    src/arbol_usuarios.cpp
    src/ventana_inicial.cpp
    src/dialogo_registro_nuevo.cpp
    src/preferencias_dialogo.cpp
    src/recomendaciones.cpp
    src/filtros.cpp
    src/nodo_string.cpp
)

# Ejecutable principal
add_executable(sistema_de_recomendaciones ${SRC_FILES} ${HEADERS} resources.qrc)
target_link_libraries(sistema_de_recomendaciones Qt6::Widgets)

# Ejecutable para pruebas unitarias
add_executable(test_filtros src/test_filtros.cpp src/filtros.cpp)
target_include_directories(test_filtros PRIVATE include)
# Si tus pruebas usan Qt, descomenta la siguiente línea:
# target_link_libraries(test_filtros Qt6::Widgets)