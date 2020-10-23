#include "cabecera.h"

void datos(){
	c_t* pri=NULL;
	c_t* u=NULL;
	int i;

	do{
		printf("1) Mostrar valores \n");
		printf("0) Salir \n");
		scanf("%d",&i);
		switch(i){
		case 1:
			printf("Valores Positivos senoidal: \n");
			generarCola(&pri,&u,0,127);
			mostrarValores(&pri);
			printf("Valores Negativos senoidal: \n");
			pri=u=NULL;
			generarCola(&pri,&u,-127,0);
			mostrarValores(&pri);
		break;
		}
	}while(i!=0);
}

void aColar (unsigned char dato,c_t** pri,c_t** u){
	c_t* aux = (c_t*)malloc (sizeof (c_t));
	aux->dato = dato;

	if ((*pri)==NULL && (*u)==NULL){
		(*pri)=(*u)=aux;
		aux->ant = NULL;
		aux->sig = NULL;
	}else{
		(*u)->sig = aux;
		aux->ant = (*u);
		aux->sig = NULL;
		(*u) = aux;
	}
}

void generarCola(c_t** pri,c_t** u,int d,int h){
	int m = d;
	unsigned char valorACargar;
	while (m <= h){
		valorACargar=0;
		if (m < 0){
			valorACargar = m*(-1);
			valorACargar = valorACargar | (1 << 7);
		}else{
			valorACargar = m;
		}
		m++;
		aColar(valorACargar,pri,u);
	}

}

void mostrarValores(c_t** pri){
	c_t* aux;
	int saltoLinea = 0;
	while((*pri)){
		aux = (*pri);
		(*pri) = (*pri)->sig;
		if(saltoLinea == 20){
			printf("\n");
			saltoLinea=0;
		}
		printf("0x%X-",aux->dato);
		saltoLinea++;
		free(aux);
	}
	printf("\n");
}


