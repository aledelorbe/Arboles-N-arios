#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include "nodalesArbolesN-arios.h"


void main()
{
	system("color 4");	
	int  opc, opc2;
	char raiz[20], dir[25], dentro[25], borrar[25];
	Nodo *arbol = NULL;
	
	printf("\nCual es el nombre de tu carpeta raiz?:  ");
	gets(raiz);
	arbol = insertarA(arbol, raiz, " ");
	
	do{
		printf("\n1. Crear carpeta.");
		printf("\n2. Eliminar carpeta.");
		printf("\n3. Ver arbol.");
		printf("\n4. Salir.");
		
		printf("\n\nIngresa la opcion que deseas realizar: ");
		scanf("%d", &opc);
		
		system("cls");
		switch(opc)
		{
			case 1:
				fflush(stdin);	
				printf("\n\nIngresa el nombre de la carpeta que deseas crear: ");
				gets(dir);
					
				fflush(stdin);
				printf("\n\nDentro de que carpeta se creara?: ");
				gets(dentro);
				arbol = insertarA(arbol, dir, dentro);					
				break;
		
			case 2:
				fflush(stdin);	
				printf("\n\nIngresa el nombre de la carpeta que deseas borrar: ");
				gets(borrar);
				
				arbol = borrarA(arbol, borrar);
				break;
				
			case 3:
				arbol = verA(arbol);	
				printf("\n");
				break;
				
			case 4:
				free(arbol);
				printf("\nBye :(");
				return 0;
			case 5:
				arbol = conteo(arbol);
				break;	
				
			default:
				printf("\nNo existe esa opcion. Intenta de nuevo.\n");	
		}
	
	} while(opc != 4);
	
	
	getch();
}
