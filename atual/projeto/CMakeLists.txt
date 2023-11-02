cmake_minimum_required(VERSION 3.0)
project(MeuProgramaC++)

# Adicione os arquivos-fonte do seu programa aqui
set(SOURCES
    externo/alinear.cpp
    externo/luz.cpp
    tela/canvas.cpp
    ray/raio.cpp
    objetos/cilindro.cpp
    objetos/esfera.cpp
    objetos/cone.cpp
    objetos/plano.cpp
    objetos/malha.cpp
    objetos/teste.cpp
    cenario/cenario.cpp
    tela/janela.cpp
    externo/renderizar.cpp
    main.cpp
)

# Defina as opções de compilação, incluindo as flags do SDL2
add_executable(main ${SOURCES})
target_compile_options(main PRIVATE -Wall -Wextra -pedantic)
target_compile_features(main PRIVATE cxx_std_20) # para definir o padrão C++ para C++20

# Encontre a biblioteca SDL2
find_package(SDL2 REQUIRED)

# Inclua as bibliotecas SDL2
target_include_directories(main PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(main PRIVATE ${SDL2_LIBRARIES})
