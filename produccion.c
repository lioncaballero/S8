#include "produccion.h"

char nombres[MAX_PRODUCTOS][MAX_NOMBRE];
float tiempoPorUnidad[MAX_PRODUCTOS];
float recursosPorUnidad[MAX_PRODUCTOS];
int cantidadDemandada[MAX_PRODUCTOS];
int numProductos = 0;

float tiempoDisponible = 0.0f;
float recursosDisponibles = 0.0f;

int leerLinea(char *buf, int maxLen) {
    int i = 0;
    int c;

    if (buf == NULL || maxLen <= 0) {
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        return 0;
    }

    while (i < maxLen - 1) {
        c = getchar();
        if (c == EOF || c == '\n') {
            break;
        }
        buf[i] = (char)c;
        i++;
    }

    buf[i] = '\0';

    if (i == maxLen - 1 && c != '\n' && c != EOF) {
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }

    return i;
}

int esDigito(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    return -1;
}

int parsearEnteroPositivo(const char *buf) {
    int valor = 0;
    int i = 0;
    int d;

    if (buf[0] == '\0') {
        return -1;
    }

    while (buf[i] != '\0') {
        d = esDigito(buf[i]);
        if (d == -1) {
            return -1;
        }
        valor = valor * 10 + d;
        i++;
    }

    if (valor > 0) {
        return valor;
    }

    return -1;
}

float parsearFloatPositivo(const char *buf) {
    float entero = 0.0f;
    float decimal = 0.0f;
    float divisor = 10.0f;
    int i = 0;
    int d;
    int tieneDecimal = 0;
    int digitosDespuesDecimal = 0;

    if (buf[0] == '\0') {
        return -1.0f;
    }

    while (buf[i] != '\0') {
        if (buf[i] == '.' || buf[i] == ',') {
            if (tieneDecimal) {
                return -1.0f;
            }
            tieneDecimal = 1;
            i++;
            continue;
        }

        d = esDigito(buf[i]);
        if (d == -1) {
            return -1.0f;
        }

        if (!tieneDecimal) {
            entero = entero * 10.0f + (float)d;
        } else {
            decimal += (float)d / divisor;
            divisor *= 10.0f;
            digitosDespuesDecimal++;
        }

        i++;
    }

    if (tieneDecimal && digitosDespuesDecimal == 0) {
        return -1.0f;
    }

    if (entero + decimal > 0.0f) {
        return entero + decimal;
    }

    return -1.0f;
}

int pedirEnteroPositivo(const char *mensaje) {
    char buf[32];
    int valor;

    while (1) {
        printf("%s", mensaje);
        leerLinea(buf, 32);
        valor = parsearEnteroPositivo(buf);

        if (valor != -1) {
            return valor;
        }

        printf("[ERROR] Ingrese un entero positivo valido. No use letras ni cero.\n");
    }
}

float pedirFloatPositivo(const char *mensaje) {
    char buf[32];
    float valor;

    while (1) {
        printf("%s", mensaje);
        leerLinea(buf, 32);
        valor = parsearFloatPositivo(buf);

        if (valor > 0.0f) {
            return valor;
        }

        printf("[ERROR] Ingrese un numero positivo valido. Ejemplo: 8 o 3.75.\n");
    }
}

void pedirCadena(const char *mensaje, char *destino, int maxLen) {
    int len;

    while (1) {
        printf("%s", mensaje);
        len = leerLinea(destino, maxLen);

        if (len > 0) {
            return;
        }

        printf("[ERROR] El nombre no puede estar vacio.\n");
    }
}

int pedirOpcion(int min, int max) {
    char buf[16];
    int valor;

    while (1) {
        printf("Seleccione una opcion [%d-%d]: ", min, max);
        leerLinea(buf, 16);

        if (buf[0] == '0' && buf[1] == '\0') {
            valor = 0;
        } else {
            valor = parsearEnteroPositivo(buf);
        }

        if (valor >= min && valor <= max) {
            return valor;
        }

        printf("[ERROR] Opcion invalida. Intente de nuevo.\n");
    }
}

int cadenaIgual(const char *a, const char *b) {
    int i = 0;
    char ca;
    char cb;

    while (a[i] != '\0' && b[i] != '\0') {
        ca = a[i];
        cb = b[i];

        if (ca >= 'A' && ca <= 'Z') {
            ca = (char)(ca + 32);
        }

        if (cb >= 'A' && cb <= 'Z') {
            cb = (char)(cb + 32);
        }

        if (ca != cb) {
            return 0;
        }

        i++;
    }

    return a[i] == '\0' && b[i] == '\0';
}

void copiarCadena(char *dst, const char *src, int maxLen) {
    int i;

    for (i = 0; i < maxLen - 1 && src[i] != '\0'; i++) {
        dst[i] = src[i];
    }

    dst[i] = '\0';
}

int nombreEsValido(const char *nombre) {
    int i = 0;
    char c;

    if (nombre[0] == '\0') {
        return 0;
    }

    while (nombre[i] != '\0') {
        c = nombre[i];

        if (!((c >= 'a' && c <= 'z') ||
              (c >= 'A' && c <= 'Z') ||
              c == ' ')) {
            return 0;
        }

        i++;
    }

    return 1;
}

void pedirNombre(const char *mensaje, char *destino, int maxLen) {
    int len;

    while (1) {
        printf("%s", mensaje);
        len = leerLinea(destino, maxLen);

        if (len == 0) {
            printf("[ERROR] El nombre no puede estar vacio.\n");
            continue;
        }

        if (len >= maxLen - 1) {
            printf("[ERROR] El nombre es demasiado largo. Maximo %d caracteres.\n", maxLen - 1);
            continue;
        }

        if (!nombreEsValido(destino)) {
            printf("[ERROR] El nombre solo puede contener letras y espacios. No se permiten numeros ni simbolos.\n");
            continue;
        }

        return;
    }
}

void mostrarProductos(void) {
    int i;

    if (numProductos == 0) {
        printf("\nNo hay productos registrados.\n");
        return;
    }

    printf("\nLista de productos registrados\n");
    printf("%-4s %-22s %-14s %-14s %-10s\n",
           "No.", "Producto", "Tiempo h/u", "Recursos/u", "Demanda");

    for (i = 0; i < numProductos; i++) {
        printf("%-4d %-22s %-14.2f %-14.2f %-10d\n",
               i + 1,
               nombres[i],
               tiempoPorUnidad[i],
               recursosPorUnidad[i],
               cantidadDemandada[i]);
    }
}

void ingresarProducto(void) {
    char nombre[MAX_NOMBRE];

    printf("\nINGRESAR NUEVO PRODUCTO\n");

    if (numProductos >= MAX_PRODUCTOS) {
        printf("[AVISO] Se alcanzo el limite maximo de %d productos.\n", MAX_PRODUCTOS);
        return;
    }

    pedirNombre("Nombre del producto: ", nombre, MAX_NOMBRE);

    if (buscarProducto(nombre) != -1) {
        printf("[ERROR] Ya existe un producto con ese nombre. Operacion cancelada.\n");
        return;
    }

    copiarCadena(nombres[numProductos], nombre, MAX_NOMBRE);
    tiempoPorUnidad[numProductos] = pedirFloatPositivo("Tiempo de fabricacion por unidad en horas: ");
    recursosPorUnidad[numProductos] = pedirFloatPositivo("Recursos por unidad: ");
    cantidadDemandada[numProductos] = pedirEnteroPositivo("Cantidad demandada: ");

    numProductos++;

    printf("[OK] Producto registrado correctamente.\n");
}

int buscarProducto(const char *nombre) {
    int i;

    for (i = 0; i < numProductos; i++) {
        if (cadenaIgual(nombres[i], nombre)) {
            return i;
        }
    }

    return -1;
}

void editarProducto(void) {
    char nombre[MAX_NOMBRE];
    int idx;
    int op;

    printf("\nEDITAR PRODUCTO\n");

    if (numProductos == 0) {
        printf("No hay productos para editar.\n");
        return;
    }

    mostrarProductos();
    pedirNombre("\nNombre del producto a editar: ", nombre, MAX_NOMBRE);

    idx = buscarProducto(nombre);

    if (idx == -1) {
        printf("[ERROR] No se encontro el producto.\n");
        return;
    }

    printf("\nProducto encontrado: %s\n", nombres[idx]);
    printf("1. Nombre\n");
    printf("2. Tiempo de fabricacion\n");
    printf("3. Recursos por unidad\n");
    printf("4. Cantidad demandada\n");
    printf("0. Cancelar\n");

    op = pedirOpcion(0, 4);

    switch (op) {
        case 0:
            printf("Edicion cancelada.\n");
            return;

        case 1: {
            char nuevoNombre[MAX_NOMBRE];
            int existe;

            pedirNombre("Nuevo nombre: ", nuevoNombre, MAX_NOMBRE);
            existe = buscarProducto(nuevoNombre);

            if (existe != -1 && existe != idx) {
                printf("[ERROR] Ya existe otro producto con ese nombre.\n");
                return;
            }

            copiarCadena(nombres[idx], nuevoNombre, MAX_NOMBRE);
            break;
        }

        case 2:
            tiempoPorUnidad[idx] = pedirFloatPositivo("Nuevo tiempo en horas por unidad: ");
            break;

        case 3:
            recursosPorUnidad[idx] = pedirFloatPositivo("Nuevos recursos por unidad: ");
            break;

        case 4:
            cantidadDemandada[idx] = pedirEnteroPositivo("Nueva cantidad demandada: ");
            break;
    }

    printf("[OK] Producto actualizado correctamente.\n");
}

void eliminarProducto(void) {
    char nombre[MAX_NOMBRE];
    int idx;
    int conf;
    int i;
    int k;

    printf("\nELIMINAR PRODUCTO\n");

    if (numProductos == 0) {
        printf("No hay productos para eliminar.\n");
        return;
    }

    mostrarProductos();
    pedirNombre("\nNombre del producto a eliminar: ", nombre, MAX_NOMBRE);

    idx = buscarProducto(nombre);

    if (idx == -1) {
        printf("[ERROR] No se encontro el producto.\n");
        return;
    }

    printf("\nProducto encontrado: %s\n", nombres[idx]);
    printf("1. Si, eliminar\n");
    printf("2. No, cancelar\n");

    conf = pedirOpcion(1, 2);

    if (conf == 2) {
        printf("Eliminacion cancelada.\n");
        return;
    }

    for (i = idx; i < numProductos - 1; i++) {
        for (k = 0; k < MAX_NOMBRE; k++) {
            nombres[i][k] = nombres[i + 1][k];
        }

        tiempoPorUnidad[i] = tiempoPorUnidad[i + 1];
        recursosPorUnidad[i] = recursosPorUnidad[i + 1];
        cantidadDemandada[i] = cantidadDemandada[i + 1];
    }

    numProductos--;

    printf("[OK] Producto eliminado correctamente.\n");
}

void calcularProduccion(void) {
    float tiempoTotal = 0.0f;
    float recursosTotal = 0.0f;
    int viable = 1;
    int i;

    printf("\nCALCULO DE PRODUCCION\n");

    if (numProductos == 0) {
        printf("No hay productos registrados.\n");
        return;
    }

    printf("\nResultado por producto\n");
    printf("%-22s %-18s %-18s\n", "Producto", "Tiempo total", "Recursos total");

    for (i = 0; i < numProductos; i++) {
        float tiempoProducto = tiempoPorUnidad[i] * (float)cantidadDemandada[i];
        float recursosProducto = recursosPorUnidad[i] * (float)cantidadDemandada[i];

        tiempoTotal += tiempoProducto;
        recursosTotal += recursosProducto;

        printf("%-22s %-18.2f %-18.2f\n",
               nombres[i],
               tiempoProducto,
               recursosProducto);
    }

    printf("\nTotales generales\n");
    printf("Tiempo requerido: %.2f horas\n", tiempoTotal);
    printf("Recursos requeridos: %.2f unidades\n", recursosTotal);
    printf("Tiempo disponible: %.2f horas\n", tiempoDisponible);
    printf("Recursos disponibles: %.2f unidades\n", recursosDisponibles);

    printf("\nResultado de viabilidad\n");

    if (tiempoTotal > tiempoDisponible) {
        printf("[X] Tiempo insuficiente. Deficit: %.2f horas.\n", tiempoTotal - tiempoDisponible);
        viable = 0;
    } else {
        printf("[OK] Tiempo suficiente. Excedente: %.2f horas.\n", tiempoDisponible - tiempoTotal);
    }

    if (recursosTotal > recursosDisponibles) {
        printf("[X] Recursos insuficientes. Deficit: %.2f unidades.\n", recursosTotal - recursosDisponibles);
        viable = 0;
    } else {
        printf("[OK] Recursos suficientes. Excedente: %.2f unidades.\n", recursosDisponibles - recursosTotal);
    }

    if (viable) {
        printf("\nLa fabrica puede cumplir con toda la demanda.\n");
    } else {
        printf("\nLa fabrica no puede cumplir con toda la demanda.\n");
    }
}

void configurarLimites(void) {
    printf("\nCONFIGURAR LIMITES DE FABRICA\n");
    tiempoDisponible = pedirFloatPositivo("Tiempo total disponible en horas: ");
    recursosDisponibles = pedirFloatPositivo("Recursos totales disponibles en unidades: ");
    printf("[OK] Limites configurados correctamente.\n");
}

void mostrarMenu(void) {
    printf("\nMENU PRINCIPAL\n");
    printf("1. Ingresar producto\n");
    printf("2. Ver todos los productos\n");
    printf("3. Editar producto\n");
    printf("4. Eliminar producto\n");
    printf("5. Calcular y verificar produccion\n");
    printf("6. Configurar limites de fabrica\n");
    printf("0. Salir del sistema\n");
}