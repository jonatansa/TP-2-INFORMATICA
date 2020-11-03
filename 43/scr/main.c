#include "cabecera.h"

int main(){
    int salir;
	do{
       	printf("\n\ **** CosmeFulanito - Partida sin fallas **** ");
		printf("\n------------------------\n");
		printf("1) Iniciar Correcion de datos\n");
		printf("2) salir\n");
		printf("\n---------------------------------------------\n");
        scanf("%d",&salir);
   			     struct pila_t *p;
  				 p=pila_t_ordenada(lista_ordenada_por_fecha());
	}while(salir!=2);
	return 0;
}



