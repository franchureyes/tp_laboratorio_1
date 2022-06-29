#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "inputs.h"
#include "Passenger.h"
#include "parser.h"

int main()
{
    int option;
    int guardado = 1;
    int len;
    int cargarDatos = 0;
    int contadorPasajerosAgregados = 0;
    int contadorPasajerosAgregadosAntesGuardar = 0;
    int contadorPasajerosBorrados = 0;
    int contadorPasajerosBorradosDespuesDeGuardar = 0;
    int errorEdit;
    int errorRemover;
    int opcionesSort;
    int controlId = 0;
    int cantidadPasajerosLista = 0;
    int ultimoId;
    int criterioFiltrado;
    int listaAGuardar;
    int listaACargar;
    int listaACargarFiltrada;
    int listaAMostrar;
    int listaAOrdenar;

    LinkedList* listaPasajeros = ll_newLinkedList();
    LinkedList* subLista = ll_newLinkedList();
    LinkedList* backup = ll_newLinkedList();
    LinkedList* listaFiltrada = ll_newLinkedList();

    setbuf(stdout, NULL);

    do{
    	utn_getInt(&option, "********************************************************************************\n"
    						"Menu Principal:\n"
							"  1- Cargar los datos de los pasajeros desde el archivo data.csv (modo texto).\n"
							"  2- Cargar los datos de los pasajeros desde el archivo data.csv (modo binario).\n"
							"  3- Alta de pasajero.\n"
							"  4- Modificar datos de pasajero.\n"
							"  5- Baja de pasajero.\n"
							"  6- Listar pasajeros.\n"
							"  7- Ordenar pasajeros.\n"
							"  8- Guardar los datos de los pasajeros en el archivo data.csv (modo texto).\n"
							"  9- Guardar los datos de los pasajeros en el archivo data.csv (modo binario).\n"
							"  10- Vaciar toda la lista.\n"
							"  11- Crear una sublista.\n"
							"  12- Crear un backup.\n"
							"  13- Generar una lista filtrada por Tipo de Pasajero.\n"
							"  14- Aplicar aumento o descuento en el precio del vuelo.\n"
							"  15- Salir.\n"
    						"*********************************************************************************\n"
							"Elija una opción: ", "\nError. Elija una opción valida.\n",1,15);
    	len = ll_len(listaPasajeros);
        switch(option)
        {
            case 1:
            	utn_getInt(&listaACargar, "Opciones de lista para cargar:\n"
            			"  1- Lista Principal.\n"
            			"  2- Sub Lista Generada.\n"
            			"  3- Lista Filtrada.\n"
            			"  4- Backup.\n"
            			"Ingrese la lista a cargar: ", "Error. Ingrese una opción valida.\n", 1, 4);
            	switch(listaACargar)
            	{
            	case 1:
					if(cargarDatos == 0)
					{
						if(controller_loadFromText("data.csv",listaPasajeros) == 0)
						{
							cargarDatos = 1;
							printf("\nLos datos han sido cargados exitosamente desde el modo texto.\n");
							if(contadorPasajerosAgregados != 0 && controlId == 0)
							{
								if(controller_controlarId("data.csv", listaPasajeros, contadorPasajerosAgregados, contadorPasajerosBorrados, &ultimoId) != -1)
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
								controller_controlarRepetidos(listaPasajeros, contadorPasajerosAgregadosAntesGuardar);
							}
						}
						else
						{
							printf("\nLos datos no se han podido cargar.\n");
						}
					}
					else
					{
						printf("\nYa cargó los datos.\n");
					}
            		break;
            	case 2:
            		if(controller_loadFromText("sublista.csv",subLista) == 0)
					{
            			printf("\nLos datos han sido cargados exitosamente desde la Sub Lista.\n");
					}
            		else
            		{
            			printf("\nLos datos no se han podido cargar.\n");
            		}
            		break;
            	case 3:
            		utn_getInt(&listaACargarFiltrada, "\nOpciones de cargar listas filtradas:\n"
        					"  1- FirstClass.\n"
        					"  2- ExecutiveClass.\n"
        					"  3- EconomyClass.\n"
        					"Que lista filtrada desea cargar? ", "Error. Ingrese una opción valida.\n", 1, 3);
            		switch(listaACargarFiltrada)
            		{
            		case 1:
						if(controller_loadFromText("FirstClass.csv",listaFiltrada) == 0)
						{
							printf("\nLos datos han sido cargados exitosamente desde la lista filtrada por First Class.\n");
						}
						else
						{
							printf("\nLos datos no se han podido cargar.\n");
						}
            			break;
            		case 2:
                		if(controller_loadFromText("ExecutiveClass.csv",listaFiltrada) == 0)
    					{
                			printf("\nLos datos han sido cargados exitosamente desde la lista filtrada por Executive Class.\n");
    					}
                		else
                		{
                			printf("\nLos datos no se han podido cargar.\n");
                		}
            			break;
            		case 3:
                		if(controller_loadFromText("EconomyClass.csv",listaFiltrada) == 0)
    					{
                			printf("\nLos datos han sido cargados exitosamente desde la lista filtrada por Economy Class.\n");
    					}
                		else
                		{
                			printf("\nLos datos no se han podido cargar.\n");
                		}
            			break;
            		}
            		break;
				case 4:
					if(controller_loadFromText("backup.csv",listaPasajeros) == 0)
					{
						printf("\nLos datos han sido cargados exitosamente desde el Back up.\n");
					}
					else
					{
						printf("\nLos datos no se han podido cargar.\n");
					}
					break;
            	}
                break;
            case 2:
            	if(cargarDatos == 0)
            	{
					if(controller_loadFromBinary("data.bin",listaPasajeros) == 0)
					{
						cargarDatos = 1;
						printf("\nLos datos han sido cargados exitosamente desde el modo binario.\n");
						if(contadorPasajerosAgregados != 0 && controlId == 0)
						{
							if(controller_controlarId("data.csv", listaPasajeros, contadorPasajerosAgregados, contadorPasajerosBorrados, &ultimoId) != -1)
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
							controller_controlarRepetidos(listaPasajeros, contadorPasajerosAgregadosAntesGuardar);
						}
					}
					else
					{
						printf("\nLos datos no se han podido cargar.\n");
					}
            	}
            	else
            	{
            		printf("\nYa cargó los datos.\n");
            	}
            	break;
            case 3:
            	if(controller_addPassenger(listaPasajeros, contadorPasajerosBorrados, contadorPasajerosBorradosDespuesDeGuardar, cantidadPasajerosLista, controlId, ultimoId, cargarDatos) == 0)
            	{
            		printf("\nSe ha agregado correctamente el pasajero.\n");
					guardado = 0;
					contadorPasajerosAgregados++;
					if(cargarDatos != 1)
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
            		errorEdit = controller_editPassenger(listaPasajeros);
            		switch(errorEdit)
            		{
            		case -1:
            			printf("\nError. Se encontró un inconveniente en la lista.\n");
            			break;
            		case -2:
            			printf("Error. El id ingresado no coincide con ninguno en la lista\n");
            			break;
            		case -3:
            			printf("Error. Hubo un inconveniente al intentar obtener los datos del pasajero.\n");
            			break;
            		default:
            			guardado = 0;
            		}
            	}
            	else
            	{
            		printf("\nTodavía no ingresó ningún pasajero.\n");
            	}
            	printf("\nVolviendo al menu principal.\n");
				break;
            case 5:
            	errorRemover = controller_removePassenger(listaPasajeros);
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
            	utn_getInt(&listaAMostrar, "Opciones de lista para mostrar:\n"
            			"  1- Lista Principal.\n"
            			"  2- Sub Lista Generada.\n"
            			"  3- Lista Filtrada.\n"
            			"Cual lista desea mostrar? ", "Error. Ingrese una opción valida.\n", 1, 3);
            	switch(listaAMostrar)
            	{
            	case 1:
					if(controller_ListPassenger(listaPasajeros) != 0)
					{
						printf("\nError. La lista se encuentra vacía.\n");
						printf("\nVolviendo al menu principal.\n");
					}
            		break;
            	case 2:
            		if(controller_ListPassenger(subLista) != 0)
					{
						printf("\nError. La lista se encuentra vacía.\n");
						printf("\nVolviendo al menu principal.\n");
					}
            		break;
            	case 3:
            		if(controller_ListPassenger(listaFiltrada) != 0)
					{
						printf("\nError. La lista se encuentra vacía.\n");
						printf("\nVolviendo al menu principal.\n");
					}
            		break;
            	}
				break;
            case 7:
            	utn_getInt(&listaAOrdenar, "Opciones de lista para ordenar:\n"
            			"  1- Lista Principal.\n"
            			"  2- Sub Lista Generada.\n"
            			"  3- Lista Filtrada.\n"
            			"Cual lista desea ordenar? ", "Error. Ingrese una opción valida.\n", 1, 3);
            	switch(listaAOrdenar)
            	{
            	case 1:
					opcionesSort = controller_sortPassenger(listaPasajeros);
            		break;
            	case 2:
            		opcionesSort = controller_sortPassenger(subLista);
            		break;
            	case 3:
            		opcionesSort = controller_sortPassenger(listaFiltrada);
            		break;
            	}
            	switch(opcionesSort)
            	{
            	case 1:
            		printf("\nSe ordenó correctamente los pasajeros por id.\n");
            		break;
            	case 2:
            		printf("\nSe ordenó correctamente los pasajeros por apellido.\n");
            		break;
            	case 3:
            		printf("\nSe ordenó correctamente los pasajeros por tipo de pasajero.\n");
            		break;
            	case 4:
            		printf("\nSe ordenó correctamente los pasajeros por codigo de vuelo.\n");
            		break;
            	default:
            		printf("\nError. No se pudo ordenar correctamente los pasajeros.\n");
            	}
				break;
            case 8:
            case 9:
            	utn_getInt(&listaAGuardar, "Opciones de lista para guardar:\n"
            			"  1- Lista Principal.\n"
            			"  2- Sub Lista Generada.\n"
            			"  3- Lista Filtrada.\n"
            			"Cual lista desea guardar? ", "Error. Ingrese una opción valida.\n", 1, 3);

            	switch(listaAGuardar)
            	{
            	case 1:
					if(cargarDatos == 0 && controlId == 0)
					{
						cantidadPasajerosLista = controller_controlarId("data.csv", listaPasajeros, contadorPasajerosAgregados, contadorPasajerosBorrados, &ultimoId);
						if(cantidadPasajerosLista != -1)
						{
							controlId = 2;
						}
						else
						{
							printf("\nError.No se pudo corregir los id de los nuevos pasajeros ingresados al guardar.\n");
						}
					}
					ll_sort(listaPasajeros, Passenger_sortById, 1);
					if(controller_saveAsText("data.csv", listaPasajeros, cargarDatos) == 0)
					{
						if(controller_saveAsBinary("data.bin", listaPasajeros, cargarDatos) == 0)
						{
							printf("\nSe guardo con exito los datos de los pasajeros en el archivo data.csv.\n");
							guardado = 1;
						}
					}
					else
					{
						printf("\nError. No se pudo guardar los datos de los pasajeros en el archivo data.csv.\n");
					}
            		break;
            	case 2:
            		if(controller_saveAsText("sublista.csv", subLista, 1) == 0)
            		{
            			printf("\nSe guardo con exito los datos de la Sub Lista de pasajeros.\n");
            			guardado = 1;
            		}
            		else
            		{
            			printf("\nError. No se pudo guardar los datos de la Sub Lista de pasajeros.\n");
            		}
            		break;
            	case 3:
            		switch(criterioFiltrado)
            		{
            		case 1:
						if(controller_saveAsText("FirstClass.csv", listaFiltrada, 1) == 0)
						{
							printf("\nSe guardo con exito los datos de la lista de pasajeros filtrada por First Class.\n");
							guardado = 1;
						}
						else
						{
							printf("\nError. No se pudo guardar los datos de la Lista filtrada por First Class de pasajeros.\n");
						}
            			break;
            		case 2:
						if(controller_saveAsText("ExecutiveClass.csv", listaFiltrada, 1) == 0)
						{
							printf("\nSe guardo con exito los datos de la lista de pasajeros filtrada por Executive Class.\n");
							guardado = 1;
						}
						else
						{
							printf("\nError. No se pudo guardar los datos de la Lista filtrada por Executive Class de pasajeros.\n");
						}
            			break;
            		case 3:
						if(controller_saveAsText("EconomyClass.csv", listaFiltrada, 1) == 0)
						{
							printf("\nSe guardo con exito los datos de la lista de pasajeros filtrada por Economy Class.\n");
							guardado = 1;
						}
						else
						{
							printf("\nError. No se pudo guardar los datos de la Lista filtrada por Economy Class de pasajeros.\n");
						}
            			break;
            		}
            		break;
            	}
				break;
            case 10:
            	if(controller_borrarLista(listaPasajeros) == 0)
            	{
            		printf("\nSe ha vaciado toda la lista correctamente.\n");
            	}
            	else
            	{
            		printf("\nOcurrió un error al intentar vaciar la lista\n");
            	}
            	break;
            case 11:
            	subLista = controller_crearSubLista(listaPasajeros, ultimoId);
            	if(subLista != NULL)
            	{
            		printf("\nSe ha creado la sublista correctamente.\n");
            	}
            	else
            	{
            		printf("\nOcurrió un error al intentar crear la sublista.\n");
            	}
				break;
            case 12:
            	backup = controller_backup(listaPasajeros);
            	if(backup != NULL)
            	{
            		if(controller_saveAsText("backup.csv", backup, 1) == 0)
            		{
            			printf("\nSe ha realizado el back up con exito.\n");
            		}
            		else
            		{
            			printf("\nHa ocurrido un error al intentar guardar el back up.\n");
            		}
            	}
            	else
            	{
            		printf("\nHa ocurrido un error al intentar crear el back up.\n");
            	}
				break;
            case 13:
            	listaFiltrada = controller_filtrarPasajeros(listaPasajeros, &criterioFiltrado);
            	if(listaFiltrada != NULL)
            	{
            		switch(criterioFiltrado)
            		{
            		case 1:
            			printf("\nSe ha filtrado la lista por FirstClass con exito.\n");
            			break;
            		case 2:
            			printf("\nSe ha filtrado la lista por ExecutiveClass con exito.\n");
            			break;
            		case 3:
            			printf("\nSe ha filtrado la lista por EconomyClass con exito.\n");
            			break;
            		default:
            			printf("\nHa ocurrido un error al intentar filtrar la lista.\n");
            		}
            	}
            	else
            	{
            		printf("\nHa ocurrido un error al intentar filtrar la lista.\n");
            	}
				break;
            case 14:
            	if(controller_descuentoAumentoPrecio(listaPasajeros, listaFiltrada, subLista) == 0)
            	{
            		printf("\nSe ha aplicado el cambio al precio con exito.\n");
            	}
            	else
            	{
            		printf("\nError. No se ha aplicado el cambio al precio.\n");
            	}
				break;
            default:
            	if(guardado == 0)
            	{
            		printf("\nError. No puede cerrar el sistema sin guardar los datos antes\n");
            	}
            	else
            	{
            		printf("\nCerrando sistema.\n");
            	}
        }
    }while(option != 15 || guardado != 1);

    ll_deleteLinkedList(listaPasajeros);

    return 0;
}
