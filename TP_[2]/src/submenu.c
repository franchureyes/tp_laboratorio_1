/*
 * submenu.c
 *
 *  Created on: 26 jun. 2022
 *      Author: Fran
 */

#include <stdio.h>
#include <stdlib.h>


int submenuListar()
{
	int opcion = 1;

		printf("1-Listado de los pasajeros ordenados alfabéticamente por Apellido y Tipo de pasajero\n"
				"2-Total y promedio de los precios de los pasajes, y cuántos pasajeros superan el precio promedio\n"
				"3-Listado de los pasajeros por Código de vuelo y estados de vuelos ‘ACTIVO’\n"
				"4-Salir\n");

		printf("Ingrese una opcion: ");
		scanf("%d", &opcion);

		while(opcion<1 || opcion>4)
		{
			printf("Error, ingrese una opcion valida: \n");
			scanf("%d", &opcion);
		}

	return opcion;
}
