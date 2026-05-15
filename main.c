#include "produccion.h"

int main(void) {
    printf("\nSISTEMA DE OPTIMIZACION DE PRODUCCION\n");
    printf("Fabrica de Componentes Electronicos\n");
    printf("ISWZ1102 - Programacion I\n\n");
    printf("Antes de comenzar, configure los limites de tiempo y recursos disponibles.\n");

    configurarLimites();
    int opcion;
    
    do {
        mostrarMenu();
        opcion = pedirOpcion(0, 6);

        switch (opcion) {
            case 1:
                ingresarProducto();
                break;
            case 2:
                mostrarProductos();
                break;
            case 3:
                editarProducto();
                break;
            case 4:
                eliminarProducto();
                break;
            case 5:
                calcularProduccion();
                break;
            case 6:
                configurarLimites();
                break;
            case 0:
                printf("\nCerrando el sistema. Hasta luego.\n\n");
                break;
        }

        if (opcion != 0) {
            printf("\nPresione ENTER para continuar...");
            leerLinea(NULL, 0);
        }

    } while (opcion != 0);

    return 0;
}