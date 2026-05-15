#ifndef PRODUCCION_H
#define PRODUCCION_H

#include <stdio.h>

#define MAX_PRODUCTOS 5
#define MAX_NOMBRE 50

extern char nombres[MAX_PRODUCTOS][MAX_NOMBRE];
extern float tiempoPorUnidad[MAX_PRODUCTOS];
extern float recursosPorUnidad[MAX_PRODUCTOS];
extern int cantidadDemandada[MAX_PRODUCTOS];
extern int numProductos;

extern float tiempoDisponible;
extern float recursosDisponibles;

int leerLinea(char *buf, int maxLen);
int esDigito(char c);
int parsearEnteroPositivo(const char *buf);
float parsearFloatPositivo(const char *buf);
int pedirEnteroPositivo(const char *mensaje);
float pedirFloatPositivo(const char *mensaje);
void pedirCadena(const char *mensaje, char *destino, int maxLen);
int pedirOpcion(int min, int max);

int cadenaIgual(const char *a, const char *b);
void copiarCadena(char *dst, const char *src, int maxLen);

int buscarProducto(const char *nombre);
void mostrarProductos(void);
void ingresarProducto(void);
void editarProducto(void);
void eliminarProducto(void);
void calcularProduccion(void);
void configurarLimites(void);
void mostrarMenu(void);

#endif