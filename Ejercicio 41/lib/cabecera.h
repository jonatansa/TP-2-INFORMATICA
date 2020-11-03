#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long partNumber;
    long serialNumber;
    char descripcion[40];
    char ubicacion[40];
    }repuestos_t;

struct lista {
    long partNumber;
    long serialNumber;
    char descripcion[40];
    char ubicacion[40];
    struct lista *ant,*sig;
    };

typedef struct{
    struct lista *p,*u;
    }puntero_t;
    
puntero_t carga (puntero_t x);
void imprimirLista (puntero_t x);
void generarArchivo (puntero_t x);
void vaciaMemoria ();


    


