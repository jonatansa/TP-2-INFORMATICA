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
    orden_t x;
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
    fread(&x,sizeof(repuestos_t),1,fp);

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
        fread(&x,sizeof(repuestos_t),1,fp);
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

notifi extraer(struct pila_t *p_p)
    {
    struct pila_t *p_l;
    p_l=p_p;
    struct extraer_t_repuesto *aux,*r;
    long numparte,numserial;
    char desc[40],ubica[100];
    int cant,bandera=0;
    notifi extraer;
    extraer.p=extraer.u=NULL;
    aux=extraer.p=extraer.u=r=NULL;
    while(p_l)
        {
        aux=(struct extraer_t_repuesto *)malloc(sizeof(struct extraer_t_repuesto));
        printf("Ingrese Part Number: ");
        scanf("%ld",&numparte);
        aux->repuesto.partNumber=numparte;
        fflush(stdin);
        printf("Ingrese Serial Number: ");
        scanf("%ld",&numserial);
        aux->repuesto.serialNumber=numserial;
        fflush(stdin);
        printf("Ingrese descripcion: ");
        scanf("%s",desc);
        strcpy(aux->repuesto.descripcion,desc);
        fflush(stdin);
        printf("Ingrese ubicacion: ");
        scanf("%s",ubica);
        strcpy(aux->repuesto.ubicacion,ubica);
        fflush(stdin);
        printf("Ingrese cantidad: ");
        scanf("%d",&cant);
        aux->cantidad=cant;
        fflush(stdin);
        if(extraer.p==NULL)
            {
            extraer.p=extraer.u=aux;
            aux->sig=aux->ant=NULL;
            }
        else
            {
            r=extraer.p;
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
                aux->sig=extraer.p;
                aux->ant=NULL;
                extraer.p->ant=aux;
                extraer.p=aux;
                }
            }
        p_l=p_l->l;
        }
    printf("\n **** Pila de ordenes vacia ****\n");
    return extraer;
    }

void cargarstock(notifi extraer)
    {
    FILE *fp;
    struct extraer_t_repuesto *aux;
    repuestos_t auxx;
    int i,bandera;
    struct buscarstock *mover,*p,*u,*r;
    mover=p=u=r=NULL;
    aux=extraer.p;
    if((fp=fopen("CosmeFulanito_stock.dat","rb"))== NULL)
    {
    printf("\n Error puede ser que no exita CosmeFulanito_stock.dat\n");
    system("pause");
    return;
    }
    while(extraer.p)
        {
        for(i=0;i<(aux->cantidad);i++)
            {
            bandera=1;
            fread(&auxx,sizeof(repuestos_t),1,fp);
            if(auxx.partNumber==(aux->repuesto).partNumber)
                {
                if(auxx.partNumber!=0&&auxx.serialNumber!=0)
                    {
                    auxx.partNumber=auxx.serialNumber=0;
                    fseek(fp,(-1L)*sizeof(repuestos_t),1);
                    fwrite(&auxx,sizeof(repuestos_t),1,fp);
                    }
                else
                    bandera=0;
                }
            else
                bandera=0;
            if(bandera==0)
                {
                mover=(struct buscarstock *)malloc(sizeof(struct buscarstock));
                if(p==NULL)
                    {
                    p=u=mover;
                    mover->sig=mover->ant=NULL;
                    }
                else
                    {
                    mover->sig=p;
                    mover->ant=NULL;
                    p->sig=mover;
                    p=mover;
                    }
                }
            }
        extraer.p=(extraer.p)->sig;
        }
    fclose(fp);
    guardarArchivo();
    }

void guardarArchivo(void)
    {
    repuestos_t auxx;
    FILE *fp0,*fp1;
        if((fp0=fopen("CosmeFulanito_stock.dat","rb"))== NULL)
        {
        printf("\n Error puede ser que no exita CosmeFulanito_stock.dat\n");
        system("pause");
        return;
    	}
    fread(&auxx,sizeof(repuestos_t),1,fp0);
    while(!feof(fp0))
        {
        if(auxx.partNumber!=0&&auxx.serialNumber!=0)
        {
        if((fp1=fopen("CosmeFulanito_correccion.dat","ab"))== NULL)
        {
        printf("\n Error puede ser que no exita CosmeFulanito_correcion.dat\n");
        system("pause");
        return;
    	}
        fwrite(&auxx,sizeof(repuestos_t),1,fp1);
        fclose(fp1);
         }
        fread(&auxx,sizeof(repuestos_t),1,fp0);
        }
    fclose(fp0);
    remove("CosmeFulanito_stock.dat");
    rename("CosmeFulanito_ok.dat","CosmeFulanito_stock.dat");
    }
