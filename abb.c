#include "abb.h"
#include "pila.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct nodo{
	char *clave;
	void *dato;
	struct nodo *izquierdo;
	struct nodo *derecho;
} nodo_t;

struct abb{
	nodo_t* raiz;
	size_t cantidad;
	abb_comparar_clave_t comparar;
	abb_destruir_dato_t destruir_dato;
};

struct abb_iter{
  const abb_t *arbol;
  pila_t *pila;
};

/* ******************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

nodo_t* crear_nodo(const char *clave, void *dato){

    nodo_t* nodo = malloc(sizeof(nodo_t));
    if(!nodo) return NULL;

    char *clave_aux = malloc(sizeof(char) * strlen(clave) + 1);
    if(!clave_aux){
    	free(nodo);
    	return NULL;
    }
    strcpy(clave_aux, clave);
    nodo->clave = clave_aux;
    nodo->dato = dato;
    nodo->izquierdo = NULL;
    nodo->derecho = NULL;
    return nodo;
}

void destruir_nodo(nodo_t* nodo, void destruir_dato(void*)){

    free(nodo->clave);
    if(destruir_dato){
	    destruir_dato(nodo->dato);
    }
    free(nodo);
}

nodo_t* buscar_padre( nodo_t* padre, nodo_t* nodo, const abb_t* abb, const char* clave){
	if(!nodo) return NULL;

	if(abb->comparar(clave, nodo->clave) < 0){
		return buscar_padre(nodo, nodo->izquierdo,abb, clave);
	}
	if(abb->comparar(clave, nodo->clave) > 0){
		return buscar_padre(nodo, nodo->derecho,abb, clave);
	}
	return padre;
}

void apilar_izquierdos(nodo_t* actual , abb_iter_t* abb_iter){

    while(actual){
    	pila_apilar(abb_iter->pila, actual);
    	actual = actual->izquierdo;
    }
}

nodo_t* abb_buscar(nodo_t *actual, const char *clave, const abb_t* arbol){

	if (!actual) return NULL;

	int cmp = arbol->comparar(actual->clave, clave);
	if (cmp == 0)return actual;
	if (cmp < 0) return abb_buscar(actual->derecho, clave, arbol);
	if (cmp > 0) return abb_buscar(actual->izquierdo, clave, arbol);

	return NULL;
}

nodo_t* buscar_reemplazante(nodo_t* actual , abb_t* arbol){

	if (!actual) return NULL;
	if (actual->izquierdo) return buscar_reemplazante(actual->izquierdo, arbol);
	return actual;
}

void asignar_hijo(nodo_t* padre, nodo_t* hijo, abb_t* arbol){

	if (!padre){
		arbol->raiz = hijo;
	}else if (arbol->comparar(padre->clave, hijo->clave) > 0){ //si el padre es mas grande que su hijo,este hijo es izq
		padre->izquierdo = hijo;
	} else{
		padre->derecho = hijo;
	}
}

/* ******************************************************************
 *                    PRIMITIVAS DEL ABB
 * *****************************************************************/

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){

	abb_t *abb = calloc(1 , sizeof(abb_t));
	if(!abb) return NULL;

	abb->comparar = cmp;
	abb->destruir_dato = destruir_dato;
	return abb;
}

bool _abb_guardar(nodo_t *actual, const char *clave, void *dato, abb_t* arbol){

	int cmp = arbol->comparar(actual->clave, clave);

	if (cmp == 0){
		void *aux = actual->dato;
		actual->dato = dato;
		if(arbol->destruir_dato){
			arbol->destruir_dato(aux);
		}
		actual->dato = dato;
		return true;
	}

	if (cmp < 0) {

		if (!actual->derecho){
			actual->derecho = crear_nodo(clave, dato);
			if (!actual->derecho) return false;
		} else {
			return _abb_guardar(actual->derecho, clave, dato, arbol);
		}
	}

	if (cmp > 0) {

		if (!actual->izquierdo){
			actual->izquierdo = crear_nodo(clave, dato);
			if (!actual->izquierdo) return false;
		} else {
			return _abb_guardar(actual->izquierdo, clave, dato, arbol);
		}
	}

	arbol->cantidad = arbol->cantidad + 1;
	return true;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){

	if(!arbol->raiz){
		nodo_t *nuevo_nodo = crear_nodo(clave, dato);
		if(!nuevo_nodo) return false;
    arbol->raiz = nuevo_nodo;
		arbol->cantidad = arbol->cantidad + 1;
		return true;
	}else{
		return _abb_guardar(arbol->raiz, clave, dato, arbol);
	}
}

void* _abb_borrar(nodo_t *borrado, abb_t* arbol){

	void* dato = borrado->dato;

	abb_comparar_clave_t cmp = arbol->comparar;

	if(borrado->derecho && borrado->izquierdo){

		nodo_t* reemplazante = buscar_reemplazante(borrado->derecho , arbol);

		char* clave_aux = strdup(reemplazante->clave);
		void* dato_aux = abb_borrar(arbol,clave_aux);
		free(borrado->clave);
		borrado->clave = clave_aux;
		borrado->dato = dato_aux;

	} else if(!borrado->derecho && !borrado->izquierdo){ //no tiene hijos

		nodo_t* padre_borrado = buscar_padre(NULL, arbol->raiz, arbol, borrado->clave);

		if(!padre_borrado){
			arbol->raiz = NULL; //si el padre es null significa que buscado es la raiz del arbol

		} else if (cmp(padre_borrado->clave, borrado->clave) > 0){ //si el padre es mas grande que su hijo,este hijo es izq
			padre_borrado->izquierdo = NULL;
		} else{
			padre_borrado->derecho = NULL;
		}
		destruir_nodo(borrado, arbol->destruir_dato);
		arbol->cantidad --;

	} else { //tiene un hijo

		nodo_t* padre_borrado = buscar_padre(NULL, arbol->raiz, arbol, borrado->clave);

		if(borrado->izquierdo){
			//if (!padre_borrado) arbol->raiz = borrado->izquierdo;
			asignar_hijo(padre_borrado, borrado->izquierdo, arbol);
		} else {
			//if (!padre_borrado) arbol->raiz = borrado->derecho;
			asignar_hijo(padre_borrado, borrado->derecho, arbol);
		}
		destruir_nodo(borrado, arbol->destruir_dato);
		arbol->cantidad --;
	}

	return dato;
}

void* abb_borrar(abb_t* arbol, const char* clave){

	if(!arbol->raiz) return NULL;
	nodo_t* buscado = abb_buscar(arbol->raiz, clave, arbol);
	if(!buscado) return NULL;
	return _abb_borrar(buscado,arbol);

}

void* abb_obtener(const abb_t *arbol, const char *clave){

	if(!arbol->raiz) return NULL;
	nodo_t* encontrado = abb_buscar(arbol->raiz, clave, arbol);
	if (!encontrado) return NULL;
	return encontrado->dato;
}

bool abb_pertenece(const abb_t* arbol, const char *clave){

	if(!arbol->raiz) return false;

	nodo_t* encontrado = abb_buscar(arbol->raiz, clave, arbol);
	return (encontrado!=NULL);
}

size_t abb_cantidad(abb_t *arbol){

	return arbol->cantidad;
}

void abb_destruir_rec(nodo_t* nodo, void destruir_dato(void*)){

	if(!nodo) return;
	abb_destruir_rec(nodo->izquierdo , destruir_dato);
	abb_destruir_rec(nodo->derecho , destruir_dato);
	destruir_nodo(nodo, destruir_dato);
}

void abb_destruir(abb_t *arbol){

	abb_destruir_rec(arbol->raiz, arbol->destruir_dato);
	free(arbol);
}

/* ******************************************************************
 *                    ITERADOR EXTERNO
 * *****************************************************************/

abb_iter_t* abb_iter_in_crear(const abb_t *arbol){

    abb_iter_t* abb_iter = malloc(sizeof(abb_iter_t));
    if(!abb_iter) return NULL;

		abb_iter->arbol = arbol;

    abb_iter->pila = pila_crear();
    if(!abb_iter->pila){
        free(abb_iter);
        return NULL;
    }

		apilar_izquierdos(arbol->raiz , abb_iter);

    return abb_iter;
}

bool abb_iter_in_avanzar(abb_iter_t *iter){

  if(abb_iter_in_al_final(iter)) return false;

  nodo_t* actual = pila_desapilar(iter->pila);

  if(actual->derecho) apilar_izquierdos(actual->derecho, iter);
  return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){

  if(abb_iter_in_al_final(iter)) return NULL;
	nodo_t* actual = pila_ver_tope(iter->pila);
  return actual->clave;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){

  return pila_esta_vacia(iter->pila);
}

void abb_iter_in_destruir(abb_iter_t* iter){

    pila_destruir(iter->pila);
    free(iter);
}

/* ******************************************************************
 *                    ITERADOR INTERNO
 * *****************************************************************/

bool _abb_in_order(nodo_t* nodo, abb_t* arbol,bool visitar(const char *, void *, void *),void* extra){

	if(!nodo) return true;

	if(!_abb_in_order(nodo->izquierdo, arbol, visitar, extra)) return false;
	if(!visitar(nodo->clave, nodo->dato, extra)) return false;
	if(!_abb_in_order(nodo->derecho, arbol, visitar, extra)) return false;
	return true;
}

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
	_abb_in_order(arbol->raiz, arbol, visitar, extra);
}
