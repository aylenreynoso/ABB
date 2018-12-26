#include "abb.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For ssize_t in Linux.

static void prueba_crear_abb_vacio(){

	abb_t* abb = abb_crear(strcmp , NULL);
    print_test("Prueba crear abb vacio", abb != NULL);
    print_test("Prueba la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("Prueba obtener clave A, es NULL, no existe", abb_obtener(abb, "A") == NULL);
    print_test("Prueba pertenece clave A, es false, no existe", abb_pertenece(abb, "A") == false);
    print_test("Prueba borrar clave A, es NULL, no existe", abb_borrar(abb, "A") == NULL);
    abb_destruir(abb);
}

static void prueba_iterar_abb_vacio(){

    abb_t* abb = abb_crear(strcmp , NULL);
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba iter crear iterador abb vacio", iter != NULL);
    print_test("Prueba iter esta al final", abb_iter_in_al_final(iter));
    print_test("Prueba iter avanzar es false", abb_iter_in_avanzar(iter) == false);
    print_test("Prueba iter ver actual es NULL", abb_iter_in_ver_actual(iter) == NULL);

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

static void prueba_abb_insertar(){

    abb_t* abb = abb_crear(strcmp , NULL);

    char *clave1 = "e", *valor1 = "guau";
    char *clave2 = "b", *valor2 = "miau";
    char *clave3 = "f", *valor3 = "mu";
    char *clave4 = "a", *valor4 = "guau";
    char *clave5 = "d", *valor5 = "miau";
    char *clave6 = "c", *valor6 = "mu";

    print_test("Prueba insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba pertenece clave1, es true", abb_pertenece(abb, clave1));

    print_test("Prueba insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Prueba obtener clave2 es valor2", abb_obtener(abb , clave2) == valor2);
    print_test("Prueba pertenece clave2, es true", abb_pertenece(abb , clave2));

    print_test("Prueba insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba la cantidad de elementos es 3", abb_cantidad(abb) == 3);
    print_test("Prueba obtener clave3 es valor3", abb_obtener(abb , clave3) == valor3);
    print_test("Prueba pertenece clave3, es true", abb_pertenece(abb , clave3));

    print_test("Prueba insertar clave4", abb_guardar(abb, clave4, valor4));
    print_test("Prueba la cantidad de elementos es 4", abb_cantidad(abb) == 4);
    print_test("Prueba obtener clave4 es valor", abb_obtener(abb , clave4) == valor4);
    print_test("Prueba pertenece clave4, es true", abb_pertenece(abb , clave4));

    print_test("Prueba insertar clave5", abb_guardar(abb, clave5, valor5));
    print_test("Prueba la cantidad de elementos es 5", abb_cantidad(abb) == 5);
    print_test("Prueba obtener clave5 es valor5", abb_obtener(abb , clave5) == valor5);
    print_test("Prueba pertenece clave5, es true", abb_pertenece(abb , clave5));

    print_test("Prueba insertar clave6", abb_guardar(abb, clave6, valor6));
    print_test("Prueba la cantidad de elementos es 6", abb_cantidad(abb) == 6);
    print_test("Prueba obtener clave6 es valor6", abb_obtener(abb , clave6) == valor6);
    print_test("Prueba pertenece clave6, es true", abb_pertenece(abb , clave6));

    abb_destruir(abb);
}

static void prueba_abb_reemplazar(){

	abb_t* abb = abb_crear(strcmp , NULL);

    char *clave1 = "perro", *valor1a = "guau", *valor1b = "warf";
    char *clave2 = "gato", *valor2a = "miau", *valor2b = "meaow";

    /* Inserta 2 valores y luego los reemplaza */
    print_test("Prueba insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba obtener clave2 es valor2a", abb_obtener(abb , clave2) == valor2a);
    print_test("Prueba la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba insertar clave1 con otro valor", abb_guardar(abb , clave1, valor1b));
    print_test("Prueba obtener clave1 es valor1b", abb_obtener(abb , clave1) == valor1b);
    print_test("Prueba insertar clave2 con otro valor", abb_guardar(abb , clave2, valor2b));
    print_test("Prueba obtener clave2 es valor2b", abb_obtener(abb , clave2) == valor2b);
    print_test("Prueba la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
}

static void prueba_abb_reemplazar_con_destruir(){

    abb_t* abb = abb_crear(strcmp , free);

    char *clave1 = "perro", *valor1a, *valor1b;
    char *clave2 = "gato", *valor2a, *valor2b;

    /* Pide memoria para 4 valores */
    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));

    /* Inserta 2 valores y luego los reemplaza (debe liberar lo que reemplaza) */
    print_test("Prueba insertar clave1", abb_guardar(abb, clave1, valor1a) == true);
    print_test("Prueba obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba insertar clave2", abb_guardar(abb, clave2, valor2a) == true);
    print_test("Prueba obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    /* Se destruye el abb (se debe liberar lo que quedó dentro) */
    abb_destruir(abb);
}

static void prueba_abb_borrar_general()
{
    abb_t* abb = abb_crear(strcmp , NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    /* Inserta 3 valores y luego los borra */
    print_test("Prueba insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba insertar clave3", abb_guardar(abb, clave3, valor3));

    /* Al borrar cada elemento comprueba que ya no está pero los otros sí. */
    print_test("Prueba pertenece clave3, es verdadero", abb_pertenece(abb, clave3) == true);
    print_test("Prueba borrar clave3, es valor3", abb_borrar(abb, clave3) == valor3);
    print_test("Prueba borrar clave3, es NULL", abb_borrar(abb, clave3) == false);
    print_test("Prueba pertenece clave3, es falso", abb_pertenece(abb, clave3) == false);
    print_test("Prueba obtener clave3, es NULL", abb_obtener(abb, clave3) == NULL);
    print_test("Prueba la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba pertenece clave1, es verdadero", abb_pertenece(abb, clave1) == true);
    print_test("Prueba borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba borrar clave1, es NULL", abb_borrar(abb, clave3) == NULL);
    print_test("Prueba pertenece clave1, es falso", abb_pertenece(abb, clave1) == false);
    print_test("Prueba obtener clave1, es NULL", abb_obtener(abb, clave1) == NULL);
    print_test("Prueba la cantidad de elementos es 1", abb_cantidad(abb) == 1);

    print_test("Prueba pertenece clave2, es verdadero", abb_pertenece(abb, clave2) == true);
    print_test("Prueba borrar clave2, es valor2", abb_borrar(abb, clave2) == valor2);
    print_test("Prueba borrar clave2, es NULL", abb_borrar(abb, clave3) == false);
    print_test("Prueba pertenece clave2, es falso", abb_pertenece(abb, clave2) == false);
    print_test("Prueba obtener clave2, es NULL", abb_obtener(abb, clave2) == NULL);
    print_test("Prueba la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

static void prueba_abb_borrar_casos_borde(){
	abb_t* abb = abb_crear(strcmp, NULL);
	abb_t* abb2 = abb_crear(strcmp, NULL);
	char *clave1 = "p", *valor1 = "guau";
	char *clave2 = "g", *valor2 = "miau";
	char *clave3 = "v", *valor3 = "mu";
	char *clave4 = "r", *valor4 = "chipchip";
	char *clave5 = "m", *valor5 = "uh";
	char *clave6 = "e", *valor6 = "trompeta";
	char *clave7 = "h", *valor7 = "nose";
	char *clave8 = "s", *valor8= "tsss";

	abb_guardar(abb, clave1, valor1);
	abb_guardar(abb, clave2, valor2);
  abb_guardar(abb, clave3, valor3);
	abb_guardar(abb, clave6, valor6);

	/*arbol P G V E*/

	print_test("Borrar G con 1 hijo", abb_borrar(abb, clave2) == valor2);
	print_test("cantidad es 3",abb_cantidad(abb) == 3);
	print_test("Prueba pertenece P, es true", abb_pertenece(abb , clave1));
	print_test("Prueba pertenece E, es true", abb_pertenece(abb , clave6));
	print_test("Prueba pertenece V, es true", abb_pertenece(abb , clave3));
	print_test("Borrar V hoja", abb_borrar(abb, clave3) == valor3);
	print_test("Prueba pertenece E, es true", abb_pertenece(abb , clave1));
	print_test("Prueba pertenece P, es true", abb_pertenece(abb , clave1));
	print_test("cantidad es 2",abb_cantidad(abb) == 2);

	// Árbol P G V R M E H S

	abb_guardar(abb2, clave1, valor1);
	abb_guardar(abb2, clave2, valor2);
  abb_guardar(abb2, clave3, valor3);
	abb_guardar(abb2, clave4, valor4);
	abb_guardar(abb2, clave5, valor5);
	abb_guardar(abb2, clave6, valor6);
	abb_guardar(abb2, clave7, valor7);
	abb_guardar(abb2, clave8, valor8);

	print_test("Borrar P raíz con 2 hijos",abb_borrar(abb2,clave1) == valor1);
	print_test("cantidad es 7",abb_cantidad(abb2) == 7);
	print_test("S hijo derecho de R reemplazante sigue en el arbol", abb_pertenece(abb2,clave8));
	print_test("G hijo izquierdo de P borrado sigue en el arbol", abb_pertenece(abb2,clave2));
	print_test("V hijo derecho de P borrado sigue en el arbol", abb_pertenece(abb2,clave3));
	print_test("Borrar G nodo interno con 2 hijos",abb_borrar(abb2,clave2) == valor2);
	print_test("cantidad es 6",abb_cantidad(abb2) == 6);
	print_test("M hijo derecho de G borrado sigue en el arbol", abb_pertenece(abb2,clave5));
	print_test("E hijo izquierdo de G borrado sigue en el arbol", abb_pertenece(abb2,clave6));

	abb_destruir(abb);
	abb_destruir(abb2);

}

static void prueba_abb_clave_vacia(){

    abb_t* abb = abb_crear(strcmp , NULL);

    char *clave = "", *valor = "";

    print_test("Prueba insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("Prueba la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
    print_test("Prueba pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
    print_test("Prueba la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

static void prueba_abb_valor_null()
{
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = NULL;

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba abb insertar clave vacia valor NULL", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor NULL", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor NULL", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

static void prueba_abb_volumen(size_t largo, bool debug)
{
    abb_t* abb = abb_crear(strcmp,NULL);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    unsigned* valores[largo];

    /* Inserta 'largo' parejas en el abb */
    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int));
        sprintf(claves[i], "%X", i);
        *valores[i] = i;
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb almacenar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    /* Verifica que devuelva los valores correctos */
    for (size_t i = 0; i < largo; i++) {
        ok = abb_pertenece(abb, claves[i]);
        if (!ok) break;
        ok = abb_obtener(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb pertenece y obtener muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    /* Verifica que borre y devuelva los valores correctos */
    for (size_t i = 0; i < largo; i++) {
        ok = abb_borrar(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb borrar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    /* Destruye el abb y crea uno nuevo que sí libera */
    abb_destruir(abb);
    abb = abb_crear(strcmp, free);

    /* Inserta 'largo' parejas en el abb */
    ok = true;
    for (size_t i = 0; i < largo; i++) {
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    free(claves);

    /* Destruye el abb - debería liberar los enteros */
    abb_destruir(abb);

}

static ssize_t buscar(const char* clave, char* claves[], size_t largo)
{
    for (size_t i = 0; i < largo; i++) {
        if (strcmp(clave, claves[i]) == 0) return (ssize_t) i;
    }
    return -1;
}

static void prueba_abb_iterar()
{
    abb_t* abb = abb_crear(strcmp, NULL);

    char *claves[] = {"perro", "gato", "vaca"};
    char *valores[] = {"guau", "miau", "mu"};

    /* Inserta 3 valores */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, claves[0], valores[0]));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, claves[1], valores[1]));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, claves[2], valores[2]));

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    const char *clave;
    ssize_t indice;

    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Primer valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Segundo valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Tercer valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    /* Se anula esta prueba por diferencias de criterios */
    abb_iter_in_avanzar(iter);
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    /* Vuelve a tratar de avanzar, por las dudas */
    print_test("Prueba abb iterador ver actual, es NULL", !abb_iter_in_ver_actual(iter));
    print_test("Prueba abb iterador avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

static void prueba_abb_iterar_volumen(size_t largo)
{
    abb_t* abb = abb_crear(strcmp, NULL);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    size_t valores[largo];

    /* Inserta 'largo' parejas en el abb */
    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        sprintf(claves[i], "%X", i);
        valores[i] = i;
        ok = abb_guardar(abb, claves[i], &valores[i]);
        if (!ok) break;
    }

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    ok = true;
    unsigned i;
    const char *clave;
    size_t *valor;

    for (i = 0; i < largo; i++) {
        if ( abb_iter_in_al_final(iter) ) {
            ok = false;
            break;
        }
        clave = abb_iter_in_ver_actual(iter);
        if ( clave == NULL ) {
            ok = false;
            break;
        }
        valor = abb_obtener(abb, clave);
        if ( valor == NULL ) {
            ok = false;
            break;
        }
        *valor = largo;
        abb_iter_in_avanzar(iter);
    }
    print_test("Prueba abb iteración en volumen", ok);
    print_test("Prueba abb iteración en volumen, recorrio todo el largo", i == largo);
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    ok = true;
    for (i = 0; i < largo; i++) {
        if ( valores[i] != largo ) {
            ok = false;
            break;
        }
    }
    print_test("Prueba abb iteración en volumen, se cambiaron todo los elementos", ok);

    free(claves);
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

//:::::::::PRUEBAS ITERADOR INTERNO:::::::::
bool sumar_elementos(const char* clave, void* dato, void* suma){
  *(int*)suma += *(int*)dato;
  return true;
}

bool sumar_a_dato(const char* clave, void* dato, void* extra){
  *(int*)dato =*(int*)dato+1;
  return true;
}

bool sumar_a_5_datos(const char* clave, void* dato, void* n){
  if(*(int*)n >= 5){
    return false;
  }
  *(int*)dato =*(int*)dato+1;
  *(int*)n =*(int*)n+1;
  return true;
}

bool multiplicar_3_primeros(const char* clave, void* dato, void* extra){
  if(*(int*)dato > 3){
    return false;
  }
  *(int*)dato =*(int*)dato*2;
  return true;
}

bool sumar_primero(const char* clave, void* dato, void* extra){
	if(*(int*)extra == 0){
		*(int*)dato=*(int*)dato+1;
		*(int*)extra=*(int*)extra+1;
		return true;
	}
	return false;
}
void pruebas_iterador_interno_sin_corte_con_extra(){
  abb_t* abb = abb_crear(strcmp, NULL);
	char* claves [10] = {"f","c","h","b","d","g","i","a","e","j"};
  int arr[10] ={6,3,8,2,4,7,9,1,5,10};
  for(int i = 0; i < 10; i++){
    abb_guardar(abb, claves[i], &arr[i]);
  }
  int suma = 0;
  abb_in_order( abb, sumar_elementos, &suma);
  print_test("suma es 55", suma == 55);
  abb_destruir(abb);
}

void pruebas_iterador_interno_sin_corte_sin_extra(){
  abb_t* abb = abb_crear(strcmp,NULL);
	char* claves [10] = {"f","c","h","b","d","g","i","a","e","j"};
  int arr[10] ={6,3,8,2,4,7,9,1,5,10};
  for(int i = 0; i < 10; i++){
    abb_guardar(abb, claves[i], &arr[i]);
  }
  abb_in_order( abb, sumar_a_dato, NULL);
	bool iterar_bien = true;
	abb_iter_t* iter = abb_iter_in_crear(abb);
	if(!iter){
		abb_destruir(abb);
		return;
	}
	int i = 0;
	while(!abb_iter_in_al_final(iter)){
		if(*(int*)abb_obtener(abb,abb_iter_in_ver_actual(iter)) != i+2){
			iterar_bien = false;
		}
		abb_iter_in_avanzar(iter);
		i++;
	}
  print_test("iterador modifico correctamente al abb", iterar_bien);
	abb_iter_in_destruir(iter);
  abb_destruir(abb);
}

void pruebas_iterador_interno_con_corte_con_extra(){
  abb_t* abb = abb_crear(strcmp, NULL);
	char* claves [10] = {"f","c","h","b","d","g","i","a","e","j"};
  int arr[10] ={6,3,8,2,4,7,9,1,5,10};
  for(int i = 0; i < 10; i++){
    abb_guardar(abb, claves[i], &arr[i]);
  }
  int n = 0;
  abb_in_order( abb, sumar_a_5_datos, &n);
  print_test("se itero 5 veces", n == 5);
	bool iterar_bien = true;
	abb_iter_t* iter = abb_iter_in_crear(abb);
	if(!iter){
		abb_destruir(abb);
		return;
	}
	int i = 0;
	while(!abb_iter_in_al_final(iter)){
		if(*(int*)abb_obtener(abb,abb_iter_in_ver_actual(iter)) != i+2 && i < 5){
			iterar_bien = false;
		}
		if(i >= 5 && *(int*)abb_obtener(abb,abb_iter_in_ver_actual(iter)) != i+1){
			iterar_bien = false;
		}
		abb_iter_in_avanzar(iter);
		i++;
	}
	print_test("los elementos fueron modificados correctamente",iterar_bien);
	abb_iter_in_destruir(iter);
  abb_destruir(abb);
}

void pruebas_iterador_interno_con_corte_sin_extra(){
  abb_t* abb = abb_crear(strcmp, NULL);
	char* claves [10] = {"f","c","h","b","d","g","i","a","e","j"};
  int arr[10] ={6,3,8,2,4,7,9,1,5,10};
  for(int i = 0; i < 10; i++){
    abb_guardar(abb, claves[i], &arr[i]);
  }
  abb_in_order(abb, multiplicar_3_primeros, NULL);
	bool iterar_bien = true;
	abb_iter_t* iter = abb_iter_in_crear(abb);
	if(!iter){
		abb_destruir(abb);
		return;
	}
	int i = 0;
	while(!abb_iter_in_al_final(iter)){
		if(*(int*)abb_obtener(abb,abb_iter_in_ver_actual(iter)) != (i+1)*2 && i < 3){
			iterar_bien = false;
		}
		if(i >= 3 && *(int*)abb_obtener(abb,abb_iter_in_ver_actual(iter)) != i+1){
			iterar_bien = false;
		}
		abb_iter_in_avanzar(iter);
		i++;
	}
  print_test("ultimos 7 elementos sin modificar", iterar_bien);
	abb_iter_in_destruir(iter);
  abb_destruir(abb);
}

void prueba_corte_rama_izquierda(){
	abb_t* abb = abb_crear(strcmp, NULL);
	char* claves [10] = {"f","c","h","b","d","g","i","a","e","j"};
	int arr[10] ={6,3,8,2,4,7,9,1,5,10};
	for(int i = 0; i < 10; i++){
		abb_guardar(abb, claves[i], &arr[i]);
	}
	int contador = 0;
	abb_in_order(abb, sumar_primero, &contador);
	bool iterar_bien = true;
	abb_iter_t* iter = abb_iter_in_crear(abb);
	if(!iter){
		abb_destruir(abb);
		return;
	}
	int* receptor = abb_obtener(abb, "a");
	print_test("abb_in_order cambio el valor de \"a\"",*receptor== 2);
	int i = 0;
	abb_iter_in_avanzar(iter);
	i++;
	while(!abb_iter_in_al_final(iter)){
		if(*(int*)abb_obtener(abb,abb_iter_in_ver_actual(iter)) != (i+1)){
			iterar_bien = false;
		}
		abb_iter_in_avanzar(iter);
		i++;
	}
	print_test("resto de los elementos sin modificar", iterar_bien);
	abb_iter_in_destruir(iter);
	abb_destruir(abb);
}

void pruebas_abb_alumno(){

    /* Ejecuta todas las pruebas unitarias. */
    printf("\t\tPRUEBA ABB VACIO\n\n");
    prueba_crear_abb_vacio();
    printf("\n\n\t\tPRUEBA ITERAR ABB VACIO\n\n");
    prueba_iterar_abb_vacio();
    printf("\n\n\t\tPRUEBA ABB INSERTAR\n\n");
    prueba_abb_insertar();
    printf("\n\n\t\tPRUEBA ABB REEMPLAZAR\n\n");
		prueba_abb_reemplazar();
		printf("\n\n\t\tPRUEBA ABB REEMPLAZAR CON DESTRUIR\n\n");
    prueba_abb_reemplazar_con_destruir();
    printf("\n\n\t\tPRUEBA ABB BORRAR\n\n");
    prueba_abb_borrar_general();
		prueba_abb_borrar_casos_borde();
    printf("\n\n\t\tPRUEBA ABB CLAVE VACIA\n\n");
    prueba_abb_clave_vacia();
		printf("\n\n\t\tPRUEBA ABB VALOR NULL\n\n");
		prueba_abb_valor_null();
		printf("\n\n\t\tPRUEBA ABB VOLUMEN\n\n");
    prueba_abb_volumen(5000, true);

		printf("\n\n\t\tPRUEBA ABB ITERADOR EXTERNO\n\n");
    prueba_abb_iterar();
    prueba_abb_iterar_volumen(5000);


		printf("\n\n\t\tPRUEBA ABB ITERADOR INTERNO\n\n");
		pruebas_iterador_interno_sin_corte_con_extra();
		pruebas_iterador_interno_sin_corte_sin_extra();
		pruebas_iterador_interno_con_corte_con_extra();
		pruebas_iterador_interno_con_corte_sin_extra();
		prueba_corte_rama_izquierda();
}
