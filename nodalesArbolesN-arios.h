/*cuando uno se cambia de nodos existen 4 casos:
1-Cuando puedes irte a el hijo principal y cuando puedes irte a el hermano, en este caso se hace recursividad para ir a ambos
lados, pero antes se evalua lo que se desea realizar ya despues en caso de que no se cumpla lo que se desesa se 
debe crear otro nodo para que este en el nodo en el que nos encontramos asi uno va abajo y otro a la derecha.
2-cuando solo puedes irte a el hermano.
3-Cuando solo puedes irte a el hijo principal.
4-cuando el nodo es una hoja.
NOTA: Nunca perder el nodo referencia.
NOTA2: todo se baso en algoritmo de conteo.
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<windows.h>


typedef struct _Nodo{
   char dato[25];
   struct _Nodo *siguiente, *son;
}Nodo;   


Nodo *crearNodo(char *d)
{
	Nodo *nuevo;
	nuevo=(Nodo*)malloc(sizeof(Nodo));
	strcpy(nuevo->dato,d);
	nuevo->siguiente=NULL;
	nuevo->son=NULL;
	return nuevo;
}


void gotoxy(int x, int y)
{
HANDLE hCon;
hCon = GetStdHandle(STD_OUTPUT_HANDLE);
COORD Posicion;
Posicion.X = x;
Posicion.Y = y;
SetConsoleCursorPosition(hCon, Posicion);
}



int x=0, y=0, nodales=0;



Nodo *conteoR(Nodo *arbol, Nodo *lista) //La mejor funcion hecha porque no cae en ciclos infinitos.
{
	nodales++;
	//printf("%d",nodales);
	if(lista->siguiente!=NULL && lista->son!=NULL)
	{
		Nodo *aux=lista;
		lista=conteoR(arbol,lista->son);
		aux=conteoR(arbol,aux->siguiente);
		return arbol;
	}
	
	if(lista->siguiente!=NULL)
	{
		lista=conteoR(arbol,lista->siguiente);
		return arbol;
	}
		
	if(lista->son!=NULL)
	{
		lista=conteoR(arbol,lista->son);
		return arbol;
	}
	
	if(lista->son==NULL && lista->siguiente==NULL) 
		return arbol;	
}


Nodo *conteo(Nodo *arbol)
{	
	if(arbol==NULL)
		printf("\nPor el momento el arbol se encuentra vacio.");
	else
	{
		nodales=0;
		arbol=conteoR(arbol,arbol);
		//printf("\nLa cantidad de nodos que hay es: %d\n",nodales);
	}
		
	return arbol;
}



Nodo *listarUltimo(Nodo *primero, char *d) 
{
	Nodo *nuevo=crearNodo(d);
	Nodo *aux=primero;
	
	if(primero==NULL)
		return nuevo;
	else
	{
		while(aux->siguiente!=NULL)
			aux=aux->siguiente;
		aux->siguiente=nuevo;	
	}
	
	return primero;	
}


Nodo *insertarAR(Nodo *arbol, char *dato, char *dentro, Nodo *lista)
{		
	if(lista->siguiente!=NULL && lista->son!=NULL)
	{
		if( strcmp(lista->dato,dentro )==0 ) 
		{
			lista=listarUltimo(lista->son, dato);
			return arbol;		
		}
		nodales--;
			
		Nodo *aux=lista;
		lista=insertarAR(arbol,dato,dentro,lista->son);
		aux=insertarAR(arbol,dato,dentro,aux->siguiente);
		return arbol;
	}
	
	if(lista->siguiente!=NULL)
	{	
		if( strcmp(lista->dato,dentro )==0  )
		{
			Nodo *nuevo=crearNodo(dato);
			lista->son=nuevo;
			return arbol;
		}
		nodales--;
		
		lista=insertarAR(arbol,dato,dentro,lista->siguiente);
		return arbol;
	}
			
	if(lista->son!=NULL)
	{
		
		if( strcmp(lista->dato,dentro )==0 ) 
		{
			lista=listarUltimo(lista->son, dato);
			return arbol;		
		}
		nodales--;
				
		lista=insertarAR(arbol,dato,dentro,lista->son);
		return arbol;
	}	
	
	if(lista->siguiente==NULL && lista->son==NULL)
	{
	
		if( strcmp(lista->dato,dentro )==0  )
		{
			Nodo *nuevo=crearNodo(dato);
			lista->son=nuevo;
			return arbol;
		}
		nodales--;
	
		if(nodales==0)
		{
			printf("\nNo se encontro la carpeta donde deseas crear la carpeta.\n");
			return arbol;	
		}
	}	
}


Nodo *insertarA(Nodo *arbol, char *dato, char *dentro)
{   
    if(arbol==NULL)
	{
		Nodo *nuevo=crearNodo(dato);
		return nuevo;
	}  
	else
	{
		arbol=conteo(arbol);
		arbol=insertarAR(arbol,dato,dentro,arbol); 
		return arbol;	
	}
}



Nodo *desinsertarAR(Nodo *arbol, char *borrar,Nodo *lista) //si lograra fallar poner nodales donde se puso en insertarAR
{
	//printf("%d",nodales);
	nodales--;
	
	if(nodales==0)
	{
		printf("\nNo se encontro la carpeta que deseas eliminar.");
		return arbol;	
	}	
	
	if(lista->siguiente!=NULL && lista->son!=NULL)
	{
		if( strcmp(lista->son->dato,borrar )==0 && lista->son->siguiente!=NULL )
		{	
			Nodo *aux=lista;
			aux=lista->son;
			lista->son=lista->son->siguiente;
			free(aux);
			return arbol;
		}
		if( strcmp(lista->son->dato,borrar )==0 && lista->son->siguiente==NULL )
		{
			free(lista->son);
			lista->son=NULL;
			return arbol;
		}
		
		
		if( strcmp(lista->siguiente->dato,borrar)==0 && lista->siguiente->siguiente!=NULL)
		{
			Nodo *aux=lista;
			aux=lista->siguiente->siguiente;
			free(aux->siguiente);
			lista->siguiente=aux;
			return arbol;
		}	
		if( strcmp(lista->siguiente->dato,borrar)==0 && lista->siguiente->siguiente==NULL)
		{
			free(lista->siguiente);
			lista->siguiente=NULL;
			return arbol;
		}
		
		
		Nodo *aux=lista;
		lista=desinsertarAR(arbol,borrar,lista->son);
		aux=desinsertarAR(arbol,borrar,aux->siguiente);
		return arbol;
	}
	
	if(lista->siguiente!=NULL)
	{
		if( strcmp(lista->siguiente->dato,borrar)==0 && lista->siguiente->siguiente!=NULL)
		{
			Nodo *aux=lista;
			aux=lista->siguiente->siguiente;
			free(aux->siguiente);
			lista->siguiente=aux;
			return arbol;
		}	
		if( strcmp(lista->siguiente->dato,borrar)==0 && lista->siguiente->siguiente==NULL)
		{
			free(lista->siguiente);
			lista->siguiente=NULL;
			return arbol;
		}
		
		lista=desinsertarAR(arbol,borrar,lista->siguiente);
		return arbol;
	}
		
	if(lista->son!=NULL)
	{
		if( strcmp(lista->son->dato,borrar )==0 && lista->son->siguiente!=NULL )
		{	
			Nodo *aux=lista;
			aux=lista->son;
			lista->son=lista->son->siguiente;
			free(aux);
			return arbol;
		}
		if( strcmp(lista->son->dato,borrar )==0 && lista->son->siguiente==NULL )
		{
			free(lista->son);
			lista->son=NULL;
			return arbol;
		}
		
		lista=desinsertarAR(arbol,borrar,lista->son);
		return arbol;
	}	
}


Nodo *borrarA(Nodo *arbol,char *borrar) 
{
    if(strcmp(arbol->dato,borrar)==0 )
    {
    	free(arbol);
    	arbol=NULL;
	}	
    else
	{
		arbol=conteo(arbol);
		arbol=desinsertarAR(arbol,borrar,arbol);
	}		
    	
	return arbol; 
}



Nodo *verArbolR(Nodo *arbol, Nodo *lista) 
{	 
	gotoxy(x,y);	 
	printf("%s",lista->dato); 
	
	if(lista->siguiente!=NULL && lista->son!=NULL)
	{	
		Nodo *aux=lista;
		
		x++,y++;
		lista=verArbolR(arbol,lista->son);
		
		y++;
		aux=verArbolR(arbol,aux->siguiente);
		return arbol;
	}
	
	if(lista->siguiente!=NULL)
	{
		y++;
		
		lista=verArbolR(arbol,lista->siguiente); 
		return arbol;
	}
		
	if(lista->son!=NULL)
	{
		x++,y++;
		lista=verArbolR(arbol,lista->son);
		
		if(lista->siguiente==NULL)
			x--;
			
		return arbol;
	}
	
	if(lista->son==NULL && lista->siguiente==NULL)
	{
		x--; 
		return arbol;
	} 
}


Nodo *verA(Nodo *arbol)
{   
    if(arbol==NULL)
    {
    	printf("\n No hay ninguna carpeta que mostrar.");
    	return arbol;
	}		
	else
	{
		x++,y++;
		arbol=verArbolR(arbol,arbol);
		x=0,y=0;
		return arbol;	
	}
}

