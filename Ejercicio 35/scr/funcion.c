/*
	Name: Artal Jonatan
	Description: 
            HACER UN PROGRAMA QUE TOME LOS DATOS DE CONTACTO DE UNA PERSONA (Nombre, Apellido,
            Edad,Telefono, Mail) Y LOS CARGUE EN FORMA DIRECTA, EN UNA PILA DE MEMORIA DINAMICA.
			IMPRIMIR EN PANTALLA Y CARGAR EN UN ARCHIVO LLAMADO "Contactos.dat", DE ORGANIZACION
			SECUENCIAL, LOS REGISTROS INGRESADOS POR EL USUARIO SI LA PERSONA TIENE UNA EDAD MAYOR
			A 21 AÑOS.
*/


#include "cabecera.h"

void datos(){
	int salir;
	pila_t *aux;
	pila_t *pri=NULL;
	do{
		do{
			Lista(&aux,&pri);
			printf("Cargar mas personas?\n");
			printf("Salir(0): ");
			scanf("%d",&salir);
		}while(salir !=0);
		carglista(&aux,&pri);
		arch();
		printf("Desea seguir?\n");
		printf("Salir(0): ");
		scanf("%d",&salir);		
	}while (salir!=0);

}

lista_t CargarLista(){
	lista_t x;
	fflush(stdin);
	printf("Ingrese el nombre: ");
	scanf("%s",x.n);
	fflush(stdin);
	printf("Ingrese el apellido: ");
	scanf("%s",x.n);
	fflush(stdin);
	printf("Ingrese la edad: ");
	scanf("%d",&(x.e));
	fflush(stdin);
	printf("Ingrese el telefono: ");
	scanf("%ld",&(x.t));
	fflush(stdin);
	printf("Ingrese el mail: ");
	scanf("%s",x.m);
	fflush(stdin);
	return x;
}

void imprimirLista (lista_t x){
	printf("---------------------------------------------------------\n");
	printf ("Nombre: %s \n",x.n);
	printf ("Apellido: %s \n",x.a);
	printf("Edad: %d \n",x.e);
	printf("Telefono: %ld \n",x.t);
	printf("Mail: %s \n",x.m);
}

void Lista(pila_t** aux,pila_t** pri){
	lista_t x = CargarLista();
	(*aux) = (pila_t*) malloc (sizeof(pila_t));
	(*aux)->dato = x;
	if (!(*pri)){
		(*aux)->l = NULL;
		(*pri)= (*aux);
	}else{
		(*aux)->l = (*pri);
		(*pri) = (*aux);
	}
}

void cargarArchivo(lista_t x){
	int i = 0;
	FILE* fp = fopen (CONTACTOS,"rb+");
	if(!fp){
		fp = fopen (CONTACTOS,"wb+");
		if (!fp){
			printf("\n No se pudo crear el archivo %s contactos.dat\n",CONTACTOS);
			return;
		}
		i = 1;
	}

	if (i == 0){
		lista_t xc;
		fread(&xc,sizeof(xc),1,fp);
		while(!feof(fp)){
			if (!strcmp(xc.n,x.n) && !strcmp(xc.a,x.a)){
				return;
			}
			fread(&xc,sizeof(xc),1,fp);
		}
	}

	if(x.e > 21){
		fwrite(&x,sizeof(x),1,fp);
	}
	fclose(fp);
}


void carglista(pila_t** aux,pila_t** pri){
	while((*pri)){ 
		cargarArchivo((*pri)->dato);
		imprimirLista((*pri)->dato);
		(*aux)=(*pri);
		(*pri) = (*pri)->l;
		free((*aux));
	}
}

void arch(){
	FILE* fp;
	if((fp=fopen("CONTACTOS","rb"))==NULL)
	{
		printf("\n No se pudo crear el archivo %s contactos.dat\n",CONTACTOS);
		return;	
	};
	
	lista_t x;
	fread(&x,sizeof(x),1,fp);
	while(!feof(fp)){
		imprimirLista(x);
		fread(&x,sizeof(x),1,fp);
	}
	fclose(fp);
}







