#include "cabecera2.h"

dat_t buscar(int id){
	FILE* fp = fopen(pot,"rb+");
	dat_t reg;
	reg.desc[0] = '-';
	if (!fp){
		printf("Error en la apertura del archivo %s potencia.dat \n",pot);
		reg.desc[0] = '*';
		return reg;
	}
	fseek(fp,(long)(id)*sizeof(reg),SEEK_SET);
	fread(&reg,sizeof(reg),1,fp);
	fclose(fp);
	return reg;
}

void inversa(char* palabra){
    long id;
	char aux;
	int i;
	int n= strlen(palabra);
	int j = n-1;
	for(i=0;i<n/2;i++){
		aux = *(palabra+j);
		*(palabra+j) = *(palabra+i);
		*(palabra+i) = aux;
		j--;
	}
}

void actualizar(dat_t reg,int id){
	FILE* fp = fopen (pot,"rb+");
	if (!fp){
		printf("Error en la apertura del archivo %s potencia.dat \n",pot);
	}
	fseek (fp,(id+1)*(long)sizeof(reg),SEEK_SET);
	fseek(fp,(-1L)*(long)sizeof(reg),SEEK_CUR);
	fwrite(&reg,sizeof(reg),1,fp);
	fclose(fp);
}

void apilar (dat_t reg,pila_t** p){
	pila_t* aux = (pila_t*) malloc (sizeof(pila_t));
	aux->dato = reg;
	if (!(*p)){
		aux->l = NULL;
		(*p)= aux;
	}else{
		aux->l = (*p);
		(*p) = aux;
	}
}

void agregarchivo(dat_t reg){
	FILE* fp = fopen (sal,"rb+");
	if(!fp){
		fp = fopen (sal,"wb+");
		if (!fp){
			printf("Error en la creacion del archivo %s \n",sal);
			return;
		}
	}
	dat_t leido;

	fread(&leido,sizeof(leido),1,fp);
	while(!feof(fp)){
		if (!strcmp(leido.desc,reg.desc)){
			return;
		}
		fread(&leido,sizeof(leido),1,fp);
	}
	fwrite(&reg,sizeof(reg),1,fp);
	fclose(fp);
}

void cargarpila(dat_t reg,pila_t** p){
	if ((reg.estado & (1 << 0)) && (reg.estado  & (1 << 2))){
		apilar(reg,p);
	}else{
		agregarchivo(reg);
	}
}

void operareg(dat_t* reg,int id,pila_t** p){
	char palabra[60];
	int i = 0;
	while(reg->desc[i] != ' ' && i<strlen(reg->desc)){
		primerapal[i] = reg->desc[i];
		i++;
	}
	palabra[i+1]='\0';
	inversa(palabra);
	strcat (palabra," ");
	strcat (palabra,(reg->desc)+i+1);
	strcpy(reg->desc,palabra);
	toggleBit(reg->estado,3);
	actualizar(*reg,id);
    cargarpila(*reg,p);

}

void imprimir(dat_t reg)
{
	printf ("%04d				%06d		%-60s\n",reg.potencia,reg.estado,reg.desc);
}

void atender(pila_t** p){
	pila_t* r= *p;
	printf ("*** Listado ------ (Potencias)*** \n\n");
		printf ("Potencia			Estado			Descripcion \n");
		printf ("-------------------------------------------------------------\n");
	while(r){
		imprimir(r->dato);
		r = r->l;
	}
}

void mostrarchivo(){
	FILE* fp = fopen (sal,"rb");
	if(!fp){
		printf("Error apertura archivo %s, puede que no exista \n",sal);
	}
	dat_t reg;
	printf ("***LISTADO DE POTENCIAS***\n\n");
	printf ("POTENCIA			ESTADO			DESCRIPCION\n");
	printf ("----------------------------------------------------------------------\n");
	fread(&reg,sizeof(reg),1,fp);
	while(!feof(fp)){
		printf ("%04d				%06d		%-60s\n",reg.potencia,reg.estado,reg.desc);
		fread(&reg,sizeof(reg),1,fp);
	}
	fclose(fp);
}

void ejerc(){
	int i;
	int id;
	dat_t reg;
	pila_t* p=NULL;

	do{
		printf("1) Buscar clave (id): \n");
		printf("2) Atender pila de potencia: \n");
		printf("3) Listar archivo de salida: \n");
		printf("4) Salir: \n");
		scanf("%d",&i);
		switch(i){
		case 1:
			do{
				do{
				printf("Ingrese la clave (id): \n");
				scanf("%d",&id);
				}while (id <= 0);
				reg = buscar(id);
				if (reg.desc[0]=='-'){
					printf("Registro no encontrado... \n");
				}else if (reg.desc[0]=='*'){
					return;
				}
			}while(reg.desc[0]=='-');

		operareg(&reg,id,&p);
		break;
		case 2:
			atender(&p);
		break;
		case 3:
			mostrarchivo();
		break;
		}
	}while(i!=4);
}
