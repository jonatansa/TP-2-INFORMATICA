
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define CONTACTOS "contactos.dat"

typedef struct{
	char n[20];
	char a[20];
	int e;
	long t;
	char m[50];
}lista_t;

typedef struct {
    lista_t dato;
    void *l;
} pila_t;

void datos();
void imprimirLista(lista_t);
