#include "pila.h"
#include <stdlib.h>

const size_t TAM_INICIAL_PILA = 5;
const size_t MULTIPLICADOR_CAPACIDAD = 2;
const size_t DIVISOR_CAPACIDAD_MAX = 4;
const size_t DIVISOR_CAPACIDAD_MIN = 3;
/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

bool redimensionar_pila(pila_t *pila , size_t nueva_dimension){
	
	void *auxiliar = realloc(pila->datos , sizeof(void*) * nueva_dimension);
	if(auxiliar == NULL){
		return false;	
	}	
	pila->datos = auxiliar;
	pila->capacidad = nueva_dimension;	
	return true;	
}

pila_t* pila_crear(void){

	pila_t* pila = malloc(sizeof(pila_t));
	if(pila == NULL){
		return NULL;
	}
	pila->cantidad = 0;
	pila->datos = malloc(sizeof(void*)* TAM_INICIAL_PILA);
	if(pila->datos == NULL){
		free(pila);
		return NULL;
	}
	pila->capacidad = TAM_INICIAL_PILA;
	return pila;
}

void pila_destruir(pila_t *pila){

	free(pila->datos);
	free(pila);	
}

bool pila_esta_vacia(const pila_t *pila){

	return( pila->cantidad == 0);
}

bool pila_apilar(pila_t *pila, void* valor){
	
	if(pila->cantidad == pila->capacidad){
		if( !(redimensionar_pila(pila , pila->capacidad * MULTIPLICADOR_CAPACIDAD)) ){
			return false;
		}
	}
	size_t i = pila->cantidad;
	pila->datos[i] = valor;
	(pila->cantidad)++;
   	return true;
}

void* pila_ver_tope(const pila_t *pila){

	if( pila_esta_vacia(pila) ){
		return NULL;	 
	}
	return pila->datos[pila->cantidad - 1];	
}

void* pila_desapilar(pila_t *pila){

	if(pila_esta_vacia(pila)){ 
		return NULL;	
	}
	void* tope = pila_ver_tope(pila);	
	(pila->cantidad)--;
	if( pila->cantidad < (pila->capacidad / DIVISOR_CAPACIDAD_MAX) ){
		redimensionar_pila(pila , pila->capacidad / DIVISOR_CAPACIDAD_MIN);
	}
	return tope;	
}
