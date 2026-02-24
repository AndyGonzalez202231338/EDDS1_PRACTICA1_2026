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
    src/CPPs/Menu.cpp

    src/collections/ListaJugadores.cpp
    src/collections/NodoCarta.cpp
    src/collections/NodoJugador.cpp

    src/game/CadenaRoboManager.cpp
    src/game/RoboManager.cpp
    src/game/JuegoUNO.cpp
    src/game/TurnoManager.cpp

    src/models/Carta.cpp
    src/models/CartaNumero.cpp     
    src/models/CartaAccion.cpp      
    src/models/CartaComodin.cpp
    src/models/CartaFlip.cpp    
    src/models/Jugador.cpp
    src/models/Mano.cpp
    src/models/Mazo.cpp
    src/models/Reglas.cpp
    src/models/VistaCarta.cpp
    src/models/CartaFlipSpecial.cpp
    src/models/CartaX.cpp
    src/models/CartaY.cpp

    src/utils/InputUtils.cpp
    src/utils/Colores.cpp
)

# Crear el ejecutable
add_executable(UNO ${SOURCES})

# Si quieres un nombre diferente para el ejecutable, cámbialo arriba
# add_executable(Practica1 ${SOURCES})

# Configuraciones adicionales (opcional)
# target_compile_options(UNO PRIVATE -Wall -Wextra)  # Habilitar warnings