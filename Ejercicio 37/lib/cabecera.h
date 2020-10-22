
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define DATOS "datos.dat"

typedef struct{
long id;
char d[30];
unsigned char tipo;
char b;
}d_t;

typedef struct{
	long id;
	int pos;
}n_t;

typedef struct{
    n_t dato;
    void *l;
}p_t;

void datos();
