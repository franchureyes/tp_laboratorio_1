#ifndef PASSENGER_H_
#define PASSENGER_H_
#include "LinkedList.h"

#define TAM_NOMBRES 50
#define TAM_RESTODATOS 20
#define TAM_DECIMAL 10

typedef struct
{
	int id;
	char nombre[TAM_NOMBRES];
	char apellido[TAM_NOMBRES];
	float precio;
	int tipoPasajero;
	char codigoVuelo[TAM_RESTODATOS];
	char estadoVuelo[TAM_RESTODATOS];
}Passenger;

typedef struct
{
	int statusFlight;
	char desc_StatusFlight[TAM_RESTODATOS];
	int typePassenger;
	char desc_TypePassenger[TAM_RESTODATOS];
} StatusFlightAndTypePassenger;

Passenger* Passenger_new();
Passenger* Passenger_newParametros(char* idStr,char* nombreStr,char* tipoPasajeroStr, char* apellidoStr, char* precio, char* codigo, char* estado);
void Passenger_delete();

int Passenger_setId(Passenger* this,int idPasajero);
int Passenger_getId(Passenger* this,int* idPasajero);

int Passenger_setNombre(Passenger* this,char* nombre);
int Passenger_getNombre(Passenger* this,char* nombre);

int Passenger_setApellido(Passenger* this,char* apellido);
int Passenger_getApellido(Passenger* this,char* apellido);

int Passenger_setCodigoVuelo(Passenger* this,char* codigoVuelo);
int Passenger_getCodigoVuelo(Passenger* this,char* codigoVuelo);

int Passenger_setTipoPasajero(Passenger* this,int tipoPasajero);
int Passenger_getTipoPasajero(Passenger* this,int* tipoPasajero);

int Passenger_setPrecio(Passenger* this,float precio);
int Passenger_getPrecio(Passenger* this,float* precio);

int Passenger_setEstadoVuelo (Passenger* this,char* estadoVuelo);
int Passenger_getEstadoVuelo (Passenger* this,char* estadoVuelo);

void Passenger_printOne(Passenger* this);

int Passenger_find(LinkedList* this, int id);

int Passenger_sortById(void* pasajeroUno, void* pasajeroDos);
int Passenger_sortByApellido(void* pasajeroUno, void* pasajeroDos);
int Passenger_sortByTipoPasajero(void* pasajeroUno, void* pasajeroDos);
int Passenger_sortByCodigoVuelo(void* pasajeroUno, void* pasajeroDos);

int Passenger_filterByFirstClass (void* pElement);
int Passenger_filterByExecutiveClass (void* pElement);
int Passenger_filterByEconomyClass(void* pElement);

void Passenger_applyPriceIncrease(void* pElement);
void Passenger_applyPriceDiscount(void* pElement);

#endif /* PASSENGER_H_ */
