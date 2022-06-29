/*
 ============================================================================
 Name        : TP_[2].c
 Author      : Reyes Francisco Nicol�s
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "submenu.h"
#include "ArrayPassenger.h"
#include "inputs.h"
#define LEN 2000
#define MAX	3

int main(void) {

	    setbuf(stdout, NULL);
		char salir = 'n';
		int idAux = 0;
		char nameAux[51];
		char lastNameAux[51];
		float priceAux = 0;
		char flycodeAux[10];
		int typePassengerAux = 0;
		int statusFlightAux = 0;
		int flagOpcion = 0;
		float precioTotal;
		float promedio;
		int pasajerosEncimaDelPromedio;
		int indice;
		int opcionIndice = 0;

		Passenger list[LEN];


	    initPassengers(list, LEN);

	do{
		switch(menuPrincipal())
		{
		case 1:

			idAux ++;

			utn_getName(nameAux, "\nIngrese el nombre: ", "Error. Ingrese correctamente el nombre.\n", 51);
			utn_getName(lastNameAux, "Ingrese el apellido: ", "Error. Ingrese correctamente el apellido.\n", 51);
			utn_getFloat(&priceAux, "Ingrese el precio: ", "Error, ingrese correctamente el precio.\n", 1, 999999);
			utn_getInt(&typePassengerAux, "Ingrese el tipo de pasajero (1-Primera clase, 2-Clase economica, 3-Clase turista): ", "Error, Ingrese correctamente el tipo de pasajero (1-Primera clase, 2-Clase economica, 3-Clase turista).\n", 1,3);
			pedirFlycode(flycodeAux, "Ingrese el codigo de vuelo:");
			utn_getInt(&statusFlightAux, "Ingrese el estado del vuelo (1-ACTIVO, 2-INACTIVO, 3-DEMORADO): ", "Error, Ingrese correctamente el estado de vuelo (1-ACTIVO, 2-INACTIVO, 3-DEMORADO).\n", 1,3);

			if(addPassengers(list, LEN, idAux, nameAux, lastNameAux, priceAux, typePassengerAux, flycodeAux, statusFlightAux))
			{
				printf("***Pasajero cargado con exito***\n");
				flagOpcion = 1;
			}
			else
			{
				printf("No se pudo cargar el pasajero\n");
			}
			break;
		case 2:
			if(flagOpcion == 1)
			{
				modificarPasajero(list, LEN);
			}
			else
			{
				printf("No se ingreso ningun pasajero\n");
			}
			break;
		case 3:
			if(flagOpcion==1)
			{
				printPassenger(list, LEN);
				printf("Ingrese el ID del pasajero que desea dar de baja: ");
				fflush(stdin);
				scanf("%d", &opcionIndice);
				indice = findPassengerById(list, LEN, opcionIndice);
				if(indice > -1)
				{
					if(removePassenger(list, LEN, indice)==1)
					{
						printf("\nSe ha dado de baja con exito al pasajero.\n");
					}
					else
					{
						printf("\nHubo un error al dar de baja al pasajero\n");
					}
				}
					else
					{
						printf("\nEl ID ingresado no coincide con ningún pasajero de la lista.\n\n");
					}
			}
			else
			{
				printf("No se ingreso ningun pasajero\n");
			}
			break;
		case 4:
			if(flagOpcion==1)
			{
				switch(submenuListar())
				{
				case 1:
					if(sortPassengersByLastName(list, LEN, 0))
					{
						printPassenger(list, LEN);
					}
					else
					{
						printf("\nHa ocurrido un error\n");
					}
					break;
				case 2:
					if(promedioPrecios(list, LEN, &precioTotal, &promedio)==0)
					{
						pasajerosEncimaDelPromedio = encimaDelPromedio(list, LEN, promedio);
						printf("\nEl total de los precios es $%.2f y cada pasajero pago en promedio $%.2f\n"
								"Hay %d pasajeros que pagaron por encima del promedio\n", precioTotal, promedio, pasajerosEncimaDelPromedio);
					}
					else
					{
						printf("\nHa ocurrido un error\n");
					}
					break;
				case 3:
					if(sortPassengersByCode(list, LEN, 0))
					{
						printPassenger(list, LEN);
					}
					else
					{
						printf("\nHa ocurrido un error\n");
					}
					break;
				case 4:
					printf("Volviendo al menu\n");
					break;
				}
			}
			else
			{
				printf("No se ingreso ningun pasajero\n");
			}
			break;
		case 5:
			idAux++;
			addPassengers(list,  LEN,  idAux, "Facundo", "Alvarez", 15357.23, 3, "AFH75", 1);
			idAux++;
			addPassengers(list,  LEN,  idAux,  "Jeremias", "Rodriguez", 45250.35, 1, "OTP99", 3);
			idAux++;
			addPassengers(list,  LEN,  idAux,  "Martin", "Herrera", 37500.50, 1, "RET32", 2);
			idAux++;
			addPassengers(list,  LEN,  idAux,  "Miguel", "Reyes", 13470.31, 2, "TYW21", 1);
			idAux++;
			addPassengers(list,  LEN,  idAux,  "Alfredo", "Martinez", 56323, 3, "LKM84", 1);
			idAux++;
			addPassengers(list,  LEN,  idAux,  "German", "Fernandez", 28549.31, 1, "RXC65", 3);
			flagOpcion = 1;
			printf("\nSe han cargado con exito todos los usuarios de la carga forzada.\n");
				break;
		case 6:
			printf("¿Desea salir? (s o n)");
			fflush(stdin);
			scanf("%c", &salir);

			while((salir!='s' && salir!='S') && (salir!='n' && salir!='N'))
			    {
			        printf("Error, letra invalida (responda s o n)\n");
			        fflush(stdin);
			        scanf("%c",&salir);
			    }

			break;
		}
	}while(salir != 's');

	return EXIT_SUCCESS;
}
