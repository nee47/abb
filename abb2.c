#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include "abb.h"
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

typedef struct abb_nodo{
  struct abb_nodo* izquierda;
  struct abb_nodo* derecha;
  void* dato;
  char* clave;
}abb_nodo_t;

struct abb{
  abb_nodo_t* raiz;
  abb_destruir_dato_t destruir_dato;
  abb_cmp_t cmp;
  size_t cantidad_nodos;
};

abb_t *abb_crear(abb_destruir_dato_t destruir_dato, abb_cmp_t abb_cmp){
  abb_t* abb = malloc(sizeof(abb_t));
  if(!abb) return NULL;
  abb->raiz = NULL;
  abb->destruir_dato = destruir_dato;
  abb->cmp = abb_cmp; 
  abb->cantidad_nodos = 0;
  return abb;
}

abb_nodo_t* crear_abb_nodo(const char* clave, void*dato){
  abb_nodo_t* nodo = malloc(sizeof(abb_nodo_t));
  if(!nodo) return NULL;
  nodo->izquierda = NULL;
  nodo->derecha = NULL;
  nodo->dato = dato;
  nodo->clave = strdup(clave);
  return nodo;
}


abb_nodo_t** buscar_arbol(const char* clave, abb_nodo_t** arbol, abb_cmp_t cmp) {
  if (!*arbol) {
    return arbol;
  }
  abb_nodo_t** aux = NULL ;
  if(cmp((*arbol)->clave, clave) == -1){  // a < b 
    if(!(*arbol)->derecha) return &(*arbol)->derecha;
    else aux = buscar_arbol(clave, &(*arbol)->derecha, cmp);
  }
  
  if(cmp((*arbol)->clave, clave) == 1){ // a > b
    if(!(*arbol)->izquierda) return &(*arbol)->izquierda;
    else aux = buscar_arbol(clave, &(*arbol)->izquierda, cmp);
  }
  if(cmp((*arbol)->clave, clave) == 0){
    return arbol;
  }
  return aux;
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


abb_nodo_t** min(abb_nodo_t** arbol, abb_cmp_t cmp){ //2 //3
  if (!(*arbol)->izquierda) return arbol;//2//3
  abb_nodo_t** aux =  min(&(*arbol)->izquierda, cmp); //1ra// 
  return aux;
}


    
void *abb_borrar(abb_t *abb, const char *clave){
  if(!abb->raiz) return NULL;
  abb_nodo_t** arbol = buscar_arbol(clave, &abb->raiz, abb->cmp);
  if (!(*arbol)) return NULL;
  void* dato_salida = NULL;
  if((*arbol)->derecha && (*arbol)->izquierda){
    dato_salida = (*arbol)->dato;
    abb_nodo_t** cc = min(&(*arbol)->derecha, abb->cmp);
    (*arbol)->dato = (*cc)->dato;
    free((*arbol)->clave);
    (*arbol)->clave = strdup((*cc)->clave);
    free((*cc)->clave);
    free(*cc);
    *cc = NULL;
    abb->cantidad_nodos-- ;
    return dato_salida;
  } //tercer caso

  if(!(*arbol)->derecha && !(*arbol)->izquierda){  /* primer caso  */
    dato_salida = (*arbol)->dato;
    free((*arbol)->clave);
    free(*arbol);
    *arbol = NULL;
    abb->cantidad_nodos-- ;
    return dato_salida;
  }
  
  if((*arbol)->derecha && !(*arbol)->izquierda) { /* 2do caso   */
    dato_salida = (*arbol)->dato;
    (*arbol)->izquierda = (*arbol)->derecha->izquierda;
    (*arbol)->dato = (*arbol)->derecha->dato;
    free((*arbol)->clave);
    (*arbol)->clave = strdup((*arbol)->derecha->clave);
    free((*arbol)->derecha->clave);
    abb_nodo_t* cis = (*arbol)->derecha;
    (*arbol)->derecha = (*arbol)->derecha->derecha;
    free(cis);
    abb->cantidad_nodos--;
    return dato_salida;
  }
  if (!(*arbol)->derecha && (*arbol)->izquierda){
    dato_salida = (*arbol)->dato ;
    (*arbol)->derecha = (*arbol)->izquierda->derecha;
    (*arbol)->dato = (*arbol)->izquierda->dato;
    free((*arbol)->clave);
    (*arbol)->clave = strdup((*arbol)->izquierda->clave);
    free((*arbol)->izquierda->clave);
    abb_nodo_t* ac = (*arbol)->izquierda;
    (*arbol)->izquierda = (*arbol)->izquierda->izquierda;
    free(ac);
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
  return  abb->cantidad_nodos ;
}


void abb_destruir(abb_t *abb){
  

}

/* Iterador del hash */

// Crea iterador
abb_iter_t *abb_iter_crear(const abb_t *abb);

// Avanza iterador
bool abb_iter_avanzar(abb_iter_t *iter);

// Devuelve clave actual, esa clave no se puede modificar ni liberar.
const char *abb_iter_ver_actual(const abb_iter_t *iter);

// Comprueba si terminó la iteración

bool abb_iter_al_final(const abb_iter_t *iter);

// Destruye iterador
void abb_iter_destruir(abb_iter_t* iter);
