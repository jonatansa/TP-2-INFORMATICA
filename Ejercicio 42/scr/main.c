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
			  vaciaMemoria();
   			  ParticaconFallas(cola_regitros_fallados());
              baja();	
	}while(salir!=2);
	return 0;
}



