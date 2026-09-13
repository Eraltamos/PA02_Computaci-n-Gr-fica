cmake_minimum_required(VERSION 3.10)
project(PA2_ComputacionGrafica CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Directorios de encabezados
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Búsqueda de bibliotecas del sistema
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# Recopilación de archivos fuente
set(SOURCES
    src/main.cpp
    src/Application.cpp
    src/Camera.cpp
    src/Curves.cpp
    src/Model.cpp
    src/Scene.cpp
)

# Creación del ejecutable
add_executable(escena3d ${SOURCES})

# Enlace de bibliotecas
target_link_libraries(escena3d
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARIES}
)

if(APPLE)
    target_link_libraries(escena3d "-framework OpenGL -framework GLUT")
endif()