
#include "cabecera2.h"

void datos(){

	int salir;

	do{
		printf("1)Cargar Lista: ");
		printf("2)Salir(0): ");
		scanf("%d",&salir);
		switch(salir){
		case 1:
			leer();
			imprimir();
		break;
		}
		printf("Desea seguir?\n");
		printf("Salir(0): ");
		scanf("%d",&salir);
	}while(salir!=0);
}


void cargarLista(lista_t x,data_t** pri,data_t** u,data_t** r,data_t** aux){


	(*aux) = (data_t*)malloc (sizeof (data_t));
	(*aux)->dato = x;

	if ((*pri)==NULL && (*u)==NULL){
		(*pri)=(*u)=(*aux);
		(*aux)->ant = NULL;
		(*aux)->sig = NULL;
	}else{
		(*r) = (*pri);

		while(((*r) &&  (0 > strcmp(((*r)->dato).a,((*aux)->dato).a)) )||
				((*r) && (0 == strcmp(((*r)->dato).a,((*aux)->dato).a))
				&& (0 > strcmp(((*r)->dato).n,((*aux)->dato).n)))){
				(*r) = (*r)->sig;

		}
		if (!(*r)){
			(*u)->sig = (*aux);
			(*aux)->ant = (*u);
			(*aux)->sig = NULL;
			(*u) = (*aux);
		}else if ((*r)==(*pri)){
			(*aux)->sig = (*pri);
			(*pri)->ant = (*aux);
			(*aux)->ant = NULL;
			(*pri) = (*aux);
		}else{
			(*r) = (*r)->ant;
			(*aux)->sig = (*r)->sig;
			(*aux)->ant = (*r);
			((data_t*)((*r)->sig))->ant = (*aux);
			(*r)->sig = (*aux);
		}
	}

}

void Ord (data_t** pri,data_t** r,data_t** aux){
	lista_t x;

	FILE* fp = fopen (CONTACTOS_ORD,"wb+");
	x.e = -1; 
	fwrite(&x,sizeof(x),1,fp);
	if (!fp){
		printf("Error en la creacion del archivo %s",CONTACTOS_ORD);
		return;
	}

	(*r) = (*pri);
	
	while((*r)){
		fseek(fp,(-1L)*(long)sizeof(x),SEEK_END);
		fread(&x,sizeof(x),1,fp);
		fseek(fp,0L,SEEK_END);
		fwrite(&((*r)->dato),sizeof(x),1,fp);
		(*aux)= (*r);
		(*r) = (*r)->sig;
		free((*aux));
	}

	fclose(fp);
}

void leer(){
	data_t *pri=NULL;
	data_t *u=NULL;
	data_t *r=NULL;
	data_t *aux=NULL;

	FILE* fp = fopen (CONTACTOS,"rb");
	if (!fp){
		printf("Error en la apertura del archivo %s \n",CONTACTOS);
		return;
	}
	lista_t x;
	fread(&x,sizeof(x),1,fp);
	while(!feof(fp)){
		if (x.e > 21){
			cargarLista(x,&pri,&u,&r,&aux);
		}
		fread(&x,sizeof(x),1,fp);
	}

	fclose(fp);

	cargarArchivoOrdenado(&pri,&u,&aux);
}

void imprimir(){
	FILE* fp = fopen(CONTACTOS_ORD,"rb");
	lista_t x;

	if (fp == NULL){
		printf ("Error el archivo %s no existe\n",CONTACTOS_ORD);
		return;
	}

	fread(&x,sizeof(x),1,fp);
	while(!feof(fp)){
		if (x.e > -1){
			imprimirLista(x);
		}
		fread(&x,sizeof(x),1,fp);
	}
	fclose(fp);
}


