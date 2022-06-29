#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Passenger.h"

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromText(FILE* pFile , LinkedList* pArrayListPassenger)
{
	int retorno = -1;

	if(pFile != NULL)
	{
		if(pArrayListPassenger != NULL)
		{
			Passenger* pasajeroNuevo;
			char idStr[TAMDATOS];
			char nombre[TAMNOMBRES];
			char apellido[TAMNOMBRES];
			char precio[TAMDATOS];
			char estado[TAMDATOS];
			char tipo[TAMDATOS];
			char codigo[TAMDATOS];

			fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", idStr, nombre, apellido, precio, codigo, tipo, estado);
			while(1)
			{
				if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", idStr, nombre, apellido, precio, codigo, tipo, estado) == 7)
				{
					if(strcmp(tipo,"FirstClass") == 0)
					{
						strcpy(tipo, "1");
					}
					else
					{
						if(strcmp(tipo,"ExecutiveClass") == 0)
						{
							strcpy(tipo, "2");
						}
						else
						{
							strcpy(tipo, "3");
						}
					}

					pasajeroNuevo = Passenger_newParametros(idStr, nombre, tipo, apellido, precio, codigo, estado);

					if(pasajeroNuevo != NULL)
					{
						ll_add(pArrayListPassenger, pasajeroNuevo);
						retorno = 0;
					}
				}

				if(feof(pFile) != 0)
				{
					break;
				}
			}
		}
	}

    return retorno;
}

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.bin (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromBinary(FILE* pFile , LinkedList* pArrayListPassenger)
{
	int retorno = -1;

	if(pFile != NULL)
	{
		if(pArrayListPassenger != NULL)
		{
			while(1)
			{
				Passenger* pasajeroAux = Passenger_new();
				if(pasajeroAux != NULL)
				{
					if(fread(pasajeroAux, sizeof(Passenger), 1, pFile) != 0)
					{
						ll_add(pArrayListPassenger, pasajeroAux);

					}

					retorno = 0;
				}
				if(feof(pFile) != 0)
				{
					break;
				}
			}
		}
	}

    return retorno;
}
