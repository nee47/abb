#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include "abb.h"
#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>

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

// Recibe la clave a buscar, puntero a abb_nodo_t* osea doble puntero
// Buscar recursivamente por el hijo derecha e izquierda.
// Devuelve un puntero hacia donde se deberia insertar
// ese puntero deberia estar apuntando hacia NULL *arbol_devuelto == NULL  en caso contrario *arbol_devuelto != NULL . La clave buscada ya existia y devuelve el puntero a su ubicacion.
// Funcion utilizada en guardar, obtener, pertence.

abb_nodo_t** buscar_arbol(const char* clave, abb_nodo_t** arbol, abb_cmp_t cmp) {
  if (!(*arbol)) {
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

void in_order(abb_nodo_t** arbol){
  if (!*arbol) return; 
  in_order(&(*arbol)->izquierda);
  int* a = (*arbol)->dato;
  printf(" %d \n", *a);
  in_order(&(*arbol)->derecha);
}

void imprimir_in(abb_t* abb){

  in_order(&abb->raiz);
  /*
  char* c = abb->raiz->clave;

  printf("nodo 1  es %s \n", c);
  c = abb->raiz->izquierda->clave;
  printf("nodo 2 es %s \n", c);
  c = abb->raiz->derecha->clave;
  printf("nodo 3 es %s \n", c);
  c = abb->raiz->izquierda->izquierda->clave;
  printf("nodo 4 es %s \n", c);
  c = abb->raiz->derecha->izquierda->clave;
  printf("nodo 5 es %s \n", c);
  c = abb->raiz->derecha->izquierda->derecha->clave;
  printf("nodo 6 es %s \n", c);
  //c = abb->raiz->derecha->izquierda->derecha->derecha->clave;
  //printf("nodo 7 es %s \n", c);
  */
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
abb_nodo_t** min(abb_nodo_t** arbol, abb_cmp_t cmp){ //2 //3
  abb_nodo_t** aux = arbol;
  if(!(*arbol)->izquierda) return aux;
  if (!(*arbol)->izquierda->izquierda) return aux;//2//3
  aux =  min(&(*arbol)->izquierda, cmp); //1ra// 
  return aux;
}

// Funcion del 2do caso de borrado (el arbol tiene hijo derecho o hijo izquierdo).
// Recibe puntero al arbol y un abb 
// Contempla los 2 casos y devuelve el dato asociado a la clave .  
void* salida(abb_nodo_t** arbol, abb_t* abb){
  void* dato_salida = NULL;
  if((*arbol)->derecha && !(*arbol)->izquierda) { /* 2do caso   */
    dato_salida = (*arbol)->dato;
    (*arbol)->izquierda = (*arbol)->derecha->izquierda; //distinto
    (*arbol)->dato = (*arbol)->derecha->dato; //distinto
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
    (*arbol)->derecha = (*arbol)->izquierda->derecha; // distinto
    (*arbol)->dato = (*arbol)->izquierda->dato;//distinto
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

// MODIFIQUE EL PRIMER CASO DE BORRAR (EL MAS DIFICIL)
// DENTRO DEL PRIMER CASO TAMBIEN HAY OTRO CASO PARTICULAR
// RESUELTO
void *abb_borrar(abb_t *abb, const char *clave){
  if(!abb->raiz) return NULL;
  abb_nodo_t** arbol = buscar_arbol(clave, &abb->raiz, abb->cmp);
  if (!(*arbol)) return NULL;
  void* dato_salida = NULL;
  /* primer caso */
  if((*arbol)->derecha && (*arbol)->izquierda){
    dato_salida = (*arbol)->dato;
    abb_nodo_t** padre_minimo = min(&(*arbol)->derecha, abb-> cmp);
    if(!(*padre_minimo)->izquierda) {
      abb_nodo_t* derecha_padre_minimo = (*padre_minimo)->derecha;
      printf("papa de MINIMON ES  %s \n", (*padre_minimo)->clave);
      (*arbol)->dato = (*padre_minimo)->dato; 
      free((*arbol)->clave);
      (*arbol)->clave = strdup((*padre_minimo)->clave);
      free((*padre_minimo)->clave);
      free(*padre_minimo);
      (*arbol)->derecha = derecha_padre_minimo;
      abb->cantidad_nodos--;
      return dato_salida;
    }
    printf("MINIMON ES  %s \n", (*padre_minimo)->izquierda->clave);
    (*arbol)->dato = (*padre_minimo)->izquierda->dato;
    free((*arbol)->clave);
    (*arbol)->clave = strdup((*padre_minimo)->izquierda->clave);
    //free((*padre_minimo)->izquierda->clave);
    abb_nodo_t* derecha_minimo = (*padre_minimo)->izquierda->derecha; 
    abb_nodo_t* nodo_a_borrar = (*padre_minimo)->izquierda;
    (*padre_minimo)->izquierda->derecha = (*arbol)->derecha;
    (*padre_minimo)->izquierda = derecha_minimo;
    free(nodo_a_borrar->clave);
    free(nodo_a_borrar);
    abb->cantidad_nodos--;
    return dato_salida;
  } 

  if(!(*arbol)->derecha && !(*arbol)->izquierda){  /* segundo caso  */
    dato_salida = (*arbol)->dato;
    free((*arbol)->clave);
    free(*arbol);
    *arbol = NULL;
    abb->cantidad_nodos-- ;
    return dato_salida;
  }
  /* tercer caso   */
  dato_salida = salida(arbol, abb);
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
    printf("RAIZ A BORRAR ES  es %s \n", abb->raiz->clave);
    printf("IN ORDER: \n");
    imprimir_in(abb);
    abb_borrar(abb, abb->raiz->clave);
    
  }
  free(abb);
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
