#include "cabecera.h"

void datos(){
	int i;
	long id;
	p_t* pila;
	p_t* pri=NULL;
	do{
		printf("1) Cargar datos: \n");
		printf("2) Apilar: \n");
		printf("3) Ver datos: \n");
		printf("4) Ver Descripcion: \n");
		printf("0) Salir \n");
		scanf("%d",&i);
		switch(i){
			case 1:
				cargar();
			break;
			case 2:
				printf("Ingrese el id a apilar: \n");
				scanf("%ld",&id);
				pila = apilar(id,&pri);
			break;
			case 3:
				listar();
			break;
			case 4:
				descripcion(&pila);
			break;
		}
	}while(i!=0);
}

void cargar(){
	FILE* fp = fopen (DATOS,"rb+");
	if(!fp){
		fp = fopen (DATOS,"wb+");
		if(!fp){
			printf("Error en la (apertura y creacion) del archivo %s datos.dat",DATOS);
			return;
		}
	}
	d_t dato;

	printf("Ingrese id del registro: \n");
	scanf("%ld",&(dato.id));

	d_t reg;
	fread(&reg,sizeof(reg),1,fp);
	while(!feof(fp)){
		if (reg.id == dato.id){
			if (reg.b == 'B'){
				printf("El registro existe pero se encuentra dado de baja....\n");
			}else if (reg.b == 'A'){
				printf("El registro ya existe..... \n");
			}
			return;
		}
		fread(&reg,sizeof(reg),1,fp);
	}
	printf("Ingrese la descripcion: \n");
	fflush(stdin);
	gets(dato.d);
	fflush(stdin);
	int tipo;
	do{
		printf("Ingrese tipo de dato: \n");
		scanf("%d",&tipo);
	}while(tipo > 255 || tipo < 0);
	dato.tipo = (unsigned char)(tipo);
	dato.b = 'A';
	fwrite (&dato,sizeof(dato),1,fp);
	fclose(fp);
}

void imprimir(d_t dato){
	printf ("%08ld		0x%-4X			%-30s\n",dato.id,dato.tipo,dato.d);
}

void listar(){
	FILE* fp = fopen (DATOS,"rb");
	d_t reg;
	if(!fp){
		printf("Error en la apertura del archivo %s datos.dat ",DATOS);
		return;
	}
	printf ("*** Listado de Datos ***\n\n");
	printf ("Id			Tipo			Descripcion\n");
	printf ("------------------------------------------\n");
	fread(&reg,sizeof(reg),1,fp);
	while(!feof(fp)){
			if (reg.b == 'A'){
				imprimir(reg);
			}
		fread(&reg,sizeof(reg),1,fp);
	}
	fclose(fp);
}

void descripcion(p_t** pri){
	printf ("*** Listado de Datos ***\n\n");
	printf ("Id			Tipo			Descripcion\n");
	printf ("------------------------------------------\n");
	p_t* aux = NULL;
	d_t dato;
	while((*pri)){
		dato= buscar((*pri)->dato.id,&((*pri)->dato.pos));
		imprimir (dato);
		aux=(*pri);
		(*pri) = (*pri)->l;
		free(aux);
	}
}

d_t buscar(long id,int* pos){
	FILE* fp = fopen (DATOS,"rb");
	d_t reg;
	(*pos) = 1;
	if(!fp){
		printf("Error en la apertura del archivo datos.dat %s",DATOS);
		reg.b = 'E';
		return reg;
	}

	fread(&reg,sizeof(reg),1,fp);
	while(!feof(fp)){
			if (id == reg.id && reg.b == 'A'){
				return reg;
			}
		fread(&reg,sizeof(reg),1,fp);
		(*pos)++;
	}
	reg.b = 'N';
	return reg;
	fclose(fp);
}

p_t* apilar (long id,p_t** pri){
	p_t* aux=NULL;
	n_t nodo;
	d_t dato = buscar(id,&(nodo.pos));
	nodo.id = dato.id;

	if ((dato.tipo & (1 << 3)) && dato.b == 'A'){
		aux = (p_t*) malloc (sizeof(p_t));
		aux->dato = nodo;
		if (!(*pri)){
			aux->l = NULL;
			(*pri)= aux;
		}else{
			aux->l = (*pri);
			(*pri) = aux;
		}
	}else{
		printf("Registro no encotnrado.... \n");
	}
	return (*pri);
}






