/* Autor: Xavier Romero Hernández, Realizado: 21/05/2022 
	Utilizando Archivos Binarios
	Programa que almacena los Equipos de un centro de computo con sus datos y un resguardo al que se le es asignado
	El programa tendra las siguientes opciones:
		0. Salir
		1. Agregar Equipo
		2. Lista de todos los Equipos
		3. Lista de todas las PCs
		4. Lista de todas las Laptops
		5. Buscar el Equipo asignado a un administrativo
		6. Reasignar Equipo
		7. Guardar datos
		8. Cargar datos
	*/
	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "milibreria.h"
#define MAX 50


int menu();
void agregar(struct equipo x[]);
void imprimir(struct equipo x[],int tipo, char *a);
void guardar(struct equipo x[]);
void cargar(struct equipo x[]);
void buscarequipo(struct equipo x[]);
void ordenarNombre(struct equipo x[]);
void encabezado();
void contenido(struct equipo x[], int i);
void reasignar(struct equipo x[]);
void borrarredun(struct equipo x[]);

struct equipo{
	char tipo[10], modelo[25], nombre[25], edificio[2], area[10];
	int numeroserie;
};

int n=0;

int main(){
	struct equipo computo[MAX];
	int opcion, centi=0;
	do{
		opcion=menu();
		system("cls");
		switch(opcion) {
			case 0: printf("Adios.....\n");
					break;
			case 1: agregar(computo);
					centi=1;
					ordenarNombre(computo);
					system("cls");
					break;
			case 2:	if(centi==1){
						imprimir(computo,0,"Equipos");
					}
					else{
						printf("Primero debes agregar Equipos.\n");
					}
					system("PAUSE");
					system("cls");
					break;
			case 3: if(centi==1){
						imprimir(computo,1,"PCs");
					}
					else{
						printf("Primero debes agregar Equipos.\n");
					}
					system("PAUSE");
					system("cls");
					break;
			case 4: if(centi==1){
						imprimir(computo,2,"Laptops");
					}
					else{
						printf("Primero debes agregar Equipos.\n");
					}
					system("PAUSE");
					system("cls");
					break;
			case 5: if(centi==1){
						buscarequipo(computo);
					}
					else{
						printf("Primero debes agregar Equipos.\n");
					}
					system("PAUSE");
					system("cls");
					break;
			case 6: if(centi==1){
						reasignar(computo);
						ordenarNombre(computo);
					}
					else{
						printf("Primero debes agregar Equipos.\n");
					}
					system("PAUSE");
					system("cls");
					break;
			case 7: if(centi==1){
						guardar(computo);
					}
					else{
						printf("No se han agregado o modificado los registros\n");
					}
					system("PAUSE");
					system("cls");
					break;
			case 8: cargar(computo);
					centi=1;
					ordenarNombre(computo);
					system("PAUSE");
					system("cls");
					break;							
			default:printf("Opcion no valida, ingresa otra opcion\n\n");
					break;		
		}
	}while(opcion!=0);
	
	return 0;
}

//funciones
//Funcion que muestra el menu, pide una opcion, la valida y la regresa
int menu(){
	int opcion;
	printf("-----------------Menu Principal-----------------\n");
	printf("0. Salir\n");
	printf("1. Agregar Equipo\n");
	printf("2. Lista de todos los Equipos\n");
	printf("3. Lista de todas las PCs\n");
	printf("4. Lista de todas las Laptops\n");
	printf("5. Buscar el Equipo asignado a un administrativo\n");
	printf("6. Reasignar Equipo\n");
	printf("7. Guardar datos\n");
	printf("8. Cargar datos\n");
	printf("------------------------------------------------\n");
	printf("Selecciona una opcion: ");
	scanf("%d",&opcion);
	return opcion;
}

//guardar daros del arreglo de estructuras en un archivo binario
void guardar(struct equipo x[]){
	FILE *f;
	f=fopen("equipos.dat","w");
	if(f==NULL){
		printf("Error al intentar guardar los datos!!!\n");
	}
	else{
		for(int i=0;i<n;i++){
			fwrite(&x[i],sizeof(x[i]),1,f);
		}
		fclose(f);
		printf("--> Se guardaron %d registros\n",n);
	}
}

//leer el archivo binario y cargarlo al arreglo de estructuras
void cargar(struct equipo x[]){
	FILE *f;
	f=fopen("equipos.dat","r");
	n=0;
	if(f==NULL){
		printf("Error al intentar guardar los datos!!!\n");
	}
	else{
		printf("Leyendo.......\n");
		while(fread(&x[n],sizeof(x[n]),1,f)==1){
			n++;
		}
		fclose(f);
		printf("--> %d registros leidos\n",n);
	}
}

void agregar(struct equipo x[]){
	int pregunta,tipo;
	while(n<MAX){
		x[n].numeroserie=leerd("Numero de Serie: ",1,999999);
		tipo=leerd("Tipo de Equipo (1.-Laptop o 2.-PC): ",1,2);
		if(tipo==1) strcpy(x[n].tipo,"Laptop");
		else strcpy(x[n].tipo,"PC");
		leers("Modelo: ",x[n].modelo,25);
		leers("Resguardo o Administrativo a asignar Equipo: ",x[n].nombre,25);
		leers("Edificio: ",x[n].edificio,2);
		leers("Area: ",x[n].area,10);
		printf("Equipo Guardado\n");
		n++;
		if(n<MAX){
			pregunta=leerd("Agregar otro Equipo? (1-Si, 0-No) ",0,1);
			system("cls");
			if(pregunta==0){
				break;
			}
		}
	}
	if(n==MAX){
		printf("Arreglo lleno!!\n");
		system("PAUSE");
	}
}

void imprimir(struct equipo x[], int tipo, char *a){
	printf("------------------------------------------------------Lista de %s-------------------------------------------------\n",a);
	encabezado();
	for(int i=0;i<n;i++){
		switch(tipo){
			case 0: contenido(x,i);
					break;
			case 1: if(strcmp(x[i].tipo,"PC") == 0){
						contenido(x,i);
					}
					break;
			case 2: if(strcmp(x[i].tipo,"Laptop") == 0){
						contenido(x,i);
					}
					break;
		}
	}
}

void buscarequipo(struct equipo x[]){
	char buscar[25];
	int centiserie=0;
	leers("Ingresa el nombre del administrativo a buscar: ",buscar,25);
	for(int i=0;i<n;i++){
		if(strcmp(x[i].nombre,buscar)==0){
			if(centiserie==0){
				encabezado();
				centiserie=1;
			}
			contenido(x,i);
			}
		}
	if(centiserie==0){
		printf("El administrativo no tiene asignado ningun equipo\n");
	}
}

void reasignar(struct equipo x[]){
	int buscar;
	char buscarnombre[25];
	struct equipo aux;
	int centiserie=0, centinombre=0, centinela=0, confirmar=0, posicioneq;
	buscar=leerd("Numero de Serie del equipo a reasignar: ",1,999999);
	do{
		if(centiserie==0){
			for(int i=0;i<n;i++){
				if(x[i].numeroserie==buscar){
					encabezado();
					contenido(x,i);
					centiserie=1;
					posicioneq=i;
				}
			}
			if(centiserie==0){
				printf("No se encontrado el Equipo\n");
				centinela=leerd("Desea buscar otra vez? (1-Si, 0-No) ",0,1);
			}
		}
		if(centiserie!=0){
			leers("Ingresa el nombre del administrativo a reasignar Equipo: ",buscarnombre,25);
			for(int i=0;i<n;i++){
				if(strcmp(x[i].nombre,buscarnombre)==0){
					centinombre=1;
					printf("\nSe asignara el Equipo con Numero de serie: %d a %-25s, Confirmar?",x[posicioneq].numeroserie,x[i].nombre);
					confirmar=leerd(" (1-Si, 0-No) ",0,1);
					if(confirmar==1){
						x[n]=x[posicioneq];
						x[posicioneq]=aux;
						strcpy(x[posicioneq].nombre,x[n].nombre);
						strcpy(x[n].nombre,x[i].nombre);
						n++;
						printf("Equipo Reasignado\n");
						borrarredun(x);
						centinela=0;
						break;
					}
					else{
						centinela=leerd("Desea buscar otro administrativo? (1-Si, 0-No) ",0,1);
					}
				}
			}
			if(centinombre==0){
				printf("No se encontrado el administrativo\n");
				centinela=leerd("Desea buscar otro administrativo? (1-Si, 0-No) ",0,1);
			}
		}
	}while(centinela==1);
}

void encabezado(){
	printf("\nNo.\tResguardo\t\t\tEdificio\tArea\t\tNo.Serie\tTipo\t   Modelo\n");
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
}

void contenido(struct equipo x[], int i){
	printf("%2d\t%-25s\t%-5s\t\t%-10s\t%-6d\t\t%-6s\t   %-25s\n",i+1,x[i].nombre,x[i].edificio,x[i].area,x[i].numeroserie,x[i].tipo,x[i].modelo);
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
}

void ordenarNombre(struct equipo x[]){
	//ordenamiento del arreglo por el metodo de la burbuja
	//usando el codigo de https://es.wikipedia.org/wiki/Ordenamiento_de_burbuja#:~:text=El%20ordenamiento%20de%20burbuja%20(Bubble,est%C3%A1n%20en%20el%20orden%20equivocado.	
	for(int z = 1; z < n; ++z) {
		struct equipo aux;
      	for(int v = 0; v < (n - z); v++) {
      	//edades[v] > edades[v+1]
         if(strcmp(x[v].nombre,x[v+1].nombre)>0){
            aux = x[v];
            x[v] = x[v + 1];
            x[v + 1] = aux;
         	}
      	}
    }
    //imprimir(x,0,"Equipos");
}

void borrarredun(struct equipo x[]){
	int z;
	do{
      	for(int v = z+1; v < n; v++) {
         	if(strcmp(x[z].nombre,x[v].nombre)==0){
            	if(x[z].numeroserie==0 && x[v].numeroserie!=0){
            		for(int h=z;h<=n;h++){
            			x[h]=x[h+1];
					}
					n--;
					z=-1;
				}
        	}
    	}
    	z++;
    }while(z<n);
}
