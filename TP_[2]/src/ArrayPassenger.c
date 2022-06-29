/*
 * ArrayPassenger.c
 *
 *  Created on: 12 may. 2022
 *      Author: Fran
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayPassenger.h"
#include "inputs.h"



int initPassengers(Passenger *list, int len) {
	int i = 0;

	for (; i < len; i++) {
		list[i].isEmpty = VACIO;
	}

	return 0;
}


int buscarEspacioLibre(Passenger* list,int len, int* pIndex)
{

    int todoOk = 0;
    if( list != NULL && pIndex != NULL)
    {
        *pIndex = -1;
        for(int i=0; i<len; i++)
        {
            if(list[i].isEmpty)
            {
                *pIndex = i;
                break;
            }
        }
        todoOk = 1;
    }
    return todoOk;
}

int addPassengers(Passenger* list, int len, int id, char name[], char lastName[], float price, int typePassenger, char flycode[],int statusFlight)
{
	int todoOk = 0;
	int indice;
	Passenger nuevoPasajero;


	    if( list != NULL && len > 0)
	    {
	        buscarEspacioLibre(list, len, &indice);

	        if(indice == -1)
	        {
	            printf("No hay lugar en el sistema\n");
	        }
	        else
	        {
	        	nuevoPasajero.id = id;
	            strcpy(nuevoPasajero.name, name);
	            strcpy(nuevoPasajero.lastName, lastName);
	            nuevoPasajero.price = price;
	            nuevoPasajero.typePassenger = typePassenger;
	            strcpy(nuevoPasajero.flycode, flycode);
	            nuevoPasajero.statusFlight = statusFlight;

	            nuevoPasajero.isEmpty = 0;

	            list[indice] = nuevoPasajero;

	            todoOk = 1;
	        }
	    }
	    return todoOk;
	}



int findPassengerById(Passenger* list, int len, int id)
{
    int retorno = -1;
    if( list != NULL && len > 0 )
    {
        for(int i=0; i < len; i++)
        {
            if( !list[i].isEmpty  && list[i].id == id)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}


int printPassenger(Passenger* list, int length)
{
	int i;
	int todoOk = -1;

		if(list!=NULL && length>=0)
		{
			for(i=0; i<length; i++ )
			{
				if(list[i].isEmpty == 0)
				{
					printf("\nID: %d \t NOMBRE: %s \t APELLIDO: %s \t PRECIO: %.2f \t CODIGO DE VUELO: %s \t TIPO DE PASAJERO: %d \t ESTADO DE VUELO: %d\n",list[i].id, list[i].name, list[i].lastName, list[i].price, list[i].flycode, list[i].typePassenger, list[i].statusFlight);
				}
			}
		todoOk=0;
		}
	return todoOk;
}

int modificarPasajero(Passenger* list, int len)
{
		int idAUsar;
		int indicePasajero;
		int opcion;
		int retorno = 0;

		printPassenger(list, len);
		printf("Ingresar el id del pasajero a modificar");
		fflush(stdin);
		scanf("%d", &idAUsar);

		indicePasajero = findPassengerById(list, len, idAUsar);

		while(indicePasajero == -1)
		{
			printf("Error, no se encontro el pasajero\n");
			printf("Ingresar el id del pasajero a modificar");
			fflush(stdin);
			scanf("%d", &idAUsar);

			indicePasajero = findPassengerById(list, len, idAUsar);

		}

		do
		{

			printf("1-Modificar nombre\n"
				"2-Modificar apellido\n"
				"3-Modificar precio\n"
				"4-Modificar tipo de pasajero\n"
				"5-Modificar codigo de vuelo\n"
				"6-Modificar estado de vuelo\n"
				"7-Salir\n");

				printf("Ingrese una opcion: ");
				scanf("%d", &opcion);

				switch(opcion)
				{
				case 1:
					printf("Ingrese el nuevo nombre:\n");
					fflush(stdin);
					scanf("%s", list[indicePasajero].name);
					retorno = 1;
					break;
				case 2:
					printf("Ingrese el nuevo apellido:\n");
					fflush(stdin);
					scanf("%s", list[indicePasajero].lastName);
					retorno = 1;
					break;
				case 3:
					printf("Ingrese el nuevo precio:\n");
					fflush(stdin);
					scanf("%f", &list[indicePasajero].price);
					retorno = 1;
					break;
				case 4:
					printf("Ingrese el nuevo tipo de pasajero:\n");
					fflush(stdin);
					scanf("%d", &list[indicePasajero].typePassenger);
					retorno = 1;
					break;
				case 5:
					printf("Ingrese el nuevo codigo de vuelo:\n");
					fflush(stdin);
					scanf("%s", list[indicePasajero].flycode);
					retorno = 1;
					break;
				case 6:
					printf("Ingrese el nuevo estado de vuelo:\n");
					fflush(stdin);
					scanf("%d", &list[indicePasajero].statusFlight);
					retorno = 1;
					break;
				case 7:
					printf("Modificacion finalizada\n");
					retorno = 1;
					break;
				}

		}while(opcion!=7);

		return retorno;
	}

int removePassenger(Passenger* list, int len, int id)
{
		int retorno = 0;

	    if( list != NULL && len > 0)
	    {
	        list[id].isEmpty = VACIO;

	         retorno = 1;
	    }
	    return retorno;
	}

int sortPassengersByLastName(Passenger* list, int len, int order)
{
		int todoOk = 0;
		Passenger auxPassenger;

		    if( list != NULL && len > 0)
		    {
		        for(int i=0; i < len - 1; i++)
		        {
		            for(int j= i+1; j < len; j++)
		            {
		                if( strcmp(list[i].lastName, list[j].lastName) > 0 )
		                {
		                    auxPassenger = list[i];
		                    list[i] = list[j];
		                    list[j] = auxPassenger;
		                }

		                if(strcmp(list[i].lastName, list[j].lastName)==0)
		                {
							if(list[i].typePassenger > list[j].typePassenger)
							{
									auxPassenger = list[i];
									list[i] = list[j];
									list[j] = auxPassenger;
							}
		                }
		            }
		        }
		        todoOk = 1;
		    }
		    return todoOk;

}

int promedioPrecios(Passenger* list, int len, float* precioTotal, float* promedio)
{
	int retorno = -1;
	int preciosIngresados = 0;
	float preciosAcumulados;

	if(list != NULL)
		{
			if(len > 0)
			{
				for(int i = 0; i < len; i++)
				{
					if(list[i].isEmpty == OCUPADO && list[i].price >= 0)
					{
						preciosIngresados++;
						preciosAcumulados+= list[i].price;
						retorno = 0;
					}
				}
			}
		}
		*promedio = preciosAcumulados / preciosIngresados;
		*precioTotal = preciosAcumulados;

		return retorno;
}

int encimaDelPromedio(Passenger* list, int len, float promedio)
{
	int retorno = -1;
	int contador = 0;

	if(list != NULL)
	{
		if(len > 0)
		{
			for(int i = 0; i < len; i++)
			{
				if(list[i].isEmpty == OCUPADO && list[i].price > promedio)
				{
					contador++;
					retorno = contador;
				}
			}
		}
	}

	return retorno;
}

int sortPassengersByCode(Passenger* list, int len, int order)
{
	int todoOk = 0;
	Passenger auxPassenger;

	if( list != NULL && len > 0)
	{
		for(int i=0; i < len - 1; i++)
		{
			for(int j= i+1; j < len; j++)
			{
				if( strcmp(list[i].flycode, list[j].flycode) > 0 )
				{
					auxPassenger = list[i];
					list[i] = list[j];
					list[j] = auxPassenger;
				}
				if(strcmp(list[i].flycode, list[j].flycode)==0)
				{
					if(list[i].statusFlight > list[j].statusFlight)
					{
						auxPassenger = list[j];
						list[j] = list[i];
						list[i] = auxPassenger;
					}
				}
			}
		}
			todoOk = 1;
	}
	return todoOk;

}
