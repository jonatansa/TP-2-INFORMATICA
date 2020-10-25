#include "cabecera.h"

void cargarLista(respuestos_t respuesto,lista_t** p,lista_t** u,lista_t** r,lista_t** aux){

	(*aux) = (lista_t*)malloc (sizeof (lista_t));
	(*aux)->dato = respuesto;

	if ((*p)==NULL && (*u)==NULL){
		(*p)=(*u)=(*aux);
		(*aux)->ant = NULL;
		(*aux)->sig = NULL;
	}else{
		(*r) = (*p);

		while(((*r) &&  (0 > strcmp(((*r)->dato).descripcion,((*aux)->dato).descripcion)) )||
				((*r) && (0 == strcmp(((*r)->dato).descripcion,((*aux)->dato).descripcion))
				&& (0 > strcmp(((*r)->dato).ubicacion,((*aux)->dato).ubicacion)))){
				(*r) = (*r)->sig;
		}
		if (!(*r)){
			(*u)->sig = (*aux);
			(*aux)->ant = (*u);
			(*aux)->sig = NULL;
			(*u) = (*aux);
		}else if ((*r)==(*p)){
			(*aux)->sig = (*p);
			(*p)->ant = (*aux);
			(*aux)->ant = NULL;
			(*p) = (*aux);
		}else{
			(*r) = (*r)->ant;
			(*aux)->sig = (*r)->sig;
			(*aux)->ant = (*r);
			((lista_t*)((*r)->sig))->ant = (*aux);
			(*r)->sig = (*aux);
		}
	}
}

void cargarStockOrdenado(lista_t** p,lista_t** r,lista_t** aux){
	respuestos_t respuesto;
	FILE* fp = fopen (STOCK_ORD,"wb+");
	respuesto.partNumber= -1;
	fwrite(&respuesto,sizeof(respuesto),1,fp);
	if (!fp){
		printf("No se puede crear %s .... \n",STOCK_ORD);
		return;
	}

	(*r) = (*p);
	while((*r)){
		fseek(fp,(-1L)*(long)sizeof(respuesto),SEEK_END);
		fread(&respuesto,sizeof(respuesto),1,fp);
		fseek(fp,0L,SEEK_END);
		fwrite(&((*r)->dato),sizeof(respuesto),1,fp);
		(*aux)= (*r);
		(*r) = (*r)->sig;
		free((*aux));
	}
	fclose(fp);
}

void leerArchivo(){
	lista_t *p=NULL;
	lista_t *u=NULL;
	lista_t *r=NULL;
	lista_t *aux=NULL;
	FILE* fp = fopen (STOCK_ORD,"rb");
	if (!fp){
		printf("No se puede leer %s ... \n",STOCK_ORD);
		return;
	}
	respuestos_t respuesto;
	fread(&respuesto,sizeof(respuesto),1,fp);
	while(!feof(fp)){
		cargarLista(respuesto,&p,&u,&r,&aux);
		fread(&respuesto,sizeof(respuesto),1,fp);
	}
	fclose(fp);
	cargarStockOrdenado(&p,&u,&aux);
}

void imprimirStockOrdenado(){
	FILE* fp = fopen(STOCK_ORD,"rb");
	respuestos_t respuesto;
	if (fp == NULL){
		printf ("No puedo leer el archivo %s ... \n",STOCK_ORD);
		return;
	}
	fread(&respuesto,sizeof(respuesto),1,fp);
	while(!feof(fp)){
		imprimirStock(respuesto);
		fread(&respuesto,sizeof(respuesto),1,fp);
	}
	fclose(fp);
}

void generarListadeProdutos()
{
	leerArchivo();
	imprimirStockOrdenado();
}
