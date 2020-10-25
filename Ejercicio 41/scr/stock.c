#include "cabecera.h"

respuestos_t ingresarinfo(){
	respuestos_t respuesto;
	printf("Ingrese el partNumber: ");
	scanf("%ld",&(respuesto.partNumber));
	fflush(stdin);
	printf("Ingrese el serialNumber: ");
	scanf("%ld",respuesto.serialNumber);
	fflush(stdin);
	printf("Ingrese el descripcion: ");
	scanf("%s",respuesto.descripcion);
	fflush(stdin);
	printf("Ingrese el ubicacion: ");
	scanf("%s",respuesto.ubicacion);
	fflush(stdin);
	return respuesto;
}

void imprimirStock(respuestos_t respuesto){
	printf("---------------------------------------------------------\n");
	printf ("Nº de Parte	Nª de Serie		Descripcion 	Ubicacion\n");
	printf ("%%ld           %-%ld            %-40s          %-100s\n",respuesto.partNumber,respuesto.serialNumber,respuesto.descripcion,respuesto.ubicacion);
}

void cargarStock(pila_t** auxiliar,pila_t** primero){
	respuestos_t respuesto = ingresarinfo();
	(*auxiliar) = (pila_t*) malloc (sizeof(pila_t));
	(*auxiliar)->dato = respuesto;
	if (!(*primero)){
		(*auxiliar)->lazo = NULL;
		(*primero)= (*auxiliar);
	}else{
		(*auxiliar)->lazo = (*primero);
		(*primero) = (*auxiliar);
	}
}

void cargarStockArchivo(respuestos_t respuesto){
	int fpclear = 0;
	FILE* fp = fopen (STOCK,"rb+");
	if(!fp){
		fp = fopen (STOCK,"wb+");
		if (!fp){
			printf("No se puede crear %s .... \n",STOCK);
			return;
		}
		fpclear = 1;
	}
	if (fpclear == 0){
		respuestos_t stockCargado;
		fread(&stockCargado,sizeof(stockCargado),1,fp);
		while(!feof(fp)){
			if (!strcmp(stockCargado.ubicacion,respuesto.ubicacion) && !strcmp(stockCargado.descripcion,respuesto.descripcion)){
				return;
			}
			fread(&stockCargado,sizeof(stockCargado),1,fp);
		}
	}
	fwrite(&respuesto,sizeof(respuesto),1,fp);
	fclose(fp);
}

void imprimirStocks(pila_t** auxiliar,pila_t** primero){
	while((*primero)){
		cargarStockArchivo((*primero)->dato);
		imprimirStock((*primero)->dato);
		(*auxiliar)=(*primero);
		(*primero) = (*primero)->lazo;
		free((*auxiliar));
	}
}

void verArchivo(){
	FILE* fp = fopen (STOCK,"rb");
	if(!fp){
		printf("No se puede abrir %s .... \n",STOCK);
	}
	respuestos_t respuesto;
	fread(&respuesto,sizeof(respuesto),1,fp);
	while(!feof(fp)){
		imprimirStock(respuesto);
		fread(&respuesto,sizeof(respuesto),1,fp);
	}
	fclose(fp);
}

void SolicitarDatos(){
	int salir;
	pila_t *auxiliar;
	pila_t *primero=NULL;
	do{
		cargarStock(&auxiliar,&primero);
		printf("\nDesea seguir cargando produtos...?\n");
	    printf("0) Si... : \n");
	    printf("1) No... : \n");
		scanf("%d",&salir);
	}while (salir!=1);
	
}




