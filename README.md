### main.c

Contiene la funcion principal `main`. Desde este archivo se inicia el programa, se configuran los limites iniciales y se controla el menu principal mediante un ciclo `do while` y una estructura `switch`.

### produccion.c

Contiene la implementacion de las funciones principales del sistema:

- Lectura y validacion de datos.
- Ingreso de productos.
- Visualizacion de productos.
- Busqueda de productos.
- Edicion de productos.
- Eliminacion de productos.
- Calculo de produccion.
- Configuracion de limites.
- Menu principal.

### produccion.h

Contiene las constantes, declaraciones externas de arreglos paralelos y prototipos de funciones.

## Compilacion

Para compilar el proyecto, ubicar los archivos `main.c`, `produccion.c` y `produccion.h` en la misma carpeta.

### Windows con GCC

```bash
gcc -Wall -Wextra -o produccion main.c produccion.c
```

Luego ejecutar:

```bash
produccion.exe
```

### Linux o Mac

```bash
gcc -Wall -Wextra -o produccion main.c produccion.c
./produccion
```