#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STOCK_ORD "productos_ordenados.dat"
#define STOCK "productos.dat"

typedef struct{
	long partNumber;
	long serialNumber;
	char descripcion[40];
	char ubicacion[100];
}respuestos_t;

typedef struct {
    respuestos_t dato;
    void *lazo;
}pila_t;

typedef struct{
	respuestos_t dato;
	void *ant;
	void *sig;
}lista_t;

void SolicitarDatos();
void generarListadeProdutos();
void imprimirStock(respuestos_t);

