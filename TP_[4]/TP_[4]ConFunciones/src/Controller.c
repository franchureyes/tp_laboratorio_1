#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Passenger.h"
#include "parser.h"
#include "Controller.h"
#include <string.h>
#include "inputs.h"

/** \brief Carga los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListPassenger)
{
	int retorno = -1;

	if(pArrayListPassenger != NULL)
	{
		if (path != NULL)
		{
			FILE* pArchivo;
			pArchivo = fopen (path,"r");

			if(pArchivo != NULL)
			{
				if(parser_PassengerFromText(pArchivo, pArrayListPassenger) == 0)
				{
					retorno = 0;
				}
			}

			fclose(pArchivo);
		}
	}

    return retorno;
}

/** \brief Carga los datos de los pasajeros desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListPassenger)
{
	int retorno = -1;

	if(path != NULL)
	{
		if(pArrayListPassenger != NULL)
		{
			FILE *pArchivo;

			pArchivo = fopen(path, "rb");

			if(pArchivo != NULL)
			{
				if(parser_PassengerFromBinary(pArchivo, pArrayListPassenger) == 0)
				{
					retorno = 0;
				}
			}

			fclose(pArchivo);
		}
	}

    return retorno;
}

/** \brief Alta de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_addPassenger(LinkedList* pArrayListPassenger, int contadorBorrados, int contadorBorradosDespuesDeGuardar, int contadorLista ,int usoGuardarPeroNoCargar, int ultimoId, int cargarDatos)
{
	int retorno = -1;

	if(pArrayListPassenger != NULL)
	{
		Passenger* unPasajero;
		char idStr[TAM_RESTODATOS];
		char nombre[TAM_NOMBRES];
		char apellido[TAM_NOMBRES];
		char precioStr[TAM_RESTODATOS];
		int tipoPasajero;
		char tipoPasajeroStr[TAM_RESTODATOS];
		char codigoVuelo[TAM_RESTODATOS];
		int estadoVuelo;
		char estadoVueloStr[TAM_RESTODATOS];
		int len;
		int r;
		int id;
		int difEntreUltIdYContLista;

		len = ll_len(pArrayListPassenger);
		difEntreUltIdYContLista = ultimoId - contadorLista;

		if(usoGuardarPeroNoCargar == 2)
		{
			if(cargarDatos != 1)
			{
				id = 1 + len + contadorLista + difEntreUltIdYContLista + contadorBorradosDespuesDeGuardar;
			}
			else
			{
				id = 1 + len + difEntreUltIdYContLista + contadorBorradosDespuesDeGuardar;
			}
		}
		else
		{
			id = 1 + len + contadorBorrados;
		}

		itoa(id,idStr,TAM_DECIMAL);

		r = utn_getName(nombre, "Ingrese el nombre del pasajero: ", "Error. Ingrese el nombre correctamente.\n");
		if(r == 0)
		{
			r = utn_getName(apellido, "Ingrese el apellido del pasajero: ", "Error. Ingese el apellido correctamente.\n");
			if(r == 0)
			{
				r = utn_getFloat(precioStr, "Ingrese el precio del vuelo: ", "Error. Ingrese un dato valido.\n");
				if(r == 0)
				{
					r = utn_getInt(&tipoPasajero, "Ingrese 1 si es First Class, 2 si es Executive Class, 3 si es Economy Class: ",
							"Error. Ingrese una opción valida.\n", 1, 3);
					itoa(tipoPasajero, tipoPasajeroStr, TAM_DECIMAL);
					pedirCodigoVuelo(codigoVuelo, "Ingrese el codigo de vuelo: ");

					if(r == 0)
					{
						r = utn_getInt(&estadoVuelo, "Ingrese 1 si el vuelo esta Aterrizado, 2 si esta En horario, 3 si esta En vuelo, 4 si esta Demorado: ",
								"Error. Ingrese una opción valida.\n",1,4);
						switch(estadoVuelo)
						{
						case 1:
							strcpy(estadoVueloStr,"Aterrizado");
							break;
						case 2:
							strcpy(estadoVueloStr,"En horario");
							break;
						case 3:
							strcpy(estadoVueloStr,"En vuelo");
							break;
						default:
							strcpy(estadoVueloStr,"Demorado");
						}
						if(r == 0)
						{
							unPasajero = Passenger_newParametros(idStr, nombre, tipoPasajeroStr, apellido, precioStr, codigoVuelo, estadoVueloStr);
							if(unPasajero != NULL)
							{
								ll_add(pArrayListPassenger, unPasajero);
								retorno = 0;
							}
						}
					}
				}
			}
		}
	}

    return retorno;
}

/** \brief Modificar datos de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_editPassenger(LinkedList* pArrayListPassenger)
{
	int retorno = -1;

	if(pArrayListPassenger != NULL)
	{
		int id;
		int index;
		int campoModificar;
		char nombre[TAM_NOMBRES];
		char apellido[TAM_NOMBRES];
		char precio[TAM_RESTODATOS];
		char codigo[TAM_RESTODATOS];
		int tipoPasajero;
		int estadoVuelo;
		char estadoVueloStr[TAM_RESTODATOS];
		Passenger* pasajeroAux;

		if(!ll_isEmpty(pArrayListPassenger))
		{
			if(utn_getInt(&id,"Ingrese el id del pasajero que desea modificar: ","Error. El id ingresado no es valido.\n", 1, 9999999) == 0)
			{
				index = Passenger_find(pArrayListPassenger, id);
				if(index > -1)
				{
					pasajeroAux = ll_get(pArrayListPassenger, index);
					if(pasajeroAux != NULL)
					{
						printf("\nEl pasajero que seleccionó para modificar es:\n");
						Passenger_printOne(pasajeroAux);
						do{
							utn_getInt(&campoModificar, "\nCampos que se pueden modificar:\n"
									"  1- Nombre.\n"
									"  2- Apellido.\n"
									"  3- Precio del Vuelo.\n"
									"  4- Tipo de pasajero.\n"
									"  5- Codigo de vuelo.\n"
									"  6- Estado de vuelo.\n"
									"  7- Guardar cambios y volver al menú principal.\n"
									"Cual desea modificar? ", "Error. Ingrese una opción valida\n", 1, 7);
							switch(campoModificar)
							{
							case 1:
								if(utn_getName(nombre, "Ingrese el nombre del pasajero: ", "Error. Ingrese el nombre correctamente.\n") == 0)
								{
									if(Passenger_setNombre(pasajeroAux, nombre) == 0)
									{
										printf("\nEl nombre del pasajero fue modificado correctamente.\n");
										retorno = 0;
									}
									else
									{
										printf("\nError. No se pudo cambiar el nombre.\n");
									}
								}
								else
								{
									printf("\nError. No se pudo cambiar el nombre.\n");
								}
								break;
							case 2:
								if(utn_getName(apellido, "Ingrese el apellido del pasajero: ", "Error. Ingese el apellido correctamente.\n") == 0)
								{
									if(Passenger_setApellido(pasajeroAux, apellido) == 0)
									{
										printf("\nEl apellido del pasajero fue modificado correctamente.\n");
										retorno = 0;
									}
									else
									{
										printf("\nError. No se pudo cambiar el apellido.\n");
									}
								}
								else
								{
									printf("\nError. No se pudo cambiar el apellido.\n");
								}
								break;
							case 3:
								if(utn_getFloat(precio, "Ingrese el precio del vuelo: ", "Error. Ingrese un dato valido.\n") == 0)
								{
									if(Passenger_setPrecio(pasajeroAux, atof(precio)) == 0)
									{
										printf("\nEl precio del vuelo fue modificado correctamente.\n");
										retorno = 0;
									}
									else
									{
										printf("\nError. No se pudo cambiar el precio del vuelo.\n");
									}
								}
								else
								{
									printf("\nError. No se pudo cambiar el precio del vuelo.\n");
								}
								break;
							case 4:
								utn_getInt(&tipoPasajero, "Ingrese 1 si es First Class, 2 si es Executive Class, 3 si es Economy Class: ",
										"Error. Ingrese una opción valida.\n", 1, 3);
								if(Passenger_setTipoPasajero(pasajeroAux, tipoPasajero) == 0)
								{
									printf("\nEl tipo de pasajero fue modificado correctamente.\n");
									retorno = 0;
								}
								else
								{
									printf("\nError. No se pudo cambiar el tipo de pasajero.\n");
								}
								break;
							case 5:
								pedirCodigoVuelo(codigo, "Ingrese el codigo de vuelo: ");
								if(Passenger_setCodigoVuelo(pasajeroAux, codigo) == 0)
								{
									printf("\nEl codigo del vuelo fue modificado correctamente.\n");
									retorno = 0;
								}
								else
								{
									printf("\nError. No se pudo cambiar el codigo del vuelo.\n");
								}
								break;
							case 6:
								utn_getInt(&estadoVuelo, "Ingrese 1 si el vuelo esta Aterrizado, 2 si esta En horario, 3 si esta En vuelo, 4 si esta Demorado: ",
																	"Error. Ingrese una opción valida.\n",1,4);
								switch(estadoVuelo)
								{
								case 1:
									strcpy(estadoVueloStr,"Aterrizado");
									break;
								case 2:
									strcpy(estadoVueloStr,"En horario");
									break;
								case 3:
									strcpy(estadoVueloStr,"En vuelo");
									break;
								default:
									strcpy(estadoVueloStr,"Demorado");
								}
								if(Passenger_setEstadoVuelo(pasajeroAux, estadoVueloStr) == 0)
								{
									printf("\nEl estado del vuelo fue modificado correctamente.\n");
									retorno = 0;
								}
								else
								{
									printf("\nError. No se pudo cambiar el estado del vuelo.\n");
								}
								break;
							case 7:
								if(ll_set(pArrayListPassenger, index, pasajeroAux) == 0)
								{
									printf("\nEl pasajero fue modificado con exito.\n");
									retorno = 0;
								}
								else
								{
									printf("\nError. No se pudo modificar el pasajero\n");
								}
							}
						}while(campoModificar != 7);
					}
					else
					{
						retorno = -3;
					}
				}
				else
				{
					retorno = -2;
				}
			}
		}
	}
    return retorno;
}

/** \brief Baja de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_removePassenger(LinkedList* pArrayListPassenger)
{
	int retorno = -1;

	if(pArrayListPassenger != NULL)
	{
		int id;
		int index;
		char confirmacion[TAM_RESTODATOS];
		int confirmacionSi;
		int confirmacionNo;
		Passenger* pasajeroAux;

		if(!ll_isEmpty(pArrayListPassenger))
		{
			controller_ListPassenger(pArrayListPassenger);
			if(utn_getInt(&id,"Ingrese el id del pasajero que desea dar de baja: ","Error. El id ingresado no es valido.\n", 0, 999999) == 0)
			{
				index = Passenger_find(pArrayListPassenger, id);
				if(index > -1)
				{
					pasajeroAux = ll_pop(pArrayListPassenger, index);
					if(pasajeroAux != NULL)
					{
						printf("El pasajero a dar de baja es:\n");
						Passenger_printOne(pasajeroAux);
						do{
							utn_getName(confirmacion, "Esta seguro que es quien quiere eliminar? (responda 'si' o 'no'): ", "Error. Ingrese una respuesta valida.\n");
							confirmacionSi = strcmp(confirmacion, "Si");
							confirmacionNo = strcmp(confirmacion, "No");
							if(confirmacionSi == 0)
							{
								Passenger_delete(pasajeroAux);
								retorno = 0;
							}
							else
							{
								if(confirmacionNo == 0)
								{
									if(ll_push(pArrayListPassenger, index, pasajeroAux) == 0)
									{
										retorno = -3;
									}
								}
								else
								{
									printf("\nError. Ingrese una respuesta valida.\n");
								}
							}
						}while(confirmacionSi != 0 && confirmacionNo != 0);
					}
				}
				else
				{
					retorno = -2;
				}
			}
		}
	}

    return retorno;
}

/** \brief Listar pasajeros
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_ListPassenger(LinkedList* pArrayListPassenger)
{
	int retorno = -1;
	if(pArrayListPassenger != NULL)
	{
		int cantElementosPasajeros;
	    Passenger* unPasajero;

		cantElementosPasajeros = ll_len(pArrayListPassenger);

		if(ll_isEmpty(pArrayListPassenger) == 0)
		{
			for(int i = 0; i < cantElementosPasajeros; i++)
			{
				unPasajero = (Passenger*) ll_get(pArrayListPassenger, i);
				Passenger_printOne(unPasajero);
			}
			retorno = 0;
		}
	}

    return retorno;
}

/** \brief Ordenar pasajeros
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_sortPassenger(LinkedList* pArrayListPassenger)
{
	int retorno = -1;
	int orden;
	int criterio;

	if(pArrayListPassenger != NULL)
	{
		utn_getInt(&criterio, "\nOpciones de ordenamiento:\n"
				"  1- Ordenar por id.\n"
				"  2- Ordenar por Apellido.\n"
				"  3- Ordenar por tipo de pasajero.\n"
				"  4- Ordenar por codigo de vuelo.\n"
				"Como desea ordenar la lista de pasajeros? ", "Error. Ingrese una opción valida.\n", 1, 4);
		utn_getInt(&orden, "Ingrese 1 para orden ascendente o 0 para orden desencente: ", "Error. Ingrese una opción valida.\n", 0, 1);

		switch(criterio)
		{
		case 1:
			if(ll_sort(pArrayListPassenger, Passenger_sortById, orden) == 0)
			{
				retorno = 1;
			}
			break;
		case 2:
			if(ll_sort(pArrayListPassenger, Passenger_sortByApellido, orden) == 0)
			{
				retorno = 2;
			}
			break;
		case 3:
			if(ll_sort(pArrayListPassenger, Passenger_sortByTipoPasajero, orden) == 0)
			{
				retorno = 3;
			}
			break;
		case 4:
			if(ll_sort(pArrayListPassenger, Passenger_sortByCodigoVuelo, orden) == 0)
			{
				retorno = 4;
			}
			break;
		}
	}

    return retorno;
}

/** \brief Guarda los datos de los pasajeros en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListPassenger, int abiertoPreviamente)
{
	int retorno = -1;

	if(pArrayListPassenger != NULL)
	{
		if (path != NULL)
		{
			FILE* pArchivo;
			Passenger* pasajeroAux;
			int len;
			int idAux;
			char nombreAux[TAM_NOMBRES];
			char apellidoAux[TAM_NOMBRES];
			float precioAux;
			int tipoPasajeroAux;
			char tipoPasajeroConvertido[TAM_RESTODATOS];
			char codigoVueloAux[TAM_RESTODATOS];
			char estadoVueloAux[TAM_RESTODATOS];

			len = ll_len(pArrayListPassenger);

			if(abiertoPreviamente == 1)
			{
				pArchivo = fopen (path,"w");
			}
			else
			{
				pArchivo = fopen (path,"a");
			}

			if(len > 0)
			{
				if(pArchivo != NULL)
				{
					if(abiertoPreviamente == 1)
					{
						fprintf(pArchivo,"id,name,lastname,price,flycode,typePassenger,statusFlight\n");
					}

					for(int i = 0; i < len; i++)
					{
						pasajeroAux = ll_get(pArrayListPassenger, i);
						if(pasajeroAux != NULL)
						{
							if(Passenger_getId(pasajeroAux, &idAux) == 0)
							{
								if(Passenger_getNombre(pasajeroAux, nombreAux) == 0)
								{
									if(Passenger_getApellido(pasajeroAux, apellidoAux) == 0)
									{
										if(Passenger_getPrecio(pasajeroAux, &precioAux) == 0)
										{
											if(Passenger_getCodigoVuelo(pasajeroAux, codigoVueloAux) == 0)
											{
												if(Passenger_getTipoPasajero(pasajeroAux, &tipoPasajeroAux) == 0)
												{
													if(tipoPasajeroAux == 1)
													{
														strcpy(tipoPasajeroConvertido, "FirstClass");
													}
													else
													{
														if(tipoPasajeroAux == 2)
														{
															strcpy(tipoPasajeroConvertido, "ExecutiveClass");
														}
														else
														{
															strcpy(tipoPasajeroConvertido, "EconomyClass");
														}
													}
													if(Passenger_getEstadoVuelo(pasajeroAux, estadoVueloAux) == 0)
													{
														fprintf(pArchivo,"%d,%s,%s,%.0f,%s,%s,%s\n",idAux,nombreAux,apellidoAux,precioAux,codigoVueloAux,tipoPasajeroConvertido,estadoVueloAux);
													}
												}
											}
										}
									}
								}
							}
						}
					}
					retorno = 0;
				}
			}
			fclose(pArchivo);
		}
	}
    return retorno;
}

/** \brief Guarda los datos de los pasajeros en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListPassenger, int abiertoPreviamente)
{
	int retorno = -1;

	if(pArrayListPassenger != NULL)
	{
		if (path != NULL)
		{
			FILE* pArchivo;
			Passenger* pasajeroAux;
			int len;

			pArchivo = fopen (path,"wb");

			len = ll_len(pArrayListPassenger);
			if(len > 0)
			{
				if(pArchivo != NULL)
				{
					for(int i = 0; i < len; i++)
					{
						pasajeroAux = ll_get(pArrayListPassenger, i);
						if(pasajeroAux != NULL)
						{
							fwrite(pasajeroAux,sizeof(Passenger),1,pArchivo);
						}
					}
					retorno = 0;
				}
			}
			fclose(pArchivo);
		}
	}
    return retorno;
}

/**
 * @brief
 *
 * @param path
 * @param pArrayListPassenger
 * @param cantAgregados
 * @param cantBorrados
 * @return
 */
int controller_controlarId(char* path, LinkedList* pArrayListPassenger, int cantAgregados, int cantBorrados, int *pUltimoId)
{
	int retorno = -1;

	if(pArrayListPassenger != NULL)
	{
		if(path != NULL)
		{
			FILE* pArchivo;
			Passenger* pasajeroAux;
			pArchivo = fopen (path,"r");
			char buffer[1000];
			char ultimoIdStr[TAM_RESTODATOS];
			int ultimoIdInt;
			int contador = 0;

			if(pArchivo != NULL)
			{
				fscanf(pArchivo,"%[^\n]\n", buffer);
				while(1)
				{
					fscanf(pArchivo,"%[^,],%[^\n]\n", ultimoIdStr, buffer);
					contador++;
					if(feof(pArchivo) != 0)
					{
						break;
					}
				}

				ultimoIdInt = atoi(ultimoIdStr);

				for(int i = 0; i < cantAgregados - cantBorrados; i++)
				{
					pasajeroAux = ll_get(pArrayListPassenger, i);
					Passenger_setId(pasajeroAux, 1 + i + ultimoIdInt);
					ll_set(pArrayListPassenger, i, pasajeroAux);
					printf("\nSe modificó el id de %s %s para agregarse en la lista. Ahora es %d\n",pasajeroAux->nombre,pasajeroAux->apellido,pasajeroAux->id);
				}

				*pUltimoId = ultimoIdInt;
				retorno = contador;
			}

			fclose(pArchivo);
		}
	}

    return retorno;
}

void controller_controlarRepetidos(LinkedList* pArrayListPassenger, int cantAgregados)
{
	int len;
	len = ll_len(pArrayListPassenger);

	for (int i = len; i > len - cantAgregados - 1; i--)
	{
		ll_remove(pArrayListPassenger, i);
	}

}

int controller_borrarLista(LinkedList* pArrayListPassenger)
{
	int retorno = -1;

	if(pArrayListPassenger != NULL)
	{
		if(ll_clear(pArrayListPassenger) == 0)
		{
			retorno = 0;
		}
	}

	return retorno;
}

LinkedList* controller_crearSubLista(LinkedList* pArrayListPassenger, int ultimoId)
{
	LinkedList* subLista = NULL;
	int minimo;
	int minimoIndex;
	int maximo;
	int maximoIndex;

	if(utn_getInt(&minimo, "Ingrese el id desde el cual desea subdividir la lista: ", "Error.Ingrese un valor valido\n", 0, ultimoId - 1) == 0)
	{
		minimoIndex = Passenger_find(pArrayListPassenger, minimo);
		if(utn_getInt(&maximo,"Ingrese el id hasta el cual desea subdividir la lista: ", "Error.Ingrese un valor valido\n", minimoIndex, ultimoId) == 0)
		{
			maximoIndex = Passenger_find(pArrayListPassenger, maximo);

			subLista = ll_subList(pArrayListPassenger, minimoIndex, maximoIndex);
		}
	}

	return subLista;
}

LinkedList* controller_backup (LinkedList* pArrayListPassenger)
{
	LinkedList* backup = NULL;

	if(pArrayListPassenger != NULL)
	{
		backup = ll_clone(pArrayListPassenger);
	}

	return backup;
}

LinkedList* controller_filtrarPasajeros(LinkedList* pArrayListPassenger, int* criterioFiltrado)
{
	LinkedList* listaFiltrada = NULL;
	int criterio;

	utn_getInt(&criterio, "\nOpciones de filtrado:\n"
					"  1- FirstClass.\n"
					"  2- ExecutiveClass.\n"
					"  3- EconomyClass.\n"
					"Como desea filtrar la lista de pasajeros? ", "Error. Ingrese una opción valida.\n", 1, 3);

	switch(criterio)
	{
	case 1:
		listaFiltrada = ll_filter(pArrayListPassenger, Passenger_filterByFirstClass);
		break;
	case 2:
		listaFiltrada = ll_filter(pArrayListPassenger, Passenger_filterByExecutiveClass);
		break;
	case 3:
		listaFiltrada = ll_filter(pArrayListPassenger, Passenger_filterByEconomyClass);
		break;
	}

	*criterioFiltrado = criterio;

	return listaFiltrada;
}

int controller_descuentoAumentoPrecio(LinkedList* pArrayListPassenger, LinkedList* pListFiltered, LinkedList* pSubList)
{
	int retorno = -1;
	int eleccionLista;
	int eleccionAumentoDescuento;

	if(pArrayListPassenger != NULL)
	{
		if(pListFiltered != NULL)
		{
			if(pSubList != NULL)
			{
				utn_getInt(&eleccionLista, "\nOpciones de lista para modificar su precio:\n"
									"  1- Lista Principal.\n"
									"  2- Sub Lista Generada.\n"
									"  3- Lista Filtrada.\n"
									"En cual lista desea generar el cambio? ", "Error. Ingrese una opción valida.\n", 1, 3);

				utn_getInt(&eleccionAumentoDescuento, "\nOpciones disponibles para modificar el precio:\n"
						"  1- Realizar un aumentar del 10% al precio.\n"
						"  2- Realizar un descuento del 10% al precio.\n"
						"Que operacion desea realizar? ", "Error. Ingrese una opción valida.\n", 1, 2);

				switch(eleccionLista)
				{
				case 1:
					if(ll_len(pArrayListPassenger) > 0)
					{
						if(eleccionAumentoDescuento == 1)
						{
							ll_map(pArrayListPassenger, Passenger_applyPriceIncrease);
						}
						else
						{
							ll_map(pArrayListPassenger, Passenger_applyPriceDiscount);
						}
						retorno = 0;
					}
					break;
				case 2:
					if(ll_len(pSubList) > 0)
					{
						if(eleccionAumentoDescuento == 1)
						{
							ll_map(pSubList, Passenger_applyPriceIncrease);
						}
						else
						{
							ll_map(pSubList, Passenger_applyPriceDiscount);
						}
						retorno = 0;
					}
					break;
				case 3:
					if(ll_len(pListFiltered) > 0)
					{
						if(eleccionAumentoDescuento == 1)
						{
							ll_map(pListFiltered, Passenger_applyPriceIncrease);
						}
						else
						{
							ll_map(pListFiltered, Passenger_applyPriceDiscount);
						}
						retorno = 0;
					}
					break;

			}
		}
	}
	}

	return retorno;
}


