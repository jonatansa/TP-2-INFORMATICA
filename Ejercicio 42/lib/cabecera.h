#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    long partNumber;
    long serialNumber;
    char descripcion[40];
    char ubicacion[40];
    }repuestos_t;

struct lista{
    long partNumber;
    long serialNumber;
    char descripcion[40];
    char ubicacion[40];
    struct lista *ant,*sig;
    };

typedef struct{
    struct lista *p,*u;
    }puntero_t;

puntero_t cola_regitros_fallados();
void baja();
void ParticaconFallas (puntero_t l);
void Correcion (repuestos_t x);
void vaciaMemoria();


    


