/*
 * ArrayPassenger.h
 *
 *  Created on: 12 may. 2022
 *      Author: Fran
 */

#ifndef ARRAYPASSENGER_H_
#define ARRAYPASSENGER_H_
#define VACIO -1
#define OCUPADO 0

struct
{
int id;
char name[51];
char lastName[51];
float price;
char flycode[10];
int typePassenger;
int statusFlight;
int isEmpty;
}typedef Passenger;

/// @fn int initPassengers(Passenger*, int)
/// @brief 	To indicate that all position in the array are empty,
/// 		this function put the flag (isEmpty) in TRUE in all
/// 		position of the array
/// @param list Passenger* Pointer to array of passenger
/// @param len int Array length
/// @return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
int initPassengers(Passenger* list, int len);


/// @fn int addPassenger(Passenger*, int, int, char[], char[], float, int, char[])
/// @brief 	add in a existing list of passengers the values received as parameters
/// 		in the first empty position
/// @param list passenger*
/// @param len int
/// @param id int
/// @param name[] char
/// @param lastName[] char
/// @param price float
/// @param typePassenger int
/// @param flycode[] char
/// @return int Return (-1) if Error [Invalid length or NULL pointer or without
/// 		free space] - (0) if Ok
int addPassengers(Passenger* list, int len, int id, char name[], char lastName[], float price, int typePassenger, char flycode[],int statusFlight);


/// @fn int findPassengerById(Passenger*, int, int)
/// @brief 	find a Passenger by Id en returns the index position in array.
/// @param list Passenger*
/// @param len int
/// @param id int
/// @return Return passenger index position or (-1) if [Invalid length or
/// 		NULL pointer received or passenger not found]
int findPassengerById(Passenger* list, int len, int id);


/// @fn int removePassenger(Passenger*, int, int)
/// @brief Remove a Passenger by Id (put isEmpty Flag in 1)
/// @param list Passenger*
/// @param len int
/// @param id int
/// @return int Return (-1) if Error [Invalid length or NULL pointer or if can't
/// 		find a passenger] - (0) if Ok
int removePassenger(Passenger* list, int len, int id);


/// @fn int sortPassengers(Passenger*, int, int)
/// @brief 	Sort the elements in the array of passengers, the argument order
/// 		indicate UP or DOWN order
/// @param list Passenger*
/// @param len int
/// @param order int [1] indicate UP - [0] indicate DOWN
/// @return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
int sortPassengers(Passenger* list, int len, int order);


/// @fn int printPassenger(Passenger*, int)
/// @brief print the content of passengers array
/// @param list int
/// @param length int
/// @return int
int printPassenger(Passenger* list, int length);


/// @fn int sortPassengersByCode(Passenger*, int, int)
/// @brief 	Sort the elements in the array of passengers, the argument order
/// 		indicate UP or DOWN order
/// @param list Passenger*
/// @param len int
/// @param order int [1] indicate UP - [0] indicate DOWN
/// @return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
int sortPassengersByCode(Passenger* list, int len, int order);


/// @fn int modificarPasajero(Passenger*, int)
/// @brief Permite modificar alguno de los pasajeros ingresados
/// @param list Passenger*
/// @param len int
/// @return int
int modificarPasajero(Passenger* list, int len);

int sortPassengersByLastName(Passenger* list, int len, int order);

int promedioPrecios(Passenger* list, int len, float* precioTotal, float* promedio);

int encimaDelPromedio(Passenger* list, int len, float promedio);


#endif /* ARRAYPASSENGER_H_ */
