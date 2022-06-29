/*
 * inputs.h
 *
 *  Created on: 13 may. 2022
 *      Author: Fran
 */

#ifndef INPUTS_H_
#define INPUTS_H_

int myGets(char *cadena, int longitud);
int getInt(int *pResultado);
int esNumerica(char *cadena);
int utn_getInt(int *pResultado, char *mensaje, char *mensajeError, int minimo, int maximo);
int getFloat(float *pResultado);
int utn_getFloat(float *pResultado, char *mensaje, char *mensajeError, float minimo, float maximo);
int utn_getName(char* cadena, char* mensaje, char* mensajeError, int len);
void utn_corregirMayus(char* cadena);
void pedirFlycode(char codigoDeVuelo[10], char* mensaje);


#endif /* INPUTS_H_ */
