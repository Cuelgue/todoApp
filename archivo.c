#include <stdio.h>
#include <stdlib.h>


#include "tarea.h"
#include "archivo.h"


long size_file(FILE *f)
{
  if (f == NULL) exit(1);
  //Voy al final del archivo
  int fs = fseek(f,0L,SEEK_END);
  (void) fs;
  //guardo la longitud del archivo
  long n = ftell(f);
  if (n < 0) {
    perror("ftell");
  }
  //Me posicikono al comienzo del archivo
  fseek(f,0L,SEEK_SET);
  return n;
}

//Esta es una funcion que hice pero no estoy usando, no se por que.
//La voy a dejar por si cambio la manera de leer el archivo en la carga.
long cargar_file(FILE *f,unsigned char **file_buffer)
{

  long size = size_file(f);
  //Si size es cero significa que el archivo acaba de ser creado
  //No hayu nada que leer.
  if (size > 0) {
  *file_buffer = (unsigned char*)malloc(size + 1);
  size_t ret = fread(*file_buffer,size,1,f);
  (void)ret;
  } 
  return size;
}

int guardar_file(FILE *f, tarea_t tareas, char *tipo)
{
  int n;
  //Muy "a mano" pero se que va a funcionar.
  fwrite(tipo,sizeof(char),strlen(tipo),f);
  for (int i = 0; i < tareas.cantidad; i++) {
    n = fwrite(tareas.lista[i],sizeof(char),strlen(tareas.lista[i]),f);
  }
  return n;
}



void cargar_listas(estado_t *tareas, FILE *f)
{
  char lineaDeEstado[MAX_LE];
  char linea[MAX_TAREA];
  while (fgets(linea,MAX_TAREA,f) != NULL) {

    if (linea[0] == '#') {
      strcpy(lineaDeEstado,linea);
    } else {
      if (strcmp(lineaDeEstado,TAREAS_COMPLETAS) == 0) {
        agregar_en_lista(&tareas->completa,linea);
      } else {
        agregar_en_lista(&tareas->incompleta,linea);
      }
    }
  }

}
