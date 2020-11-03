#include "cabecera.h"

long dato (orden_t x)
    {
    int d1,d2,m1,m2,a1,a2,a3,a4,df,mf,af;
    long ud;
    d1=x.fecha[0]-48;
    d2=x.fecha[1]-48;
    df=(d1*10)+d2;
    m1=x.fecha[3]-48;
    m2=x.fecha[4]-48;
    mf=m1*10+m2;
    a1=x.fecha[6]-48;
    a2=x.fecha[7]-48;
    a3=x.fecha[8]-48;
    a4=x.fecha[9]-48;
    af=a1*1000+a2*100+a3*10+a4;
    ud=(af)*10000+(mf)*100+(df);
    return ud;
}

fila_t lista_ordenada_por_fecha(void)
    {
    orden_t data;
    struct lista *aux,*r;
    fila_t local;
    FILE *fp;
    aux=r=NULL;
    local.p=local.u=NULL;
    if((fp=fopen("CosmeFulanito_ordenes.dat","rb"))== NULL)
        {
        printf("\n Error puede ser que no exita CosmeFulanito_ordenes.dat\n");
        system("pause");
        return;
    	}
    fread(&data,sizeof(repuestos_t),1,fp);

    while(!feof(fp))
        {
        aux=(struct lista *)malloc(sizeof(struct lista));
        if(local.p==NULL)
            {
            local.p=aux;
            local.u=aux;
            aux->sig=NULL;
            aux->ant=NULL;
            }
        else
            {
            r=local.p;
            if((aux->menu)<(local.p)->menu)
                {
                aux->sig=local.p;
                aux->ant=NULL;
                (local.p)->ant=aux;
                local.p=aux;
                }
            else
                {
                while(r->sig)
                    {
                    if((aux->menu)>=(r->menu))
                        r=r->sig;
                    else
                        break;
                    }
                if(r==local.u)
                    {
                    (local.u)->sig=aux;
                    aux->ant=local.u;
                    local.u=aux;
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
        fread(&data,sizeof(repuestos_t),1,fp);
        }

    fclose(fp);
    free(aux);
    return local;
    }

struct pila_t * pila_t_ordenada(fila_t local)
    {
    fila_t pilalocal;
    pilalocal=local;
    struct lista *auxl;
    struct pila_t *auxp,*p;
    auxl=NULL;
    auxp=NULL;
    p=NULL;
    auxl=pilalocal.u;
    while(auxl)
        {
        auxp=(struct pila_t *)malloc(sizeof(struct pila_t));
        auxp->numeroDeOrden=auxl->numeroDeOrden;
        strcpy(auxp->cliente,auxl->cliente);
        strcpy(auxp->descripciondeFalla,auxl->descripciondeFalla);
        strcpy(auxp->modelo,auxl->modelo);
        strcpy(auxp->fecha,auxl->fecha);
        strcpy(auxp->hora,auxl->hora);
        auxp->l=p;
        p=auxp;
        auxl=auxl->ant;
        }
    return p;
    }

void solicitud_tecnicos(struct pila_t *p_p)
    {
    struct pila_t *p_l;
    p_l=p_p;
    struct solicitud_tecnicos_t *aux,*p,*u,*r;
    long numpart,numser;
    char desc[40],ubica[100];
    int cant,bandera=0;
    aux=p=u=r=NULL;
    while(p_l)
        {
        aux=(struct solicitud_tecnicos_t *)malloc(sizeof(struct solicitud_tecnicos_t));
        printf("\n Ingrese Part Number: ");
        scanf("%ld",&numpart);
        aux->repuesto.partNumber=numpart;
        fflush(stdin);
        printf("\n Ingrese Serial Number: ");
        scanf("%ld",&numser);
        aux->repuesto.serialNumber=numser;
        fflush(stdin);
        printf("\n Ingrese descripcion: ");
        scanf("%s",desc);
        strcpy(aux->repuesto.descripcion,desc);
        fflush(stdin);
        printf("\n Ingrese ubicacion: ");
        scanf("%s",ubica);
        strcpy(aux->repuesto.ubicacion,ubica);
        fflush(stdin);
        printf("\n Ingrese cantidad: ");
        scanf("%d",&cant);
        aux->cantidad=cant;
        fflush(stdin);
        if(p==NULL)
            {
            p=u=aux;
            aux->sig=aux->ant=NULL;
            }
        else
            {
            r=p;
            while(r)
                {
                if(aux==r)
                    {
                    r->cantidad=r->cantidad+cant;
                    bandera=1;
                    break;
                    }
                else
                    r=r->sig;
                }
            if(bandera!=1)
                {
                aux->sig=p;
                aux->ant=NULL;
                p->ant=aux;
                p=aux;
                }
            }
        p_p=p_p->l;
        }
    printf("\nPila de ordenes vacia\n");
}
