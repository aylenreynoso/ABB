#include <stdbool.h>
#include <stdlib.h>

typedef struct abb abb_t;
typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);
typedef struct abb_iter abb_iter_t;

/*PRIMITIVAS DEL ABB*/

//PRE: cmp es una función que compara dos claves char* y devuelve un valor entero
//si la primera es menor el valor debe ser <0, si la segunda es menor el valor
// es >0. destruir_dato es un procedimiento que libera datos, si no se desea
//liberarlos se debe pasar NULL en su lugar.
//POS: se crea un abb vacio. Si hubo algún error se devuelve NULL.
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);
//PRE: El árbol fue creado.
//POS: devuelve true si se guardó el dato y la clave en el abb con éxito, false en otro caso
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);
//PRE:El árbol fue creado.
//POS: Se elimina la clave del abb y se devuelve el dato. Si la clave no pertenece se devuelve NULL.
void *abb_borrar(abb_t *arbol, const char *clave);
//PRE: El árbol fue creado.
//POS: Se obtiene el dato almacenado bajo la clave. Si la clave no pertenece se devuelve NULL.
void *abb_obtener(const abb_t *arbol, const char *clave);
//PRE: El árbol fue creado.
//POS: Devuelve true si la clave pertenece al árbol, y false en el caso contrario.
bool abb_pertenece(const abb_t *arbol, const char *clave);
//PRE: El árbol fue creado.
//POS: Devuelve la cantidad de elementos que hay en el árbol.
size_t abb_cantidad(abb_t *arbol);
//PRE: El árbol fue creado.
//POS: Libera la memoria ocupada por el árbol. Si existe una funcion destruir_dato también
//libera la memoria de los datos.
void abb_destruir(abb_t *arbol);

/*PRIMITIVA DEL ITERADOR INTERNO*/
//PRE: El árbol fue creado. Visitar es una función que toma la clave, el dato y un extra opcional y Devuelve
//true si se debe seguir iterando o false si se debe parar de iterar.
//POS: Se recorrén los elementos del árbol del menor al mayor hasta que visitar devuelva false.
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

/*PRIMITIVAS DEL ITERADOR EXTERNO*/
//PRE: El árbol fue creado.
//POS: Crea un iterador externo para el árbol. Si hubo algún error se devuelve NULL.
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);
//PRE: El árbol y el iterador fueron creados.
//POS: Avanza a la siguiente clave, en orden del menor al mayor y devuelve true. Si esta al final devuelve false.
bool abb_iter_in_avanzar(abb_iter_t *iter);
//PRE: El árbol y el iterador fueron creados.
//POS: Devuelve la clave sobre la cual el iterador esta parado. Si esta al final devuelve NULL.
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);
//PRE: El árbol y el iterador fueron creados.
//POS: Devuelve true si el iterador iteró sobre todos los elementos del arbol, false en otro caso.
bool abb_iter_in_al_final(const abb_iter_t *iter);
//PRE: El árbol y el iterador fueron creados.
//POS: Libera la memoria ocupada por el iterador.
void abb_iter_in_destruir(abb_iter_t* iter);


/* PRUEBAS ALUMNO */

void pruebas_abb_alumno();
