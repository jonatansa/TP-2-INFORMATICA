
#include "cabecera.h"


int main(){
	int salir;
	do{
		printf("\n**** MENU ****\n\n");
		printf("------------------------\n");
		printf("1) Iniciar:\n");
		printf("2) salir: \n");
		scanf("%d",&salir);
		switch (salir){
			case 1:
				datos();
			break;
		}
	}while(salir!=2);


	return 0;
}
