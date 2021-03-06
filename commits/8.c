#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include "abb.h"
#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include "pila.h"

/*  -Cree 2 funciones de borrar para caso 1 caso 2
    -Al parecer funciona bien, pero falta probar mas casos*/

typedef struct abb_nodo{
  struct abb_nodo* izquierda;
  struct abb_nodo* derecha;
  void* dato;
  char* clave;
}abb_nodo_t;

struct abb{
  abb_nodo_t* raiz;
  abb_destruir_dato_t destruir_dato;
  abb_comparar_clave_t cmp;
  size_t cantidad_nodos;
};

struct abb_iter{
  abb_nodo_t* actual;
  pila_t* pila;
  const abb_t* abb;
};

abb_t *abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
  abb_t* abb = malloc(sizeof(abb_t));
  if(!abb) return NULL;
  abb->raiz = NULL;
  abb->destruir_dato = destruir_dato;
  abb->cmp = cmp; 
  abb->cantidad_nodos = 0;
  return abb;
}

// Crea el nodo en memoria dinamica!
abb_nodo_t* crear_abb_nodo(const char* clave, void*dato){
  abb_nodo_t* nodo = malloc(sizeof(abb_nodo_t));
  if(!nodo) return NULL;
  nodo->izquierda = NULL;
  nodo->derecha = NULL;
  nodo->dato = dato;
  nodo->clave = strdup(clave);
  return nodo;
}

// Recibe la clave a buscar, puntero a abb_nodo_t* osea doble puntero
// Buscar recursivamente por el hijo derecha e izquierda.
// Devuelve un puntero hacia donde se deberia insertar
// ese puntero deberia estar apuntando hacia NULL *arbol_devuelto == NULL  en caso contrario *arbol_devuelto != NULL . La clave buscada ya existia y devuelve el puntero a su ubicacion.
// Funcion utilizada en guardar, obtener, pertence.

abb_nodo_t** buscar_arbol(const char* clave, abb_nodo_t** arbol, abb_comparar_clave_t cmp) {
  if (!(*arbol)) {
    return arbol;
  }
  abb_nodo_t** aux = NULL ;
  if(cmp((*arbol)->clave, clave) < 0){  // a < b 
    if(!(*arbol)->derecha) return &(*arbol)->derecha;
    else aux = buscar_arbol(clave, &(*arbol)->derecha, cmp);
  }
  
  if(cmp((*arbol)->clave, clave) > 0){ // a > b
    if(!(*arbol)->izquierda) return &(*arbol)->izquierda;
    else aux = buscar_arbol(clave, &(*arbol)->izquierda, cmp);
  }
  if(cmp((*arbol)->clave, clave) == 0){
    return arbol;
  }
  return aux;
}
// Funcion que me sirvio para comprobar los casos de borrados y probar el abb_destruir 
// no tiene mas utilidad, no se debe usar
void in_order(abb_nodo_t** arbol){
  if (!*arbol) return; 
  in_order(&(*arbol)->izquierda);
  char* a = (*arbol)->clave;
  printf(" %s \n", a);
  in_order(&(*arbol)->derecha);
}
// Funcion provisional que testea el borrado. NO SE USA MAS.
void imprimir_in(abb_t* abb){
  in_order(&abb->raiz);
}

bool abb_guardar(abb_t *abb, const char *clave, void *dato){
  abb_nodo_t** arbol = buscar_arbol(clave, &abb->raiz, abb->cmp); 
  if (!*arbol){
    *arbol = crear_abb_nodo(clave, dato);
    abb->cantidad_nodos++;
  }
  else {
    if (abb->destruir_dato) abb->destruir_dato((*arbol)->dato);
    (*arbol)->dato = dato;
  }
  if (!*arbol) return false;  
  return true;
}

// Funcion que calcula el el nodo con valor minimo 
// Recibe puntero a un nodo arbol (no un arbol en si ya que se necesita modificar)
// Devuelve un puntero a el nodo arbol mas chico
// Funcion necesaria para borrar 
abb_nodo_t** min(abb_nodo_t** arbol, abb_comparar_clave_t cmp){ //2 //3
  abb_nodo_t** aux = arbol;
  if(!(*arbol)->izquierda) return aux;
  if (!(*arbol)->izquierda->izquierda) return aux;//2//3
  aux =  min(&(*arbol)->izquierda, cmp); //1ra// 
  return aux;
}

// caso 1 borrar hoja
// funciona nueva borra un nodo que notiene hijos 
void* caso_1(abb_nodo_t** arbol){
  void* dato_salida;
  dato_salida = (*arbol)->dato;
  free((*arbol)->clave);
  free(*arbol);
  *arbol = NULL;
  return dato_salida;
}

// Funcion del 2do caso de borrado (el arbol tiene hijo derecho o hijo izquierdo).
// Recibe puntero al arbol y un abb 
// Contempla los 2 casos y devuelve el dato asociado a la clave .  
void* caso_2(abb_nodo_t** arbol, abb_t* abb){
  void* dato_salida = NULL;
  if((*arbol)->derecha && !(*arbol)->izquierda) { /* 3er caso   */
    dato_salida = (*arbol)->dato;
    (*arbol)->izquierda = (*arbol)->derecha->izquierda; //distinto
    (*arbol)->dato = (*arbol)->derecha->dato; //distinto
    free((*arbol)->clave);
    (*arbol)->clave = strdup((*arbol)->derecha->clave);
    free((*arbol)->derecha->clave);
    abb_nodo_t* cis = (*arbol)->derecha;
    (*arbol)->derecha = cis->derecha;
    free(cis);
    abb->cantidad_nodos--;
    return dato_salida;
  }
  if (!(*arbol)->derecha && (*arbol)->izquierda){
    dato_salida = (*arbol)->dato ;
    (*arbol)->derecha = (*arbol)->izquierda->derecha; // distinto
    (*arbol)->dato = (*arbol)->izquierda->dato;//distinto
    free((*arbol)->clave);
    (*arbol)->clave = strdup((*arbol)->izquierda->clave);
    free((*arbol)->izquierda->clave);
    abb_nodo_t* nodo_a_borrar = (*arbol)->izquierda;
    (*arbol)->izquierda = nodo_a_borrar->izquierda;
    free(nodo_a_borrar);
    abb->cantidad_nodos--;
    return dato_salida;
  }
  return dato_salida;
}

// Trate de implementarlo de la otra manera, pero me dio muchos errores
void *abb_borrar(abb_t *abb, const char *clave){
  if(!abb->raiz) return NULL;
  abb_nodo_t** arbol = buscar_arbol(clave, &abb->raiz, abb->cmp);
  if (!(*arbol)) return NULL;
  void* dato_salida = NULL;

  /* primer caso : borrar una hoja*/
  if(!(*arbol)->derecha && !(*arbol)->izquierda){
    dato_salida = caso_1(arbol);
    abb->cantidad_nodos--;
    return dato_salida;
  }
  
  /* segundo caso : 1 hijo */
  if(!(*arbol)->derecha || !(*arbol)->izquierda){
    dato_salida = caso_2(arbol, abb);
    return dato_salida;
  }
  /* tercer caso : 2 hijos  */
  if((*arbol)->derecha && (*arbol)->izquierda){
    dato_salida = (*arbol)->dato;
    abb_nodo_t** padre_minimo = min(&(*arbol)->derecha, abb-> cmp);
    if(!(*padre_minimo)->izquierda) {
      abb_nodo_t* derecha_padre_minimo = (*padre_minimo)->derecha;  
      (*arbol)->dato = (*padre_minimo)->dato; 
      free((*arbol)->clave);
      (*arbol)->clave = strdup((*padre_minimo)->clave);
      free((*padre_minimo)->clave);
      free(*padre_minimo);
      (*arbol)->derecha = derecha_padre_minimo;
      abb->cantidad_nodos--;
      return dato_salida;
    }
    
    (*arbol)->dato = (*padre_minimo)->izquierda->dato;
    free((*arbol)->clave);
    (*arbol)->clave = strdup((*padre_minimo)->izquierda->clave);
    abb_nodo_t* derecha_minimo = (*padre_minimo)->izquierda->derecha; 
    abb_nodo_t* nodo_a_borrar = (*padre_minimo)->izquierda;
    (*padre_minimo)->izquierda->derecha = (*arbol)->derecha;
    (*padre_minimo)->izquierda = derecha_minimo;
    free(nodo_a_borrar->clave);
    free(nodo_a_borrar);
    abb->cantidad_nodos--;
    
    return dato_salida;
  } 
  return dato_salida;
}

void *abb_obtener(const abb_t *abb, const char *clave){
  if (abb->cantidad_nodos == 0) return NULL;
  abb_nodo_t* raiz = abb->raiz;
  abb_nodo_t** arbol = buscar_arbol(clave, &raiz, abb->cmp);
  if (*arbol){
    raiz = *arbol;
    return  raiz->dato;
  }  
  return NULL;
}

bool abb_pertenece(const abb_t *abb, const char *clave){
  if (abb->cantidad_nodos == 0) return false;
  abb_nodo_t* raiz = abb->raiz;
  abb_nodo_t** arbol = buscar_arbol(clave, &raiz, abb->cmp);
  if (*arbol) return true;
  return false;

}

size_t abb_cantidad(const abb_t *abb){
  return  abb->cantidad_nodos  ;
}



void abb_destruir(abb_t *abb){
  //int*a ;
  while(abb->cantidad_nodos != 0){
    //printf("RAIZ A BORRAR ES  es %s \n", abb->raiz->clave);
   // printf("IN ORDER: \n");
    //imprimir_in(abb);
    abb_borrar(abb, abb->raiz->clave);   
  }
  free(abb);
}

/* Iterador del hash */

void apilar_nodos(abb_iter_t* iter, abb_nodo_t* arbol){
  if (!arbol) return ;
  pila_apilar(iter->pila, arbol);
  apilar_nodos(iter, arbol->izquierda);
}

// Crea iterador
abb_iter_t *abb_iter_in_crear(const abb_t *abb){
  abb_iter_t* iter = malloc(sizeof(abb_iter_t));
  if (!iter) return NULL;
  iter->abb = abb;
  iter->pila = pila_crear(); 
  if (abb->cantidad_nodos == 0) return iter;
  apilar_nodos(iter, abb->raiz);
  return iter;
  //return NULL;
}

// Avanza iterador
bool abb_iter_in_avanzar(abb_iter_t *iter){
  if(abb_iter_in_al_final(iter)) return false;
  abb_nodo_t* desapilado  = pila_desapilar(iter->pila);
  if(desapilado->derecha) apilar_nodos(iter, desapilado->derecha);
  return true;
}

// Devuelve clave actual, esa clave no se puede modificar ni liberar.
const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
  abb_nodo_t* aux = pila_ver_tope(iter->pila);
  return aux ? aux->clave : NULL;
}

// Comprueba si terminó la iteración

bool abb_iter_in_al_final(const abb_iter_t *iter){
  return pila_esta_vacia(iter->pila);
}

// Destruye iterador
void abb_iter_in_destruir(abb_iter_t* iter){
  pila_destruir(iter->pila);
  free(iter);
}

void in_orden(abb_nodo_t* arbol,bool visitar(const char *clave, void *dato, void *extra), void* extra ){
  if (!arbol) return; 
  in_orden(arbol->izquierda, visitar, extra);
  if(!visitar(arbol->clave, arbol->dato, extra)) return;
  in_orden(arbol->derecha, visitar, extra);
}
  
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
  in_orden(arbol->raiz, visitar, extra);
}
