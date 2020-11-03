#include "cabecera.h"

puntero_t carga (puntero_t x)
    {
    repuestos_t repuestos;
    puntero_t l;
    l.p=x.p;
    l.u=x.u;
    struct lista *aux,*r;
    r=aux=NULL;
    aux=(struct lista *)malloc(sizeof(struct lista));
    
	printf("------------------------------------------------\n");
	printf("\n *** Lista de respuesto *** \n");
    printf("\n Ingrese el Numero de parte: ");
    scanf("%ld",&repuestos.partNumber);
    aux->partNumber=repuestos.partNumber;
    fflush(stdin);
    printf("\n Ingrese el Numero de Serial: ");
    scanf("%ld",&repuestos.serialNumber);
    aux->serialNumber=repuestos.serialNumber;
    fflush(stdin);
    printf("\n Ingrese la Descripcion: ");
    scanf("%s",repuestos.descripcion);
    strcpy(aux->descripcion,repuestos.descripcion);
    fflush(stdin);
    printf("\n Ingrese la Ubicacion: ");
    scanf("%s",repuestos.ubicacion);
    strcpy(aux->ubicacion,repuestos.ubicacion);
    fflush(stdin);

    if(l.p==NULL)
        {
        l.p=aux;
        l.u=aux;
        aux->sig=NULL;
        aux->ant=NULL;
        }
    else
        {
        r=l.p;
        if(strcmp(aux->descripcion,(l.p)->descripcion)<=0)
            {
            aux->sig=l.p;
            aux->ant=NULL;
            (l.p)->ant=aux;
            l.p=aux;
            }
        else
            {
            while(r->sig)
                {
                if(strcmp(aux->descripcion,r->sig->descripcion)>=0)
                    r=r->sig;
                else
                    break;
                }
            if(r==l.u)
                {
                (l.u)->sig=aux;
                aux->ant=l.u;
                l.u=aux;
                aux->sig=NULL;
                }
            else
                {
                aux->sig=r->sig;
                aux->ant=r;
                r->sig=aux;
                }
            }
        }
    return l;
    }

void imprimirLista (puntero_t x)
    {
    struct lista *aux;
    int i=0;
    aux=x.p;
    while(aux)
        {
        i++;
        printf("----------------------------------------------------\n");
        printf("\n Part Number: %ld",aux->partNumber);
        printf("\n Serial Number: %ld",aux->serialNumber);
        printf("\n Descripcion: %s",aux->descripcion);
        printf("\n Ubicacion: %s",aux->ubicacion);
        printf("\n----------- Numero de Orden -------------%04d------\n",i);
		aux=aux->sig;
        }
    free(aux);
    }

void generarArchivo (puntero_t x)
    {
    long i=0;
    struct lista *aux;
    FILE *fp;
    aux=x.p;
    while(aux)
        {
        i++;
        int size;
        fp=fopen("CosmeFulanito_stock.dat","ab");
        size=fwrite(aux,sizeof(struct lista),1,fp);
        if(size)
        printf("\n Registro %ld guardado con exito",i);
        fclose(fp);
        aux=aux->sig;
        }
    free(aux);
    }

void vaciaMemoria (void)
    {
    FILE *fp;
    fp=fopen("CosmeFulanito_stock.dat","w");
    fclose(fp);
    }


