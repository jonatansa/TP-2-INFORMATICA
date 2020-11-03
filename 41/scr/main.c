#include "cabecera.h"

int main(){
    int salir;
    puntero_t x;
    x.p=NULL;
    x.u=NULL;

	do{
		printf("\n\ **** MENU **** ");
		printf("\n------------------------\n");
		printf("1) Cargar datos: \n");
		printf("2) salir: \n");
		printf("\n------------------------\n");
       	scanf("%d",&salir);
      	x=carga(x);
      	imprimirLista(x);
        generarArchivo(x);	
	}while(salir!=2);
	//vaciaMemoria();
	return 0;
}



