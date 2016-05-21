
#include <stdio.h>
#include "testing.h"
#include "heap.h"
#include <stdlib.h>
#define VOL 7000
#define INI 10

int** vector_crear(){
  int** vector = malloc(sizeof(int) * INI);
  if (!vector) return NULL;
  for(size_t a = 0; a < INI;a++){
    vector[a] = malloc(sizeof(int));   
  }
  
  return vector;  
 
}



int comparar(const void* a , const void* b){
  const size_t* a1 = a;
  const size_t* b1 = b;

  if(*a1 > *b1) return 1;
  if(*a1 < *b1) return -1;
  return 0;
}

void heap_vacio(){
  heap_t* heap = heap_crear(comparar);
  //printf("insertadp")
  print_test("heap creado ", heap);
  print_test("heap  esta vacio", heap_esta_vacio(heap));
  print_test("heap cantidad es 0 ", heap_cantidad(heap) == 0);
  print_test("heap ver max es NULL", !heap_ver_max(heap));
  print_test("heap desencolar es NNULL", !heap_desencolar(heap));
  heap_destruir(heap, NULL);
}


void heap_encolar_desencolar(){
  heap_t* heap = heap_crear(comparar);
  size_t a = 1, b = 2, c = 3, d = 4, e = 5, f = 6; 
  //printf("insertadp")
  print_test("heap creado ", heap);
  print_test("heap encolar 1 ", heap_encolar(heap, &a));
  print_test("heap no esta vacio", !heap_esta_vacio(heap));
  print_test("heap cantidad es 1 ", heap_cantidad(heap) == 1);
  print_test("heap ver max es 1", *(size_t*)heap_ver_max(heap) == a);
  print_test("heap encolar 2", heap_encolar(heap, &b));
  print_test("heap cantidad es 2 ", heap_cantidad(heap) == 2);
  print_test("heap ver max es 2", *(size_t*)heap_ver_max(heap) == b);

  print_test("heap encolar 3", heap_encolar(heap, &c));
  print_test("heap cantidad es 3 ", heap_cantidad(heap) == 3);
  print_test("heap ver max es 3", *(size_t*)heap_ver_max(heap) == c);
  print_test("heap encolar 4 ", heap_encolar(heap, &d));
  print_test("heap cantidad es 4 ", heap_cantidad(heap) == d);
  print_test("heap ver max es 4", *(size_t*)heap_ver_max(heap) == d);
  print_test("heap encolar 5", heap_encolar(heap, &e));
  print_test("heap cantidad es 5 ", heap_cantidad(heap) == 5);
  print_test("heap ver max es 5", *(size_t*)heap_ver_max(heap) == e);
  print_test("heap encolar 6 ", heap_encolar(heap, &f));
  print_test("heap cantidad es 6 ", heap_cantidad(heap) == 6);
  print_test("heap ver max es 6", *(size_t*)heap_ver_max(heap) == f);
  heap_destruir(heap, NULL);
  heap_t* jip = heap_crear(comparar);
  
  a = 1, b = 50, c = 26, d = 31, e = 64, f = 59;
  print_test("heap creado ", jip);
  print_test("heap encolar 1 ", heap_encolar(jip, &a));
  print_test("heap no esta vacio", !heap_esta_vacio(jip));
  print_test("heap cantidad es 1 ", heap_cantidad(jip) == 1);
  print_test("heap ver max es 1", *(size_t*)heap_ver_max(jip) == a);
  print_test("heap encolar 50", heap_encolar(jip, &b));
  print_test("heap cantidad es 2 ", heap_cantidad(jip) == 2);
  print_test("heap ver max es 50", *(size_t*)heap_ver_max(jip) == b);

  print_test("heap encolar 26", heap_encolar(jip, &c));
  print_test("heap cantidad es 3 ", heap_cantidad(jip) == 3);
  //printf("heap ver max es %zu pero deberia ser 50", *(size_t*)heap_ver_max(jip));
  print_test("heap ver max es 50", *(size_t*)heap_ver_max(jip) == b);
  print_test("heap encolar 31 ", heap_encolar(jip, &d));
  print_test("heap cantidad es 4 ", heap_cantidad(jip) == 4);
  print_test("heap ver max es 50", *(size_t*)heap_ver_max(jip) == b);
  print_test("heap encolar 64", heap_encolar(jip, &e));
  print_test("heap cantidad es 5 ", heap_cantidad(jip) == 5);
  print_test("heap ver max es 64", *(size_t*)heap_ver_max(jip) == e);
  print_test("heap encolar 59 ", heap_encolar(jip, &f));
  print_test("heap cantidad es 6 ", heap_cantidad(jip) == 6);
  print_test("heap ver max es 64", *(size_t*)heap_ver_max(jip) == e); 
  print_test("heap desencolar es 64 ", *(size_t*)heap_desencolar(jip) == 64);
  print_test("heap desencolar es 59 ", *(size_t*)heap_desencolar(jip) == 59);
  print_test("heap desencolar es 50 ", *(size_t*)heap_desencolar(jip) == 50);
  print_test("heap desencolar es 31 ", *(size_t*)heap_desencolar(jip) == 31);
  print_test("heap desencolar es 26 ", *(size_t*)heap_desencolar(jip) == 26);
  print_test("heap desencolar es 1 ", *(size_t*)heap_desencolar(jip) == 1);
  print_test("heap desencolar es NULL ", !heap_desencolar(jip));
 

  heap_destruir(jip, NULL);
  
  heap = heap_crear(comparar);
  a = 10, b= 60, c=30, d=46, e=60, f=23; 
  size_t** vec = malloc(sizeof(size_t*) * 6) ;
  vec[0] = &a ;
  vec[1] = &b;
  vec[2] = &c;
  vec[3] = &d;
  vec[4] = &e;
  vec[5] = &f;
  
  jip =  heap_crear_arr((void**)vec, 6, comparar);
  // 10 23 30 46 60  60 
  printf("Vector :\n");
  for(size_t i = 0; i < 6; i++){
    printf("vec[%zu] : %zu\n",i ,*vec[i]);
  }
  int vector_ordenado[6] = {10, 23,30,46,60,60};
  printf("Prueba ordenamiento con heap (Heapsort)\n");
  heap_sort((void**)vec, 6, comparar);
  bool ok = true;
  
  printf("Vector ORDENADO CON HEAPSORT EN O(nlogn) :\n");
  for(size_t i = 0; i < 6; i++){
    ok = *vec[i] == vector_ordenado[i] ? true: false;
    if(!ok) break;
  }
  
  print_test("El vector ha sido ordenado exitosamente", ok);
  
  for(size_t i = 0; i < 6; i++){
    printf("vec[%zu] : %zu\n",i ,*vec[i]);
  }

  free(vec);
  heap_destruir(heap, NULL);
  heap_destruir(jip, NULL);
  /* 
  heap = heap_crear(comparar);
  int x=0,y=3;
  int** v1 = malloc(sizeof(int)) ;
  *v1 = &y;
  int** v2 = malloc(sizeof(int));
  *v2 = &x;
  print_test("insertar valor 1 en memoria dinamica", heap_encolar(heap,v1));
  print_test("insertar valor 2 en memoria dinamica", heap_encolar(heap, v2));
  heap_destruir(heap, free);
  */
}

void heap_volumen(){
  heap_t* heap = heap_crear(comparar);
  bool ok;
  size_t i ;
  size_t vector[VOL];
  for( i = 0; i < VOL; i++){
    vector[i] = i;
    ok = heap_encolar(heap, &vector[i]);  
    if(!ok) break;
  }
  print_test("Encole todos los elementos",ok);

  for( i = 0; i < VOL; i++){
    ok = (*(size_t*)heap_desencolar(heap) == vector[VOL-i-1]) ? true : false ;    if (!ok) break;
  }
  
  print_test("Desencole en orden ",ok);
  heap_destruir(heap, NULL);
}

void ordenar(){
  // 1,3,5,7,9,11  FALLA
  // 
  size_t a=33, b=77, c=66, d=55, e=44, f=99;
  size_t* vector[6] = {&a,&b,&c,&d,&e,&f};
  heap_sort((void**)vector, 6, comparar);
  size_t vector_ordenado[6] = {33,44,55,66,77,99};
  print_test("COMPARADO ", *vector[0] == vector_ordenado[0]);
  print_test("COMPARADO ", *vector[1] == vector_ordenado[1]);
  print_test("COMPARADO ", *vector[2] == vector_ordenado[2]);
  print_test("COMPARADO ", *vector[3] == vector_ordenado[3]);
  print_test("COMPARADO ", *vector[4] == vector_ordenado[4]);
  print_test("COMPARADO ", *vector[5] == vector_ordenado[5]);
  
}

void pruebas_heap_alumno(){
  heap_vacio();
  heap_encolar_desencolar();
  heap_volumen();
  ordenar();
}
