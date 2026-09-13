# PA02_Computaci-n-Gr-fica

# Producto Académico 2: Modelado y Construcción de una Escena 3D con OpenGL

Este proyecto corresponde a la implementación del Producto Académico 2 de la asignatura Computación Gráfica. Consiste en el diseño e implementación de una escena tridimensional interactiva de un entorno de laboratorio construida en C++ utilizando OpenGL y GLUT, estructurada modularmente con CMake. El prototipo incorpora 10 objetos diferenciables, mallas poligonales, carga de 1 modelo Wavefront (.obj), una curva paramétrica de Bézier, una superficie analítica generada por revolución, transformaciones afines, visualización en malla alámbrica (wireframe), una cámara orbital con tres vistas predefinidas y modelado jerárquico articulado.

## Requisitos del Sistema
* Compilador de C++ compatible con C++17 (GCC/MinGW, Clang o MSVC).
* CMake (versión 3.10 o superior).
* Bibliotecas de desarrollo de OpenGL y FreeGLUT / GLUT instaladas en el sistema.

## Compilación y Ejecución

### Windows (MinGW Makefiles)
Para generar los archivos de compilación y compilar desde la raíz del proyecto:
```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .

```

Para ejecutar el binario asegurando el enlace de los recursos (`assets/`):

```bash
cd ..
.\build\escena3d.exe

```


## Controles de Interacción (Teclado)

* **1 / 2**: Rotar la base del brazo robótico sobre el eje Y (Modelado Jerárquico).


* **3 / 4**: Rotar la articulación del hombro sobre el eje Z (Modelado Jerárquico).


* **5 / 6**: Rotar la articulación del codo sobre el eje Z (Modelado Jerárquico).


* **V**: Alternar cíclicamente entre las 3 vistas de cámara (Perspectiva general, Superior cenital y Lateral).


* **W**: Activar/desactivar la visualización en malla alámbrica (*wireframe*) del módulo de control.


* **Flechas direccionales**: Orbitar la cámara libremente alrededor del escenario.


* **\+ / -**: Acercar o alejar el zoom de la cámara.


* **ESC**: Cerrar la aplicación.

## Elaboración

* **Asignatura:** Computación Gráfica


* **Institución:** Universidad Continental


* **Docente:** Mg. Percy Maldonado Quispe


* **Integrante:** Erwin Alain Felix Tayro Mosqueira

## Licencia

Este proyecto se distribuye bajo la Licencia MIT. Para más detalles, consulte los términos estándar de código abierto.
