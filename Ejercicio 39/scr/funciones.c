#include "cabecera.h"

dat_t usuario(){
	dat_t datos;
	int i;
	printf("Descripcion de potencia: \n");
	fflush(stdin);
	gets(datos.desc);
	fflush(stdin);
	do{
		printf("Datos Medidos (potencia): \n");
		scanf("%d",&i);
		datos.potencia = (unsigned char)i;
	}while(i < 0 || i > 255);
	datos.estado = ((int)datos.desc[0])*datos.potencia;
	return datos;
}

void cargarlista(dat_t datos,lista_t** p,lista_t** u){
	lista_t* r;
	lista_t* aux = (lista_t*)malloc (sizeof (lista_t));
	aux->dato = datos;
	if ((*p)==NULL && (*u)==NULL){
		(*p)=(*u)=aux;
		aux->ant = NULL;
		aux->sig = NULL;
	}else{
		r = (*p);
		while(r && (r->dato.potencia > aux->dato.potencia)){
			r = r->sig;
		}
		if (!r){
			(*u)->sig = aux;
			aux->ant = (*u);
			aux->sig = NULL;
			(*u) = aux;
		}else if (r==(*p)){
			aux->sig = (*p);
			(*p)->ant = aux;
			aux->ant = NULL;
			(*p) = aux;
		}else{
			r = r->ant;
			aux->sig = r->sig;
			aux->ant = r;
			((lista_t*)(r->sig))->ant = aux;
			r->sig = aux;
		}
	}
}

void cargararchivo(lista_t* p){
	dat_t reg;
	lista_t* r;
	FILE*  fp = fopen (pot,"wb+");
	reg.desc[0] = '-'; 
	fwrite(&reg,sizeof(reg),1,fp);
	if (!fp){
		printf("Error en la creacion del archivo %s potencia.dat",pot);
		return;
	}
	r = p;
	while(r){
		fseek(fp,(-1L)*(long)sizeof(reg),SEEK_END);
		fread(&reg,sizeof(reg),1,fp);
		fseek(fp,0L,SEEK_END);
		fwrite(&(r->dato),sizeof(reg),1,fp);
		r = r->sig;
	}
	fclose(fp);
}

void mostrararchivo(){
	FILE* fp = fopen (pot,"rb");
	dat_t reg;
	if(!fp){
		printf("Error en la apertura del archivo %s potencia.dat ",pot);
	}
	printf ("*** Lista ord de mayor a menor (Potencias)*** \n\n");
		printf ("Potencia			Estado			Descripcion \n");
		printf ("-----------------------------------------------------------------------\n");
	fread(&reg,sizeof(reg),1,fp);
	while(!feof(fp)){
		if (reg.desc[0] != '-'){
			printf ("%04d				%06d		%-60s\n",reg.potencia,reg.estado,reg.desc);
		}
		fread(&reg,sizeof(reg),1,fp);
	}
}

void ejer(){
	dat_t datos;
	int salir;
	lista_t* p = NULL;
	lista_t* u = NULL;

	do{
		printf("1) Cargar datos: \n");
		printf("2) Ver archivo: \n");
		printf("3) Salir: \n");
		scanf("%d",&salir);
		switch(salir){
		case 1:
			datos = usuario();
			cargarlista(datos,&p,&u);
		break;
		case 2:
			cargararchivo(p);
			mostrararchivo();
		break;
		}
	}while(salir!=3);
}

