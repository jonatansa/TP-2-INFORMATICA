#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
    {
    long partNumber;
    long serialNumber;
    char descripcion[40];
    char ubicacion[100];
    }repuestos_t;

typedef struct{
    long numeroDeOrden;
    char cliente[40];
    char descripciondeFalla[200];
    char modelo[65];
    char fecha[10];
    char hora[10];
    }orden_t;

struct lista{
    long numeroDeOrden;
    char cliente[40];
    char descripciondeFalla[200];
    char modelo[65];
    char fecha[10];
    char hora[10];
    struct lista *ant,*sig;
    long menu;
    };

struct pila_t{
    long numeroDeOrden;
    char cliente[40];
    char descripciondeFalla[200];
    char modelo[65];
    char fecha[10];
    char hora[10];
    struct pila_t *l;
    };

typedef struct{
    struct lista *p,*u;
    }fila_t;

struct solicitud_tecnicos_t{
    repuestos_t repuesto;
    int cantidad;
    struct solicitud_tecnicos_t *ant,*sig;
    };

long dato (orden_t);
fila_t lista_ordenada_por_fecha ();
struct pila_t * pila_t_ordenada (fila_t);
void solicitud_tecnicos(struct pila_t *);


