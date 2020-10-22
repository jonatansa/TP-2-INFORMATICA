/*
	Name: Artal Jonatan
	Description: Hacer un programa que lea el archivo "contactos.dat" creado en el ejercicio 35 y crear una lista, en memoria 
	dinamica, ordernarla alfabeticamene. Una vez creada la lista guardarla en un archivo de organizacion directa llamodo
	"contactos_ordenados.dat" imprimiendola en pantalla
*/


#include "cabecera2.h"


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
