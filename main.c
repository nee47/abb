#include "testing.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
void pruebas_heap_alumno(void);

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

int main(int argc, char *argv[])
{
  clock_t inicio = clock();
    printf("~~~ PRUEBAS ALUMNO ~~~\n");
    pruebas_heap_alumno();
    double tiempo = (clock() - inicio) *1.00 / CLOCKS_PER_SEC ;
    printf("tiempo de ejecucion fue : %f\n", tiempo);
    return failure_count() > 0;
}
