/*
 ============================================================================
 Name        : main.c
 Author      : Reyes Francisco Nicol�s
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "inputs.h"
#include "Passenger.h"
#include "parser.h"

int main()
{
    int opcion;
    int opcionesOrdenar;
    int guardado = 1;
    int len;
    int flagDatosCargados = 0;
    int contadorPasajerosAgregados = 0;
    int contadorPasajerosAgregadosAntesGuardar = 0;
    int contadorPasajerosBorrados = 0;
    int contadorPasajerosBorradosDespuesDeGuardar = 0;
    int errorEdit;
    int errorRemover;
    int controlId = 0;
    int cantidadPasajerosLista = 0;
    int ultimoId;

    LinkedList* list = ll_newLinkedList();

    setbuf(stdout, NULL);

    do{
    	utn_getInt(&opcion,"\nMenu Principal:\n"
							"  1- Cargar los datos de los pasajeros desde el archivo data.csv (modo texto).\n"
							"  2- Cargar los datos de los pasajeros desde el archivo data.csv (modo binario).\n"
							"  3- Alta de pasajero.\n"
							"  4- Modificar datos de pasajero.\n"
							"  5- Baja de pasajero.\n"
							"  6- Listar pasajeros.\n"
							"  7- Ordenar pasajeros.\n"
							"  8- Guardar los datos de los pasajeros en el archivo data.csv (modo texto).\n"
							"  9- Guardar los datos de los pasajeros en el archivo data.csv (modo binario).\n"
							"  10- Salir.\n"
							"Elija una opcion: ", "\nError. Elija una opcion valida.\n",1,10);
    	len = ll_len(list);
        switch(opcion)
        {
            case 1:
            	if(flagDatosCargados == 0)
            	{
					if(controller_loadFromText("data.csv",list) == 0)
					{
						flagDatosCargados = 1;
						printf("\nLos datos han sido cargados exitosamente desde el modo texto.\n");
						if(contadorPasajerosAgregados != 0 && controlId == 0)
						{
							if(controller_controlarId("data.csv", list, contadorPasajerosAgregados, contadorPasajerosBorrados, &ultimoId) != -1)
							{
								printf("\nSe corrigieron los id de los pasajeros agregados anteriormente correctamente.\n");
								controlId = 1;
							}
							else
							{
								printf("\nNo se pudieron corregir los id de los pasajeros agregados anteriormente.\n");
							}
						}
						else
						{
							controller_controlarRepetidos(list, contadorPasajerosAgregadosAntesGuardar);
						}
					}
					else
					{
						printf("\nLos datos no se han podido cargar.\n");
					}
            	}
            	else
            	{
            		printf("\nYa cargo los datos.\n");
            	}
                break;
            case 2:
            	if(flagDatosCargados == 0)
            	{
					if(controller_loadFromBinary("data.bin",list) == 0)
					{
						flagDatosCargados = 1;
						printf("\nLos datos han sido cargados exitosamente desde el modo binario.\n");
						if(contadorPasajerosAgregados != 0 && controlId == 0)
						{
							if(controller_controlarId("data.csv", list, contadorPasajerosAgregados, contadorPasajerosBorrados, &ultimoId) != -1)
							{
								printf("\nSe corrigieron los id de los pasajeros agregados anteriormente correctamente.\n");
								controlId = 1;
							}
							else
							{
								printf("\nNo se pudieron corregir los id de los pasajeros agregados anteriormente.\n");
							}
						}
						else
						{
							controller_controlarRepetidos(list, contadorPasajerosAgregadosAntesGuardar);
						}
					}
					else
					{
						printf("\nLos datos no se han podido cargar.\n");
					}
            	}
            	else
            	{
            		printf("\nYa cargo los datos.\n");
            	}
            	break;
            case 3:
            	if(controller_addPassenger(list, contadorPasajerosBorrados, contadorPasajerosBorradosDespuesDeGuardar, cantidadPasajerosLista, controlId, ultimoId, flagDatosCargados) == 0)
            	{
            		printf("\nPasajero dado de alta con exito.\n");
					guardado = 0;
					contadorPasajerosAgregados++;
					if(flagDatosCargados != 1)
					{
						contadorPasajerosAgregadosAntesGuardar++;
					}
            	}
            	else
            	{
            		printf("\nNo se ha podido agregar al pasajero.\n");
            	}
            	printf("\nVolviendo al menu principal.\n");
				break;
            case 4:
            	if(len != 0)
            	{
            		errorEdit = controller_editPassenger(list);
            		switch(errorEdit)
            		{
            		case -1:
            			printf("\nError. Se encontro un error en la lista.\n");
            			break;
            		case -2:
            			printf("Error. El id ingresado no coincide con ninguno en la lista\n");
            			break;
            		case -3:
            			printf("Error. Hubo un error al intentar obtener los datos del pasajero.\n");
            			break;
            		default:
            			guardado = 0;
            		}
            	}
            	else
            	{
            		printf("\nTodavia no ingreso ningun pasajero.\n");
            	}
            	printf("\nVolviendo al menu principal.\n");
				break;
            case 5:
            	errorRemover = controller_removePassenger(list);
            	switch(errorRemover)
            	{
            	case 0:
					contadorPasajerosBorrados++;
					printf("\nSe ha dado de baja correctamente al pasajero de la lista.\n");
					if(controlId == 2)
					{
						contadorPasajerosBorradosDespuesDeGuardar++;
					}
					guardado = 0;
					break;
            	case -1:
            		printf("\nError. La lista se encuentra vacia.\n");
					break;
            	case -2:
            		printf("\nError. El id ingresado no coincide con ningun pasajero de la lista.\n");
            		break;
            	case -3:
            		printf("\nSe ha cancelado la bajada del pasajero de la lista.\n");
            		break;
            	}
            	printf("\nVolviendo al menu principal.\n");
				break;
            case 6:
            	if(controller_ListPassenger(list) != 0)
            	{
            		printf("\nError. La lista se encuentra vacia.\n");
					printf("\nVolviendo al menu principal.\n");
            	}
				break;
            case 7:
            	opcionesOrdenar = controller_sortPassenger(list);
            	switch(opcionesOrdenar)
            	{
            	case 1:
            		printf("\nSe ordenaron correctamente los pasajeros por id.\n");
            		break;
            	case 2:
            		printf("\nSe ordenaron correctamente los pasajeros por apellido.\n");
            		break;
            	case 3:
            		printf("\nSe ordenaron correctamente los pasajeros por tipo de pasajero.\n");
            		break;
            	case 4:
            		printf("\nSe ordenaron correctamente los pasajeros por codigo de vuelo.\n");
            		break;
            	default:
            		printf("\nError. No se pudo ordenar correctamente a los pasajeros.\n");
            	}
				break;
            case 8:
            case 9:
            	if(flagDatosCargados == 0 && controlId == 0)
            	{
            		cantidadPasajerosLista = controller_controlarId("data.csv", list, contadorPasajerosAgregados, contadorPasajerosBorrados, &ultimoId);
            		if(cantidadPasajerosLista != -1)
            		{
						controlId = 2;
            		}
            		else
            		{
            			printf("\nError.No se pudo corregir los id de los nuevos pasajeros ingresados al guardar.\n");
            		}
            	}
            	ll_sort(list, Passenger_sortById, 1);
            	if(controller_saveAsText("data.csv", list, flagDatosCargados) == 0)
            	{
            		if(controller_saveAsBinary("data.bin", list, flagDatosCargados) == 0)
            		{
						printf("\nSe guardaron con exito los datos de los pasajeros en el archivo data.csv.\n");
						guardado = 1;
            		}
            	}
            	else
            	{
					printf("\nError. No se pudo guardar los datos de los pasajeros en el archivo data.csv.\n");
            	}
				break;
            default:
            	if(guardado == 0)
            	{
            		printf("\nError. No puede cerrar el sistema sin guardar los datos antes\n");
            	}
            	else
            	{
            		printf("\nSaliendo.\n");
            	}
        }
    }while(opcion != 10 || guardado != 1);

    return 0;
}

