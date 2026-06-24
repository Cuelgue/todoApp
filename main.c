#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*
  No deberia por ningún motivo ser insuficiente,
  teniendo en cuenta que esto no pretende ser
  un editor de texto.
*/
#define BUFFER 1024
#define MAX_TAREA BUFFER / 2
//MBFP es por MAX BUFFER FULL PATH para que no quede largo
#define MBFP MAX_TAREA / 2
#define RESTO 5 // Valor a restar al bufer por los agregados (COMPLETA o INCOMPLETA) + "\0"
//El nombre es por BUFFER EFECTIVO, pero quedaba muy largo.
#define BUFFEF BUFFER - RESTO 
#define INCOMPLETA " [ ]"


/* Por el momento este programita va a ser solo para linux */
#define ARCHIVO ".tareas"
#define PATH ".config/"

typedef struct {
  char *lista[MAX_TAREA];
  int cantidad;
} tarea_t;

//Mi problema para nombrar es grande.
/* La idea es tener tanto tareas completadas como incompletas
 asi de querese poder resetear las completas, tendria que ver tambien
si mas adelante quiero agregar "Tareas complejar"*/
typedef struct {
  tarea_t incompleta;
  tarea_t completa;
} estado_t;

void agregar_tarea(char cad[])
{
  fgets(cad,BUFFEF,stdin);
  int salto = strlen(cad);
  cad[salto - 1] = '\0';
  strncat(cad,INCOMPLETA,sizeof(&cad) - strlen(cad) - 1);
}

void completar_tarea(char cad[])
{
  /*el fin de linea es \0 strlen cuenta los caracteres incluso ese
  al restarte 2 quedo posicionado en el espacio"*/
  int pos = strlen(cad) - 2;
  cad[pos] = 'X';
}


/*FIXME: Tanto agregar_tarea como
  completar_tarea ni agregan de manera
  correcta el estado si la longitud de la
  es inferior a ocho.
*/

long size_file(FILE *f)
{
  if (f == NULL) exit(1);
  //Voy al final del archivo
  int fs = fseek(f,0L,SEEK_END);
  //guardo la longitud del archivo
  long n = ftell(f);
  if (n < 0) {
    perror("ftell");
  }
  //Me posicikono al comienzo del archivo
  fseek(f,0L,SEEK_SET);
  return n;
}

long cargar_file(FILE *f,unsigned char **file_buffer)
{

  long size = size_file(f);
  //Si size es cero significa que el archivo acaba de ser creado
  //No hayu nada que leer.
  if (size > 0) {
  *file_buffer = (unsigned char*)malloc(size + 1);
  size_t ret = fread(*file_buffer,size,1,f);
  } 
  return size;
}




void agregar_en_lista(tarea_t *tareas, char cad)
{
  tareas->lista[tareas->cantidad] = strdup(&cad);
  if (tareas->lista[tareas->cantidad] == NULL) {
    fprintf(stderr,"MALOCC ERROR: No se pudo reserver memoria\n",__LINE__);
    exit(1);
  }
  
  tareas->cantidad++;
    
}

//Aca simplemente se hace un desplazo de todos los elementos restantes del array.
void eliminar_tarea(tarea_t *tarea, int pos)
{
  int posR = pos - 1;
  if (posR >= 0 && posR < tarea->cantidad) {
    for (int i = posR; i < tarea->cantidad -1; i++){
      tarea->lista[i] = tarea->lista[i + 1];
    }
    tarea->cantidad--;
  } 
 
}

void resetear_tarea(estado_t *tareas, int pos)
{
  /*Vamos a explicar esto: tareas->incompleta.cantidad siempre esta +1 por encima
  del contador, los indices empiezan en 0, por lo que uso cantidad como indice
  Ademas tengo pos, que aparece como la posicion real + 1
  por lo que tengo que restarle 1 a pos para que de ael indice correcto.u
  */
  tareas->incompleta.lista[tareas->incompleta.cantidad] = tareas->completa.lista[pos - 1];
  tareas->incompleta.cantidad++;
  eliminar_tarea(&tareas->incompleta,pos);
}


int main()
{
  char cadena[BUFFER];
  char full_path[256];
  int size_cadena;
  estado_t tareas;
  //acá armo la ruta absoluta
  snprintf(full_path,sizeof(full_path),"%s/%s%s",getenv("HOME"),PATH,ARCHIVO);
  FILE *f = fopen(full_path,"r+");
  //Otra cosa que ahora no estoy teniendo en cuenta es que el archivo si exista pero
  //que el path sea incorrecto, voy a poner un FIXME pero esto en linux deberia funcionar.
  if (f == NULL) {
    f = fopen(full_path,"w");
    if (f == NULL) {
      //Puede que sea redundante pero no se me ocurre una mejopr manera
      //La idea es "Si el archivo no existe lo creo, si no lo puedo crear mando error"
      perror("fopen (r)");
      //      fprintf(stderr,"ERROR: No se pudo abrir el archivo %s\n",ARCHIVO);
      exit(1);
    }


  }
  unsigned char *file_buffer = NULL;
  if (cargar_file(f,&file_buffer) == 0) {
    printf("No se han cargado tareas\n");
  }
  //agregar_tarea(cadena);
  //completar_tarea(cadena);
  //printf("%s\n",cadena);
  fclose(f);
  return 0;
}
