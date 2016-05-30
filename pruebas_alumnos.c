#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <string.h>
#include "abb.h"
#include <stdio.h>
#include "testing.h"
#include <time.h>
#define TAM 9000

int comparar(const char* cadena1, const char* cadena2){
  long int cad1, cad2;
  cad1 = strtol(cadena1, NULL, 10);
  cad2 = strtol(cadena2, NULL, 10);
  if(cad1 > cad2) return 1;
  if(cad1 < cad2) return -1;
  else return 0;
}

char** crear_vector_cadenas(size_t largo){
  size_t a, r ;
  char cad[13];
  srand((unsigned int)time(NULL));
  char** vector = malloc(sizeof(char*) * largo);
  for( a = 0; a < largo; a++){
    r = rand();
    snprintf(cad, sizeof(cad),"%zu", r );
    vector[a] = strdup(cad);
  }
  return vector;
}

void liberar_cadenas(char** vec){
  size_t a;
  for( a = 0; a < TAM; a++){
    free(vec[a]);
  }
  free(vec);
}

void pruebas_vacia(){
  printf("Inicio de pruebas con abb vacio \n");
  abb_t* abb = abb_crear(comparar, NULL);
  
  print_test("abb vacio creado", abb);
  print_test("abb cantidad de nodos es 0 ", abb_cantidad(abb) == 0);
  print_test("abb obtener clave 'clave' es NULL", !abb_obtener(abb, "clave"));
  print_test("abb borrar clave 'clave' es NULL", !abb_borrar(abb, "clave"));
  print_test("abb pertenece 'clave' es false", !abb_pertenece(abb, "clave"));
  
  abb_destruir(abb);
  
}

void pruebas_guardar(){
  
  abb_t* abb = abb_crear(comparar, NULL);
  
  int c1 = 14, c2 = 95, c3 = 11, c4 = 46, c5 = 85, c6 = 90, c7 = 3;
  printf("Insercion de distintos arboles\n");
  print_test("abb vacio creado", abb);
  print_test("abb insertar 14 ", abb_guardar(abb, "14", &c1));
  print_test("14 pertenece",abb_pertenece(abb, "14"));
  print_test("cantidad es 1", abb_cantidad(abb) == 1 );
  print_test("abb obtener clave 14 ", *(int*)abb_obtener(abb, "14")== c1);
  print_test("abb insertar 95", abb_guardar(abb, "95", &c2));
  print_test("95 pertenece", abb_pertenece(abb, "95"));
  print_test("cantidad es 2", abb_cantidad(abb) == 2 );
  print_test("abb obtener clave 95 ", *(int*)abb_obtener(abb, "95")== c2);
  print_test("abb insertar 11", abb_guardar(abb, "11", &c3));
  print_test("11 pertenece",abb_pertenece(abb, "11"));
  print_test("cantidad es 3", abb_cantidad(abb) == 3 );
  print_test("abb obtener clave 11 ", *(int*)abb_obtener(abb, "11")== c3);
  print_test("abb insertar 46", abb_guardar(abb, "46", &c4));
  print_test("46 pertenece",abb_pertenece(abb, "46"));
  print_test("cantidad es 4", abb_cantidad(abb) == 4 );
  print_test("abb obtener clave 46 ", *(int*)abb_obtener(abb, "46")== c4);
  print_test("abb insertar 85", abb_guardar(abb, "85", &c5));
  print_test("abb insertar 90", abb_guardar(abb, "90", &c6));
  print_test("abb insertar 3", abb_guardar(abb, "3", &c7));
  print_test("cantidad elementos es 7", abb_cantidad(abb) == 7);
  
  abb_destruir(abb);
  print_test("arbol destruido", true);
  
  abb = abb_crear(comparar, NULL);
  
  c1 = 50; c2 = 75; c3 = 25; c4 = 10; c5 = 34; c6 = 64; c7 = 90;
  // 14  95  11  46  85  90 3
  print_test("abb vacio creado", abb);
  print_test("abb insertar 50 ", abb_guardar(abb, "50", &c1));
  print_test("abb insertar 75", abb_guardar(abb, "75", &c2));
  print_test("abb insertar 25", abb_guardar(abb, "25", &c3));
  print_test("abb insertar 10", abb_guardar(abb, "10", &c4));
  print_test("abb insertar 34", abb_guardar(abb, "34", &c5));
  print_test("abb insertar 64", abb_guardar(abb, "64", &c6));
  print_test("abb insertar 90", abb_guardar(abb, "90", &c7));
  print_test("cantidad elementos es 7", abb_cantidad(abb) == 7);
  
  //print_test("")
  abb_destruir(abb);
  print_test("arbol destruido", true);
  
  c1 = 15; c2 = 23; c3 = 50; c4 = 40; c5 = 32; c6 = 45; c7 = 90;
  abb = abb_crear(comparar, NULL);
  print_test("abb insertar 15 ", abb_guardar(abb, "15", &c1));
  print_test("abb insertar 23", abb_guardar(abb, "23", &c2));
  print_test("abb insertar 50", abb_guardar(abb, "50", &c3));
  print_test("abb insertar 40", abb_guardar(abb, "40", &c4));
  print_test("abb insertar 32", abb_guardar(abb, "32", &c5));
  print_test("abb insertar 45", abb_guardar(abb, "45", &c6));
  
  abb_destruir(abb);
  
  abb = abb_crear(comparar, NULL);
  print_test("abb insertar  ", abb_guardar(abb, "15", &c1));
  print_test("abb insertar ", abb_guardar(abb, "23", &c2));
  print_test("abb insertar ", abb_guardar(abb, "50", &c3));
  print_test("abb insertar ", abb_guardar(abb, "50", &c3));
  print_test("abb insertar ", abb_guardar(abb, "70", &c3));
  
  abb_destruir(abb);
  
  abb = abb_crear(comparar, free);
  
  int* i1 = malloc(sizeof(int));
  * i1 = 3;
  //i1 = &i2;
  abb_guardar(abb, "14", i1);

  abb_destruir(abb);
}

void pruebas_borrar(){
  abb_t* abb = abb_crear(comparar, NULL);
  
  int c1 = 14, c2 = 95, c3 = 11, c4 = 46, c5 = 85, c6 = 90, c7 = 3;
  print_test("abb vacio creado", abb);
  print_test("abb insertar 14 ", abb_guardar(abb, "14", &c1));
  print_test("abb insertar 95", abb_guardar(abb, "95", &c2));
  print_test("abb insertar 11", abb_guardar(abb, "11", &c3));
  print_test("abb insertar 46", abb_guardar(abb, "46", &c4));
  print_test("abb insertar 85", abb_guardar(abb, "85", &c5));
  print_test("abb insertar 90", abb_guardar(abb, "90", &c6));
  print_test("abb insertar 3", abb_guardar(abb, "3", &c7));
  print_test("cantidad elementos es 7", abb_cantidad(abb) == 7);

  print_test("abb borrar clave 14  devuelve 14", *(int*)abb_borrar(abb, "14")== c1);
  print_test("clave 14 ya no pertenece ", !abb_pertenece(abb, "14"));
  print_test("abb borrar clave 95 devuelve 95", *(int*)abb_borrar(abb, "95") == c2);
  print_test("clave 95 ya no pertenece  ", !abb_pertenece(abb, "95"));
  print_test("borrar clave  66 (no guardada) devuelve NULL", !abb_borrar(abb, "66"));
  print_test("abb cantidad nodos es 5", abb_cantidad(abb) == 5);
  print_test("abb borrar clave 11 devuelve 11", *(int*)abb_borrar(abb, "11") == c3);
  print_test("clave 11 ya no pertenece ", !abb_pertenece(abb, "11"));
  print_test("abb borrar clave 46 devuelve 46", *(int*)abb_borrar(abb, "46") == c4);
  print_test("clave 46 ya no pertenece", !abb_pertenece(abb, "46"));
  print_test("abb cantidad es 3 ", abb_cantidad(abb) == 3); 
  print_test("abb borrar clave 85 devuelve 85", *(int*)abb_borrar(abb, "85") == c5);
  print_test("clave 85 ya no pertenece", !abb_pertenece(abb, "85"));
  print_test(" abb borrar 90 devuelve 90", *(int*)abb_borrar(abb, "90") == c6);
  print_test("clave 90 ya no pertenece", !abb_pertenece(abb, "90"));
  print_test("abb borrar 3 devuelve 3 ", *(int*)abb_borrar(abb, "3") == c7 );
  print_test("clave 3 ya no pertenece", !abb_pertenece(abb, "3"));
  print_test("cantidad nodos es 0 ", abb_cantidad(abb) == 0);

  abb_destruir(abb);
  
  abb = abb_crear(comparar, NULL);
  print_test("abb insertar  ", abb_guardar(abb, "40", &c1));
  print_test("abb insertar ", abb_guardar(abb, "30", &c2));
  print_test("abb insertar ", abb_guardar(abb, "20", &c3));
  
  print_test("abb borrar", *(int*)abb_borrar(abb, "40") == c1);
  print_test(" borrado ya no pertenece", !abb_pertenece(abb, "40"));
  print_test("abb borrar", *(int*)abb_borrar(abb, "30") == c2);
  print_test("borrado ya no pertenece", !abb_pertenece(abb, "30"));
  print_test("abb borrar", *(int*)abb_borrar(abb, "20") == c3);
  print_test("borrado ya no pertenece", !abb_pertenece(abb, "20"));
  
  print_test("abb insertar  ", abb_guardar(abb, "40", &c1));
  print_test("abb insertar ", abb_guardar(abb, "30", &c2));
  print_test("abb insertar ", abb_guardar(abb, "20", &c3));
  
  print_test("abb borrar ", *(int*)abb_borrar(abb, "30")==c2);
  print_test("borrado ya no pertenece", !abb_pertenece(abb, "30"));
  print_test("abb borrar", *(int*)abb_borrar(abb, "40") == c1);
  print_test("borrado ya no pertenece", !abb_pertenece(abb, "40"));
  print_test("abb borrar", *(int*)abb_borrar(abb, "20")==c3);
  print_test("borrado ya no pertenece", !abb_pertenece(abb, "20"));

  print_test("abb insertar  ", abb_guardar(abb, "40", &c1));
  print_test("abb insertar ", abb_guardar(abb, "60", &c2));
  print_test("abb insertar ", abb_guardar(abb, "20", &c3));

  print_test("abb borrar", *(int*)abb_borrar(abb, "60")==c2);
  print_test("borrado ya no pertenece", !abb_pertenece(abb, "60"));
  print_test("abb borrar", *(int*)abb_borrar(abb, "40")==c1);
  print_test("borrado ya no pertenece", !abb_pertenece(abb, "40"));
  print_test("abb borrar", *(int*)abb_borrar(abb, "20")==c3);
  print_test("borrado ya no pertenece", !abb_pertenece(abb, "20"));
  
  print_test("abb insertar  ", abb_guardar(abb, "40", &c1));
  print_test("abb insertar ", abb_guardar(abb, "60", &c2));
  print_test("abb insertar ", abb_guardar(abb, "20", &c3));
  
  print_test("abb borrar", *(int*)abb_borrar(abb, "40")==c1);
  print_test("borrado ya no pertenece", !abb_pertenece(abb, "40"));
  print_test("abb borrar", *(int*)abb_borrar(abb, "60")==c2);
  print_test("borrado ya no pertenece", !abb_pertenece(abb, "60"));
  print_test("abb borrar", *(int*)abb_borrar(abb, "20")== c3);
  print_test("borrado ya no pertenece", !abb_pertenece(abb, "20"));
  
  print_test("abb insertar  ", abb_guardar(abb, "40", &c1));
  print_test("abb insertar ", abb_guardar(abb, "60", &c2));
  print_test("abb insertar ", abb_guardar(abb, "50", &c3));
  
  print_test("abb borrar", *(int*)abb_borrar(abb, "40")==c1);
  print_test("borrado ya no pertenece", !abb_pertenece(abb, "40"));
  print_test("abb borrar", *(int*)abb_borrar(abb, "60")==c2);
  print_test("borrado ya no pertenece", !abb_pertenece(abb, "60"));
  print_test("abb borrar", *(int*)abb_borrar(abb, "50")==c3);

  print_test("abb insertar  ", abb_guardar(abb, "40", &c1));
  print_test("abb insertar ", abb_guardar(abb, "60", &c2));
  print_test("abb insertar ", abb_guardar(abb, "50", &c3));
  
  print_test("abb borrar", *(int*)abb_borrar(abb, "60")==c2);
  print_test("borrado ya no pertenece", !abb_pertenece(abb, "60"));
  print_test("abb borrar", *(int*)abb_borrar(abb, "40")==c1);
  print_test("borrado ya no pertenece", !abb_pertenece(abb, "40"));
  print_test("abb borrar", *(int*)abb_borrar(abb, "50")==c3);
  print_test("borrado ya no pertenece", !abb_pertenece(abb, "50"));

  print_test("abb insertar  ", abb_guardar(abb, "50", &c1));
  print_test("abb insertar ", abb_guardar(abb, "60", &c2));
  print_test("abb insertar ", abb_guardar(abb, "70", &c3));
  print_test("abb insertar  ", abb_guardar(abb, "65", &c1));
  print_test("abb insertar ", abb_guardar(abb, "63", &c2));
  print_test("abb insertar ", abb_guardar(abb, "64", &c3));
  print_test("abb insertar  ", abb_guardar(abb, "40", &c3));

  print_test("abb borrar", *(int*)abb_borrar(abb, "50")==c1);
  print_test("borrado ya no pertenece", !abb_pertenece(abb, "50"));
  print_test("abb borrar", *(int*)abb_borrar(abb, "60")==c2);
  print_test("borrado ya no pertenece", !abb_pertenece(abb, "60"));
  print_test("abb borrar", *(int*)abb_borrar(abb, "70")==c3);
  print_test("borrado ya no pertenece", !abb_pertenece(abb, "70"));

  abb_destruir(abb);
  abb = abb_crear(comparar, free);
  int* i1 = malloc(sizeof(int));
  * i1 = 3;
  //i1 = &i2;
  abb_guardar(abb, "14", i1);

  abb_destruir(abb);

}


bool contar_elementos(const char*clave, void* dato, void* extra){
  size_t* a = extra; 
  print_test("clave encontrada", clave);
  if(clave) *a = *a+1;
  return true;
}

bool buscar_tres(const char*clave, void* dato, void* extra){
  size_t* num = extra;
  if(*(int*)dato == 3){ 
    return false; 
  }
  *num = *num+1;
  return true;
}

void pruebas_iter(){
  abb_t* abb = abb_crear(comparar, NULL);
  
  int c1 = 1 , c2 = 2, c3 = 3;

  print_test("abb insertar  ", abb_guardar(abb, "50", &c1));
  print_test("abb insertar ", abb_guardar(abb, "60", &c3));
  print_test("abb insertar ", abb_guardar(abb, "70", &c3));
  print_test("abb insertar ", abb_guardar(abb, "65", &c1));
  print_test("abb insertar ", abb_guardar(abb, "63", &c2));
  print_test("abb insertar ", abb_guardar(abb, "64", &c1));
  print_test("abb insertar  ", abb_guardar(abb, "40", &c1));
  // 40 50 60 63 64 65 70 
  abb_iter_t* iter = abb_iter_in_crear(abb);
  
  print_test("abb iter no esta al final", !abb_iter_in_al_final(iter));
  print_test("abb iter ver actual es clave: 40", comparar(abb_iter_in_ver_actual(iter), "40") == 0);
  print_test("abb iter avanzar es true", abb_iter_in_avanzar(iter));
  print_test("abb iter ver actual es clave: 50", comparar(abb_iter_in_ver_actual(iter), "50") == 0);
  print_test("abb iter avanzar es true", abb_iter_in_avanzar(iter));
  print_test("abb iter ver actual es clave: 60", comparar(abb_iter_in_ver_actual(iter), "60") == 0);
  print_test("abb iter avanzar es true", abb_iter_in_avanzar(iter));
  print_test("abb iter ver actual es clave: 63", comparar(abb_iter_in_ver_actual(iter), "63") == 0);
  print_test("abb iter avanzar es true", abb_iter_in_avanzar(iter));
  print_test("abb iter ver actual es clave: 64", comparar(abb_iter_in_ver_actual(iter), "64") == 0);
  print_test("abb iter avanzar es true", abb_iter_in_avanzar(iter));
  print_test("abb iter ver actual es clave: 65", comparar(abb_iter_in_ver_actual(iter), "65") == 0);
  print_test("abb iter avanzar es true", abb_iter_in_avanzar(iter));
  print_test("abb iter ver actual es clave: 70", comparar(abb_iter_in_ver_actual(iter), "70") == 0);
  print_test("abb iter avanzar es false", abb_iter_in_avanzar(iter));
  size_t a = 0;
  abb_in_order(abb, contar_elementos, &a);
  print_test("Cantidad iterada correctamente", a == 7);
  printf("cantidad real %zu\n",a);
  a = 0;
  abb_in_order(abb, buscar_tres, &a);
  print_test("posicion del primer 3 correcta", a == 2);
  printf("POSCIION REAL %zu \n", a);
  abb_iter_in_destruir(iter);
  abb_destruir(abb);
   
}

void pruebas_volumen(){
  abb_t* abb = abb_crear(comparar, NULL);
  print_test("PRUEBAS VOLUMEN abb creado", abb);
  bool ok;
  size_t a;
  char** vector = crear_vector_cadenas(TAM);
  size_t cantidad_guardados = 0;
  for( a =0; a < TAM; a++){
    if( !abb_pertenece(abb, vector[a])) cantidad_guardados++;
    ok = abb_guardar(abb, vector[a], &a);
    if(!ok) break;
  }
  print_test("muchos elementos guardados", ok);
  print_test("La cantidad guardada es correcta", abb_cantidad(abb) == cantidad_guardados);
  abb_destruir(abb);
  liberar_cadenas(vector);  
}


void pruebas_abb_alumno(){
  pruebas_vacia();
  pruebas_guardar();
  pruebas_borrar();
  pruebas_iter();
  pruebas_volumen();
}

 
int main(){
  clock_t inicio = clock();
  pruebas_abb_alumno();
  
  double tiempo = (clock()-inicio) * 1.00 / CLOCKS_PER_SEC ;
  printf("el tiempo de ejecucion fue : %f \n",  tiempo);
  return 0;
}
