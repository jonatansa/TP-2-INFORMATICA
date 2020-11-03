#include "cabecera.h"

puntero_t cola_regitros_fallados(void)
    {
    struct lista *aux;
    puntero_t l;
    FILE *fp;
    l.p=NULL;
    l.u=NULL;
    aux=NULL;
    repuestos_t x;
    if((fp=fopen("CosmeFulanito_stock.dat","rb"))== NULL)
        {
        printf("\n Error puede ser que no exita CosmeFulanito_stock.dat\n");
        system("pause");
        return;
    	}
    fread(&x,sizeof(repuestos_t),1,fp);

    while(!feof(fp))
        {
        if(x.partNumber==1234)
            if(x.serialNumber&0x28)
                {
                aux=(struct lista *)malloc(sizeof(struct lista));
                aux->partNumber=x.partNumber;
                aux->serialNumber=x.serialNumber;
                strcpy(aux->descripcion,x.descripcion);
                strcpy(aux->ubicacion,x.ubicacion);
                if(l.p==NULL)
                    {
                    l.p=aux;
                    l.u=aux;
                    aux->sig=NULL;
                    aux->ant=NULL;
                    }
                else
                    {
                    aux->sig=l.u;
                    aux->ant=NULL;
                    (l.u)->ant=aux;
                    l.u=aux;
                    }
                }
        else
        Correcion(x);
        fread(&x,sizeof(repuestos_t),1,fp);
        }
    return l;
    }

void ParticaconFallas (puntero_t l)
    {
    struct lista *aux;
    puntero_t partidanueva;
    FILE *fp;
    partidanueva=l;
    aux=NULL;
    aux=partidanueva.u;
    while(aux)
    {
    if((fp=fopen("Partida_con_fallas.dat","ab"))== NULL)
    {
        printf("\n Error puede ser que no exita Partida_con_fallas.dat\n");
        system("pause");
        return;
   	}
        fwrite(aux,sizeof(repuestos_t),1,fp);
        fclose(fp);
        aux=aux->ant;
        }
    free(aux);
    }

void Correcion (repuestos_t x)
    {
    FILE *fp;
    if((fp=fopen("CosmeFulanito_fallados.dat","ab"))== NULL)
    {
        printf("\n Error puede ser que no exita Partida_con_fallas.dat\n");
        system("pause");
        return;
   	}
    fwrite(&x,sizeof(repuestos_t),1,fp);
    fclose(fp);
    }

void baja(void)
    {
    remove("CosmeFulanito_stock.dat");
    rename("Partida_con_fallas.dat","CosmeFulanito_stock.dat");
    }

void vaciaMemoria(void)
    {
    FILE *fp;
    if((fp=fopen("CosmeFulanito_correccion.dat","wb"))== NULL)
        {
        printf("\n Error puede ser que no exita CosmeFulanito_correccion.dat\n");
        system("pause");
        return;
    	}
    fclose(fp);
    if((fp=fopen("Partida_con_fallas.dat","wb"))== NULL)
        {
        printf("\n Error puede ser que no exita Partida_con_fallas.dat\n");
        system("pause");
        return;
    	}
    fclose(fp);
    }
