#include "tarea.h"

void agregar_tarea(char cad[])
{
  if (fgets(cad,BUFFEF,stdin) == NULL) {
    perror("fgets()");
    exit(1);
  }
  int salto = strlen(cad);
  cad[salto - 1] = '\0';
  strncat(cad,INCOMPLETA,strlen(cad) - 1);
  strncat(cad,"\n",sizeof(&cad) - strlen(cad) - 1);
}



/*FIXME: Tanto agregar_tarea como
  completar_tarea ni agregan de manera
  correcta el estado si la longitud de la
  es inferior a ocho.
*/


int existe(tarea_t tareas,char *cad)
{
  int ret = 0;
  int i = 0;
  while (i < tareas.cantidad && strcoll(tareas.lista[i],cad) != 0) i++;

  //Si no llego al total es porque encontro una cadena que es igual.
  if (i < tareas.cantidad) ret = 1;


  return ret;

}

//FIXME: No se deberia poder agregar una tarea dos veces.
void agregar_en_lista(tarea_t *tareas, char *cad)
{

  if (!existe(*tareas,cad)){
    tareas->lista[tareas->cantidad] = strdup(cad);
    if (tareas->lista[tareas->cantidad] == NULL) {
      fprintf(stderr,"MALLOC ERROR: No se pudo reserver memoria\n");
      exit(1);
    }
    tareas->cantidad++;
  }
}

//Aca simplemente se hace un desplazo de todos los elementos restantes del array.
void eliminar_tarea(tarea_t *tarea, int pos, bool vf)
{
  int posR = pos - 1;
  if (posR >= 0 && posR < tarea->cantidad) {
  //acá el tema es el siguiente, esta funcion ademas la estoy usando
  //Para hacer un reset, tengo dos alternativas o usar un booleano
  //para decidir si hacer un free de la cadena, segun corresponda 
  if (vf) {
    free(tarea->lista[posR]);
    tarea->lista[posR] = NULL;
}

    for (int i = posR; i < tarea->cantidad -1; i++){
      tarea->lista[i] = tarea->lista[i + 1];
    }
    tarea->cantidad--;
  } 
 
}



// Resetea o completa una tarea, según como se pase los parametros.
void rc_tarea(tarea_t *dst, tarea_t *src, int pos)
{
  /*Vamos a explicar esto: tareas->incompleta.cantidad siempre esta +1 por encima
  del contador, los indices empiezan en 0, por lo que uso cantidad como indice
  Ademas tengo pos, que aparece como la posicion real + 1
  por lo que tengo que restarle 1 a pos para que de ael indice correcto.u
  */
  dst->lista[dst->cantidad] = src->lista[pos - 1];
  dst->cantidad++;
  eliminar_tarea(src,pos,false);
}


void imp_lista(tarea_t lista)
{
  for (int i = 0; i < lista.cantidad; i++){
    printf("%d - %s",i + 1,lista.lista[i]);
  }
}

void liberar_tarea(tarea_t *tarea)
{
  for (int i = 0; i < tarea->cantidad; i++) {
    free(tarea->lista[i]);
}
 }

//La unica diferencia es que aca se lineran todas las tareas.
void lib_tarea_todas(estado_t *tareas)
{
  liberar_tarea(&tareas->incompleta);
  liberar_tarea(&tareas->completa);
}
