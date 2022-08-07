/*
	Cuando uno se cambia de nodos existen 4 casos:
		1-Cuando puedes irte a el hijo principal y cuando puedes irte a el hermano, en este caso se hace recursividad para ir a ambos
		lados, pero antes se evalua lo que se desea realizar ya despues en caso de que no se cumpla lo que se desesa se 
		debe crear otro nodo para que este en el nodo en el que nos encontramos asi uno va abajo y otro a la derecha.
		2-cuando solo puedes irte a el hermano.
		3-Cuando solo puedes irte a el hijo principal.
		4-cuando el nodo es una hoja.
	NOTA: Nunca perder el nodo referencia.
	NOTA2: todo se baso en algoritmo de conteo.
	Bitacora 1: 
		No se han encontrado errores hasta el momento.
		Se utiliza mucha logica de listas.
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<windows.h>

// Definicion de la estructura nodo utilizada en el ejercicio, este tiene dos apuntadores: sig el cual apunta a un nodo siguiente y son el 
// cual apunta a un nodo hijo que pueda tener.
typedef struct _Nodo{
   char dato[25];
   struct _Nodo *sig, *son;
}Nodo;   

// Funcion la cual se encarga de crear e inicializar a un nodo nuevo.
Nodo *crearNodo(char *d)
{
	Nodo *nuevo;
	nuevo = (Nodo*)malloc(sizeof(Nodo));
	strcpy(nuevo->dato, d);
	nuevo->sig = NULL;
	nuevo->son = NULL;
	return nuevo;
}

// Funcion para desplazarnos por la pantalla del cmd.
void gotoxy(int x, int y)
{
HANDLE hCon;
hCon = GetStdHandle(STD_OUTPUT_HANDLE);
COORD Posicion;
Posicion.X = x;
Posicion.Y = y;
SetConsoleCursorPosition(hCon, Posicion);
}



int x = 0, y = 0, nodales = 0;

// Funcion para contar la cantidad de nodos que hay en el arbol.
// La mejor funcion hecha porque no cae en ciclos infinitos. Primero se diseño esta funcion y con base a esta,
// se realizaron todas las demas. ****
Nodo *conteoR(Nodo *arbol, Nodo *lista) 
{
	nodales++;
	//printf("%d",nodales);
	
	// Si el nodo en el que nos encontremos tiene un hijo y tiene al menos un hermano entonces...
	if(lista->sig != NULL && lista->son != NULL)
	{
		// Vuelve a mandar a llamar esta funcion pero para el hijo y el hermano de este nodo.
		Nodo *aux = lista;
		lista = conteoR(arbol, lista->son);
		aux = conteoR(arbol, aux->sig);
		return arbol;
	}
	
	// Si el nodo en el que nos encontremos tiene almenos un hermano entonces...
	if(lista->sig != NULL)
	{
		// Vuelve a mandar a llamar esta funcion pero para el hermano de este nodo.
		lista = conteoR(arbol, lista->sig);
		return arbol;
	}
	
	// Si el nodo en el que nos encontremos tiene un hijo entonces...	
	if(lista->son != NULL)
	{
		// Vuelve a mandar a llamar esta funcion pero para el hijo de este nodo.
		lista = conteoR(arbol, lista->son);
		return arbol;
	}
	
	// Si el nodo en el que nos encontremos no tiene un hijo y no tiene al menos un hermano entonces...
	if(lista->son == NULL && lista->sig == NULL) 
		// Significa que estamos en un nodo hoja y que debemos de parar de contar.
		return arbol;	
}


// Funcion que decide si se manda a llamar una funcion que cuenta la cantidad de nodos que hay en el arbol.
// La pura evaluacion se hace aparte del conteo de nodos porque la funcion de conteo de nodos es recursiva.
Nodo *conteo(Nodo *arbol)
{	
	// Si el arbol apunta a null, significa que aun no hay ningun nodo en el arbol. 
	if(arbol == NULL)
		printf("\nPor el momento el arbol se encuentra vacio.");
	else
	{
		// En caso contrario entonces se le asigna el 0 a la variable que cuanta la cantidad de nodos que hay y
		// se manda a llamar la funcion que en verdad cuenta el total de nodos que hay en el arbol.
		nodales = 0;
		arbol = conteoR(arbol, arbol);
		//printf("\nLa cantidad de nodos que hay es: %d\n", nodales);
	}
		
	return arbol;
}


// Funcion que se encarga de colocar un nodo al final de una serie de nodos que estan listados/formados.
Nodo *listarUltimo(Nodo *primero, char *d) 
{
	Nodo *nuevo = crearNodo(d);
	Nodo *aux = primero;
	
	if(primero == NULL)
		return nuevo;
	else
	{
		while(aux->sig != NULL)
			aux=aux->sig;
		aux->sig = nuevo;	
	}
	
	return primero;	
}


// Funcion que se encarga de insertar un nuevo nodo hijo o hermano en el arbol segun sea el caso.
Nodo *insertarAR(Nodo *arbol, char *dato, char *dentro, Nodo *lista) // lista es dentro de cual nodo se metera el nuevo nodo.
{		
	// Si el nodo lista tiene al menos un hermano y tiene un hijo entonces...
	if(lista->sig != NULL && lista->son != NULL)
	{
		// Quizas sea este nodo a quien se le debe meter (hacerlo su hijo) el nuevo nodo, para ello preguntar si el contenido del
		// nodo es igual al solicitado. 
		if( strcmp(lista->dato, dentro ) == 0 ) 
		{
			// De ser el caso, entonces al hijo del nodo lista asiganarle el nuevo nodo y retornar la referencia de la raiz (arbol) para no 
			// perder la referencia.
			lista = listarUltimo(lista->son, dato);
			return arbol;		
		}
		nodales--;
			
		// Si este nodo no es el buscado, volver a mandar a llamar esta funcion pero ahora evaluando al nodo hijo y hermano del nodo
		// actual.
		Nodo *aux = lista;
		lista = insertarAR(arbol, dato, dentro, lista->son);
		aux = insertarAR(arbol, dato, dentro, aux->sig);
		return arbol;
	}
	
	// Si el nodo lista tiene al menos un hermano entonces...
	if(lista->sig != NULL)
	{	
		// Quizas sea este nodo a quien se le debe meter (hacerlo su hijo) el nuevo nodo, para ello preguntar si el contenido del
		// nodo es igual al solicitado. 
		if( strcmp(lista->dato, dentro ) == 0  )
		{
			// De ser el caso, entonces al hijo del nodo lista asiganarle el nuevo nodo y retornar la referencia de la raiz (arbol) para no 
			// perder la referencia.
			Nodo *nuevo = crearNodo(dato);
			lista->son = nuevo;
			return arbol;
		}
		nodales--;
		
		// Si este nodo no es el buscado, volver a mandar a llamar esta funcion pero ahora evaluando al nodo hermano del nodo
		// actual.
		lista = insertarAR(arbol, dato, dentro, lista->sig);
		return arbol;
	}
	
	// Si el nodo lista tiene al menos un hijo entonces...		
	if(lista->son != NULL)
	{
		// Quizas sea este nodo a quien se le debe meter (hacerlo su hijo) el nuevo nodo, para ello preguntar si el contenido del
		// nodo es igual al solicitado.
		if( strcmp(lista->dato, dentro ) == 0 ) 
		{
			// De ser el caso, entonces al nodo lista asiganarle como hijo pero al final de todos los hermanos (al 
			// final de la lista) el nuevo nodo y retornar la referencia de la raiz (arbol) para no perder la referencia.
			lista = listarUltimo(lista->son, dato);
			return arbol;		
		}
		nodales--;
			
		// Si este nodo no es el buscado, volver a mandar a llamar esta funcion pero ahora evaluando al nodo hijo del nodo
		// actual.	
		lista = insertarAR(arbol, dato, dentro, lista->son);
		return arbol;
	}	
	
	// Si el nodo lista no tiene al menos un hijo y no tiene hermanos entonces...
	if(lista->sig == NULL && lista->son == NULL)
	{
		// Quizas sea este nodo a quien se le debe meter (hacerlo su hijo) el nuevo nodo, para ello preguntar si el contenido del
		// nodo es igual al solicitado.
		if( strcmp(lista->dato, dentro ) == 0  )
		{
			// De ser el caso, entonces al hijo del nodo lista asiganarle el nuevo nodo y retornar la referencia de la raiz (arbol) para no 
			// perder la referencia.
			Nodo *nuevo = crearNodo(dato);
			lista->son = nuevo;
			return arbol;
		}
		nodales--;
	
		// Si ya se evaluaron todos los nodos que conforman al arbol entonces ...
		if(nodales == 0)
		{
			printf("\nNo se encontro la carpeta donde deseas crear la carpeta.\n");
			return arbol;	
		}
	}	
}


Nodo *insertarA(Nodo *arbol, char *dato, char *dentro)
{   
	// Si aun no hay ningun nodo en el arbol, entonces directamente crea el nodo solicitado.
    if(arbol == NULL)
	{
		Nodo *nuevo = crearNodo(dato);
		return nuevo;
	}  
	else
	{
		// De lo contrario contar la cantidad de nodos que hay en el arbol y buscar sobre cual nodo 
		// se debe insertar (como hijo) el nuevo nodo.
		arbol = conteo(arbol);
		arbol = insertarAR(arbol, dato, dentro, arbol); 
		return arbol;	
	}
}


// Funcion que se encarga de recorrer todo el arbol y buscar el nombre de la carpeta que se desea eliminar.
Nodo *desinsertarAR(Nodo *arbol, char *borrar, Nodo *lista) //si lograra fallar poner nodales donde se puso en insertarAR
{
	//printf("%d", nodales);
	nodales--;
	
	// Si ya se recorrieron todos los nodos que hay en el arbol entonces avisarle al usuario y terminar la ejecucion de esta
	// fucnion.
	if(nodales == 0)
	{
		printf("\nNo se encontro la carpeta que deseas eliminar.");
		return arbol;	
	}	
	
	// Si el nodo lista tiene al menos un hermano y tiene un hijo entonces...
	if(lista->sig != NULL && lista->son != NULL)
	{
		// CASOS ELIMINAR HIJO.
		// Si el nodo hijo del nodo en el que nos encontremos es el solicitado y dicho nodo hijo tiene al menos un hermano entonces...
		if( strcmp(lista->son->dato, borrar ) == 0 && lista->son->sig != NULL )
		{	
			// El nodo en el que nos encontremos se le asigna el primer hermano de su nodo hijo y a nodo hijo se elimina.
			Nodo *aux = lista;
			aux = lista->son;
			lista->son = lista->son->sig;
			free(aux);
			return arbol;
		}
		// Si el nodo hijo del nodo en el que nos encontremos es el solicitado y dicho nodo hijo NO tiene al menos un hermano entonces...
		if( strcmp(lista->son->dato, borrar ) == 0 && lista->son->sig == NULL )
		{
			// El nodo hijo se elimina y remarcamos que no hay ningun hijo del nodo actual.
			free(lista->son);
			lista->son = NULL;
			return arbol;
		}
		
		// CASOS ELIMINAR HERMANO.
		// Si el nodo de inmediatamente alado del nodo actual es el solicitado y dos lugares a la derecha sigue habiendo otro hermano entonces...
		// Estos dos if siguiente probablemente no sean necesarios ya que no se entrarian a estos ifs, si no a los siguietenes dos.
		if( strcmp(lista->sig->dato, borrar) == 0 && lista->sig->sig != NULL)
		{
			// Al nodo actual asignale como hermano el nodo de dos lugares a la derecha y elimina el de inmediatamamente alado.
			Nodo *aux = lista;
			aux = lista->sig->sig;
			free(aux->sig);
			lista->sig = aux;
			return arbol;
		}	
			// Si el nodo de inmediatamente alado del nodo actual es el solicitado y dos lugares a la derecha no hay otro hermano entonces...
		if( strcmp(lista->sig->dato, borrar) == 0 && lista->sig->sig == NULL)
		{
			// El nodo de la derecha eliminalo y has que el nodo actual a su derecha apunte a la nada.
			free(lista->sig);
			lista->sig = NULL;
			return arbol;
		}
		
		// Se vuelve a mandar a llamar esta funcion pero ahora evaluando al nodo hijo y al nodo hermano.
		Nodo *aux = lista;
		lista = desinsertarAR(arbol, borrar, lista->son);
		aux = desinsertarAR(arbol, borrar, aux->sig);
		return arbol;
	}
	
	// CASOS ELIMINAR HERMANO.
	// Si el nodo actual tiene al menos un hermano entonces ...
	if(lista->sig != NULL)
	{
		// Si el nodo de inmediatamente alado es el solicitado y hay otro hermano dos lugares a la derecha entonces...
		if( strcmp(lista->sig->dato, borrar) == 0 && lista->sig->sig != NULL)
		{	
			// Elimina el nodo siguiente y asignale como hermano al nodo actual, el nodo de dos lugares a la derecha.
			Nodo *aux = lista, *aux2 = aux->sig->sig;
			free(aux->sig);
			aux->sig = aux2;
			return arbol;
		}	
		// Si el nodo de inmediatamente alado es el solicitado y NO hay otro hermano dos lugares a la derecha entonces...
		if( strcmp(lista->sig->dato, borrar) == 0 && lista->sig->sig == NULL)
		{
			// El nodo de la derecha eliminalo y has que el nodo actual a su derecha apunte a la nada.
			free(lista->sig);
			lista->sig = NULL;
			return arbol;
		}
		
		// Se vuelve a mandar a llamar esta funcion pero ahora evaluando al nodo hermano.
		lista = desinsertarAR(arbol, borrar, lista->sig);
		return arbol;
	}
		
	// CASOS ELIMINAR HIJO.
	// Si el nodo actual tiene un hijo entonces ...
	if(lista->son != NULL)
	{
		// Si el nodo hijo del nodo actual es el solicitado y el nodo hijo tiene un hermano entonces...
		if( strcmp(lista->son->dato, borrar ) == 0 && lista->son->sig != NULL )
		{	
			// Hacer que el nodo hijo del nodo actual sea el hermano del nodo hijo actual.
			Nodo *aux = lista;
			aux = lista->son;
			lista->son = lista->son->sig;
			free(aux);
			return arbol;
		}
		
		// Si el nodo hijo del nodo actual es el solicitado y el nodo hijo NO tiene un hermano entonces...
		if( strcmp(lista->son->dato, borrar ) == 0 && lista->son->sig == NULL )
		{
			// Elimina el nodo hijo y has que el nodo actual en su hijo apunta a nada.
			free(lista->son);
			lista->son = NULL;
			return arbol;
		}
		
		// Se vuelve a mandar a llamar esta funcion pero ahora evaluando al nodo hijo.
		lista = desinsertarAR(arbol, borrar, lista->son);
		return arbol;
	}	
}


// Funcion para determinar si se debe recorrer o no todo el arbol para eliminar la carpeta solicitada.
Nodo *borrarA(Nodo *arbol, char *borrar) 
{
	// Si la carpeta que se desea borrar es la carpeta raiz entonces...
    if( strcmp(arbol->dato, borrar) == 0 )
    {
    	free(arbol);
    	arbol = NULL;
	}	
    else
	{
		// En caso contrario entonces hay que contar cuantos nodos hay en el arbol y mandar a llamar la funcion que
		// se encarga de recorrer todo el arbol y buscar la carpeta solicitada.
		arbol = conteo(arbol);
		arbol = desinsertarAR(arbol, borrar, arbol);
	}		
    	
	return arbol; 
}


// Funcion que se encarga de ir recorriendo todo el arbol e ir mostrando el contenido de cada nodo.
Nodo *verArbolR(Nodo *arbol, Nodo *lista) 
{	 
	gotoxy(x, y);	 
	printf("%s", lista->dato); 
	
	// Si el nodo actual tiene un hermano y un hijo entonces...
	if(lista->sig != NULL && lista->son != NULL)
	{	
		// Vuelve a mandar esta funcion pero ahora evaluando al nodo hijo y al nodo hermano.
		Nodo *aux = lista;
		
		x++, y++;
		lista = verArbolR(arbol, lista->son);
		
		y++;
		aux = verArbolR(arbol, aux->sig);
		return arbol;
	}
	
	// Si el nodo actual tiene un hermano entonces...
	if(lista->sig != NULL)
	{
		// Vuelve a mandar esta funcion pero ahora evaluando al nodo hermano.
		y++;
		
		lista = verArbolR(arbol, lista->sig); 
		return arbol;
	}
		
	// Si el nodo actual tiene un hijo entonces...
	if(lista->son != NULL)
	{
		// Vuelve a mandar esta funcion pero ahora evaluando al nodo hijo.
		x++, y++;
		lista = verArbolR(arbol, lista->son);
		
		// Si el nodo actual no tiene hermanos, entonces...
		if(lista->sig == NULL)
			x--;
			
		return arbol;
	}
	
	// Si el nodo actual no tiene un hermano y no tiene un hijo entonces...
	if(lista->son == NULL && lista->sig == NULL)
	{
		// Significa que estamos en un nodo hoja.
		x--; 
		return arbol;
	} 
}


// Funcion que evalua si se mandara a llamar la funcion: "verArbolR" o no.
Nodo *verA(Nodo *arbol)
{   
	// Si el nodo raiz (arbol) apunta a nada, significa que aun no hay un nodo en el arbol.
    if(arbol == NULL)
    {
    	printf("\n No hay ninguna carpeta que mostrar.");
    	return arbol;
	}		
	else
	{
		// En caso contrario se manda a llamar la funcion verArbolR.
		x++, y++;
		arbol = verArbolR(arbol, arbol);
		x = 0, y = 0;
		return arbol;	
	}
}

