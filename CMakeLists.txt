# Versión mínima de CMake
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(Practica1)

# Configurar versión de C++ (ajusta según necesites)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Opcional: mostrar más información durante la compilación
set(CMAKE_VERBOSE_MAKEFILE ON)

# Incluir directorios de cabeceras
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/TADS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CPPs
)

# Listar explícitamente todos los archivos fuente
set(SOURCES
    src/CPPs/main.cpp
    src/CPPs/Carta.cpp
    src/CPPs/CartaNumero.cpp     
    src/CPPs/CartaAccion.cpp      
    src/CPPs/CartaComodin.cpp
    src/CPPs/CartaFlip.cpp    
    src/CPPs/JuegoUNO.cpp
    src/CPPs/Jugador.cpp
    src/CPPs/ListaJugadores.cpp
    src/CPPs/Mano.cpp
    src/CPPs/Mazo.cpp
    src/CPPs/Menu.cpp
    src/CPPs/NodoCarta.cpp
    src/CPPs/NodoJugador.cpp
    src/CPPs/Reglas.cpp
)

# Crear el ejecutable
add_executable(UNO ${SOURCES})

# Si quieres un nombre diferente para el ejecutable, cámbialo arriba
# add_executable(Practica1 ${SOURCES})

# Configuraciones adicionales (opcional)
# target_compile_options(UNO PRIVATE -Wall -Wextra)  # Habilitar warnings