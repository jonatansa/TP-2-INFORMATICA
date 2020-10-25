#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define pot "potencia.dat"
#define sal "salida.dat"
typedef struct{
	char desc[60];
    unsigned char potencia;
    unsigned int estado;
}dat_t;

typedef struct{
	dat_t dato;
	void *ant;
	void *sig;
}lista_t;

typedef struct{
	dat_t dato;
	void* l;
}pila_t;

void ejerc();


