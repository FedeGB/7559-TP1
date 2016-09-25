cmake_minimum_required(VERSION 3.2)
project(TP1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/PlatoComida.cpp src/PlatoComida.h src/Menu.cpp src/Menu.h src/Logger.cpp src/Logger.h src/ConfigLoader.cpp src/ConfigLoader.h src/Fifo.cpp src/Fifo.h src/FifoEscritura.cpp src/FifoEscritura.h src/FifoLectura.cpp src/FifoLectura.h src/Pipe.cpp src/Pipe.h src/Proceso.cpp src/Proceso.h src/Cliente.cpp src/Cliente.h src/Semaforo.cpp src/Semaforo.h src/LockFile.cpp src/LockFile.h src/Recepcionista.cpp src/Recepcionista.h src/IDSemaforos.h src/Utils.h src/Utils.cpp)
add_executable(TP1 ${SOURCE_FILES})