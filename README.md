Proyecto II — CI-0113 Programación II
Árbol Roji-Negro

Autores: Sergio Solano Mora — Ignacio Quirós Paniagua
Semestre: II 2025

Descripción general

Este proyecto implementa:

Un Árbol Roji-Negro (RB Tree) genérico basado en herencia desde un Árbol BST.

Soporte para:

int
string

Objetos personalizados

Generación visual usando SVG.

Implementación de una tabla hash asociativa RBHash, donde la clave es un string y los valores pueden ser de cualquier tipo (int, string, objetos…).

Estructura del Proyecto
include/
    bstTree.h
    arbolRB.h
    rbhash.h
    persona.h    

src/
    bstTree.cpp
    arbolRB.cpp
    rbhash.cpp     (si aplica)
    main.cpp
    persona.cpp    (opcional)

assets/
    svgTreeViewerTemplate.html

output/
    *.html         --> aquí se generan los SVG del programa

Makefile
README.md

Compilación con Makefile

Para compilar:

make


Para ejecutar:

make run


Para limpiar:

make clean

Compilación manual (sin Makefile)

Windows (MinGW / g++)

g++ -std=c++17 -Wall -Wextra -o programa \
    src/main.cpp \
    src/bstTree.cpp \
    src/arbolRB.cpp \
    src/rbhash.cpp \
    -I include

Linux / macOS

g++ -std=c++17 -Wall -Wextra -o programa \
    src/*.cpp \
    -I include

Luego ejecutar:

./programa

Notas importantes

El archivo assets/svgTreeViewerTemplate.html NO debe borrarse, ya que es la plantilla utilizada para generar los demás SVGs.

Todos los archivos generados por toSVG() se guardan automáticamente en la carpeta output/.

No se utiliza STL como vectores, listas o mapas, cumpliendo las restricciones del proyecto.

Nota de Transparencia

Parte del código fue generado con apoyo de herramientas de IA.
Todo el contenido fue revisado, corregido y supervisado manualmente por
Sergio Solano y Ignacio Quirós para asegurar funcionalidad y cumplimiento con los requerimientos del curso.