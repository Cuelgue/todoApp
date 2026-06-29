
#include "tarea.h"

#ifndef ARCHIVO_H
#define ARCHIVO_H

// Estas lineas son las que van a separar en el archivo las tareas.
#define TAREAS_COMPLETAS "# COMPLETAS\n"
#define TAREAS_INCOMPLETAS "# INCOMPLETAS\n"
#define MAX_LE 15


/* Por el momento este programita va a ser solo para linux */
#define ARCHIVO ".tareas"
#define PATH ".config/"

typedef struct {
  tarea_t incompleta;
  tarea_t completa;
} estado_t;


long size_file(FILE *f);


long cargar_file(FILE *f,unsigned char **file_buffer);

int guardar_file(FILE *f, tarea_t tareas, char *tipo);

void cargar_listas(estado_t *tareas, FILE *f);
#endif
