#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#ifndef TAREA_H
#define TAREA_H


/*
  No deberia por ningún motivo ser insuficiente,
  teniendo en cuenta que esto no pretende ser
  un editor de texto.
*/
#define BUFFER 1024
#define MAX_TAREA BUFFER / 2

#define RESTO 5 // Valor a restar al bufer por los agregados (COMPLETA o INCOMPLETA) + "\0"
//El nombre es por BUFFER EFECTIVO, pero quedaba muy largo.
#define BUFFEF BUFFER - RESTO 
#define INCOMPLETA " [ ]"


typedef struct {
  char *lista[MAX_TAREA];
  int cantidad;
} tarea_t;

typedef struct {
  tarea_t incompleta;
  tarea_t completa;
} estado_t;

void agregar_tarea(char cad[],int n);


int existe(tarea_t tareas,char *cad);


void agregar_en_lista(tarea_t *tareas, char *cad);


void eliminar_tarea(tarea_t *tarea, int pos, bool vf);


void rc_tarea(tarea_t *dst, tarea_t *src, int pos);


void imp_lista(tarea_t lista);

void liberar_tarea(tarea_t *tarea);

void lib_tarea_todas(estado_t *tareas);
#endif
