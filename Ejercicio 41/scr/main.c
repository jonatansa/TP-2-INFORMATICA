#include "cabecera.h"

int main(){
	int salir;
	do{
		printf("*** CosmeFulanito ***\n");
		printf("---------------------\n");
		printf("1) CARGAR LISTA \n");
		printf("2) IMPRIMIR LISTA \n");
		printf("3) SALIR \n");
		printf("---------------------\n");
		printf("Opcion elejida: ");
		scanf("%d",&salir);
		switch (salir){
			case 1:
				SolicitarDatos();
			break;
			case 2:
				generarListadeProdutos();
			break;
			case 5:
				imprimirStocks();
				verArchivo();
				break;
		}
	}while(salir!=3);
	return 0;
}
