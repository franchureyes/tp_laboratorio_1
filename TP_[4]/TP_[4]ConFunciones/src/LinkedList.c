#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this;

    this = (LinkedList*) malloc(sizeof(LinkedList));
    if(this != NULL)
    {
		this->size = 0;
		this->pFirstNode = NULL;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int retorno = -1;

    if(this != NULL)
    {
    	retorno = this->size;
    }

    return retorno;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	Node* nodoAux = NULL;
	int len;

	if(this != NULL && nodeIndex >= 0)
	{
		len = ll_len(this);

		if(len >= 0 && nodeIndex < len)
		{
			for(int i = 0; i < len; i++)
			{
				if(i == 0)
				{
					nodoAux = this->pFirstNode;
				}
				else
				{
					nodoAux = nodoAux->pNextNode;
				}
				if(i == nodeIndex)
				{
					break;
				}
			}
		}
	}

    return nodoAux;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int retorno = -1;
    Node* nuevoNodo;
    int len;

    if(this != NULL)
    {
		len = ll_len(this);

		if(len >= 0)
		{
			if(nodeIndex > -1 && nodeIndex <= len)
			{
				nuevoNodo = (Node*) malloc (sizeof(Node));
				if(nuevoNodo != NULL)
				{
					if(len == 0 || nodeIndex == 0)
					{
						if(this->pFirstNode != NULL)
						{
							nuevoNodo->pNextNode = this->pFirstNode;
						}
						else
						{
							nuevoNodo->pNextNode = NULL;
						}

						this->size++;
						this->pFirstNode = nuevoNodo;
						nuevoNodo->pElement = pElement;
					}
					else
					{
						Node* indice;
						indice = getNode(this, nodeIndex - 1);

						if(indice != NULL)
						{
							this->size++;
							indice->pNextNode = nuevoNodo;
							nuevoNodo->pElement = pElement;
							nuevoNodo->pNextNode = NULL;
						}
					}
					retorno = 0;
				}

			}
		}
    }

    return retorno;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int retorno = -1;

    if(this != NULL)
    {
    	int len;

    	len = ll_len(this);

    	if(len >= 0)
    	{
			if(addNode(this, len, pElement) == 0)
			{
				retorno = 0;
			}
    	}
    }

    return retorno;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* retorno = NULL;

    if(this != NULL && index >= 0)
    {
    	Node* nodo;

    	nodo = getNode(this, index);

    	if(nodo != NULL)
    	{
    		retorno = nodo->pElement;
    	}
    }

    return retorno;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int retorno = -1;
    int len;

    len = ll_len(this);

    if(this != NULL && index >= 0 && index < len)
    {
    	Node* modificarNodo;

    	modificarNodo = getNode(this, index);

    	if(modificarNodo != NULL)
    	{
    		modificarNodo->pElement = pElement;
    		retorno = 0;
    	}
    }

    return retorno;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int retorno = -1;
    int len;

    len = ll_len(this);

    if(this != NULL && index >= 0 && index < len)
    {
    	Node* anteriorNodo;
    	Node* nodoActual;

		nodoActual = getNode(this, index);

		if(nodoActual != NULL)
		{
			if(index == 0)
			{
				this->pFirstNode = nodoActual->pNextNode;
			}
			else
			{
				anteriorNodo = getNode(this, index - 1);

				if(anteriorNodo != NULL)
				{
					anteriorNodo->pNextNode = nodoActual->pNextNode;
				}
			}

			retorno = 0;
			this->size--;
			free(nodoActual);
		}
	}

    return retorno;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int retorno = -1;
    int len;

    if(this != NULL)
    {
    	len = ll_len(this);

    	for(int i = len; i > 0; i--)
    	{
    		ll_remove(this, i);
    	}
    	this->size--;
    	retorno = 0;
    }

    return retorno;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int retorno = -1;

    if(this != NULL)
    {
    	ll_clear(this);
    	free(this);
    	retorno = 0;
    }
    return retorno;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int retorno = -1;

    if(this != NULL)
    {
    	Node* nodo;
    	int contador = 0;

    	nodo = this->pFirstNode;

    	while(nodo != NULL)
    	{
			if(nodo->pElement == pElement)
			{
				retorno = contador;
				break;
			}
			else
			{
				nodo = nodo->pNextNode;
				contador++;
			}
    	}
    }
    return retorno;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int retorno = -1;

    if(this != NULL)
    {
    	if(this->size == 0)
    	{
    		retorno = 1;
    	}
    	else
    	{
    		retorno = 0;
    	}
    }

    return retorno;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int retorno = -1;
    int len;

    len = ll_len(this);

    if(this != NULL && index >= 0 && index <= len)
    {
    	Node* nodoAnterior;
    	Node* nodoAgregar;
    	Node* nodoPosterior;

    	nodoAgregar = (Node*) malloc (sizeof(Node));
    	nodoPosterior = getNode(this, index);

    	if(nodoAgregar != NULL)
    	{
			if(index == 0)
			{
				this->pFirstNode = nodoAgregar;
			}
			else
			{
				nodoAnterior = getNode(this, index - 1);
				if(nodoAnterior != NULL)
				{
					nodoAnterior->pNextNode = nodoAgregar;
				}
			}

			nodoAgregar->pNextNode = nodoPosterior;
			nodoAgregar->pElement = pElement;
			this->size++;
			retorno = 0;
    	}
    }

    return retorno;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* retorno = NULL;
    int len;

    len = ll_len(this);

    if(this != NULL && index >= 0 && index <= len)
    {
    	Node* nodoPop;
    	Node* nodoAnterior;

    	nodoPop = getNode(this, index);

    	if(nodoPop != NULL)
    	{
			if(index == 0)
			{
				this->pFirstNode = nodoPop->pNextNode;
			}
			else
			{
				nodoAnterior = getNode(this, index - 1);
				if(nodoAnterior != NULL)
				{
					nodoAnterior->pNextNode = nodoPop->pNextNode;
				}
			}

			this->size--;
			retorno = nodoPop->pElement;
    	}
    }
    return retorno;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int retorno = -1;

   	if(this != NULL)
   	{
   		retorno = 0;

   		if(ll_indexOf(this, pElement) != -1)
   		{
   			retorno = 1;
   		}
   	}

    return retorno;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int retorno = -1;

    if(this != NULL && this2 != NULL)
    {
    	int len;

		retorno = 1;
    	len = ll_len(this2);

		for(int i = 0; i < len; i++)
		{
			if(ll_contains(this, ll_get(this2, i)) != 1)
			{
				retorno = 0;
				break;
			}
		}
    }
    return retorno;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    cloneArray = ll_newLinkedList();
    int len;
    void* pElement;

    len = ll_len(this);

    if(this != NULL && from >= 0 && from < to && to <= len)
    {
    	for(int i = from; i < to; i++)
    	{
    		if(cloneArray != NULL)
    		{
    			pElement = ll_get(this,i);
				ll_add(cloneArray,pElement);
    		}
    	}
    }

    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;

    if(this != NULL)
    {
    	cloneArray = ll_subList(this, 0, ll_len(this));
    }

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int retorno =-1;

    if(this != NULL)
    {
    	if(pFunc != NULL && (order == 0 || order == 1))
    	{
			int len;
			void* primerElemento;
			void* segundoElemento;
			int respuesta;

			len = ll_len(this);

			for(int i = 0; i < len - 1; i++)
			{
				for(int j = i + 1; j < len; j++)
				{
					primerElemento = ll_get(this, i);
					segundoElemento = ll_get(this, j);

					respuesta = pFunc(primerElemento,segundoElemento);

					if(order == 1)
					{
						if(respuesta > 0)
						{
							ll_set(this, i, segundoElemento);
							ll_set(this, j, primerElemento);
						}
					}
					else
					{
						if(respuesta < 0)
						{
							ll_set(this, i, segundoElemento);
							ll_set(this, j, primerElemento);
						}
					}

					retorno = 0;
				}
			}
    	}
    }

    return retorno;

}

/**
 * @brief * Completa un campo del elemento, recibiendo como parámetro
 * 			la función que sera la encargada de calcular el valor de ese campo.
 * 			Verificando que tanto el puntero this como el puntero a la funcion
 * 			pFunc sean distintos de NULL.
 *
 * @param this LinkedList* Puntero a la lista
 * @param pFunc (*pFunc) Puntero a la funcion encargada de calcular el nuevo valor
 * @return Retorna la lista completa.
 */
void ll_map(LinkedList* this, void (*pFunc)(void*))
{
	if(this != NULL)
	{
		if(pFunc != NULL)
		{
			int len;
			len = ll_len(this);

			for(int i = 0; i < len; i++)
			{
				pFunc(ll_get(this, i));
			}
		}
	}
}

/**
 * @brief * Filtra la lista con una condición, recibiendo como parámetro
 * 			la función que sera la encargada de decidir si cada elemento
 * 			cumple la condición (1) o no (0) y si se agrega a una nueva lista filtrada.
 * 			Verificando que tanto el puntero this como el puntero a la funcion
 * 			pFunc sean distintos de NULL.
 *
 * @param this LinkedList* Puntero a la lista
 * @param pFunc (*pFunc) Puntero a la funcion criterio
 * @return Retorna la lista nueva lista filtrada.
 */
LinkedList* ll_filter(LinkedList* this, int(*pFunc)(void*))
{
	LinkedList* listaFiltrada = NULL;

	if(this != NULL)
	{
		if(pFunc != NULL)
		{
			int len;
			void* pElement;

			len = ll_len(this);
			listaFiltrada = ll_newLinkedList();

			if(listaFiltrada != NULL)
			{
				for(int i = 0; i < len; i++)
				{
					pElement = ll_get(this, i);

					if(pFunc(pElement) == 0)
					{
						ll_add(listaFiltrada, pElement);
					}
				}
			}
		}
	}

	return listaFiltrada;
}
