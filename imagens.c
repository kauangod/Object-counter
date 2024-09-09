#include "pqueue.h"
/* Exercício proposto pelo professor Rodrigo Minetto - UTFPR. */ 
int** create_matrix (int nrows, int ncols) {
  int i;
  int **matrix = (int **)malloc(nrows * sizeof(int *));
  for (i = 0; i < nrows; i++) {
    matrix[i] = (int *)malloc(ncols * sizeof(int));
  }
  return matrix;
}

void destroy_matrix (int **matrix, int nrows, int ncols) {
  int i;	
  for (i = 0; i < nrows; i++) 
    free (matrix[i]);
  free (matrix);  
}

int inside (int i, int j, int nrows, int ncols) {
  if ((i < 0) || (j < 0) || (i >= nrows) || (j >= ncols))
    return 0;
  return 1;    
}

void conquista (int **matrix, int i, int j, int nrows, int ncols) {
  Queue *q = create(nrows*ncols+1); /*limite maximo*/
  enqueue (q, (point){i,j});
  matrix[i][j] = 0; /*Coordenada {i,j} anulada para não ser mais explorada!*/
  while (!empty(q)) {
    point p = dequeue (q);
    if (matrix [i+1][j] == 1 && i < nrows) {
      enqueue (q, (point){i+1, j});
      conquista (matrix, i+1, j, nrows, ncols);}
    else if (matrix [i+1][j+1] == 1 && i < nrows && j < ncols){
      enqueue (q, (point){i+1, j+1});
      conquista (matrix, i+1, j+1, nrows, ncols);}
    else if (matrix [i][j+1] == 1 && j < ncols){
      enqueue (q, (point){i, j+1});
      conquista (matrix, i, j+1, nrows, ncols);}
    else if (matrix [i+1][j-1] == 1 && i < nrows && j > 0){
      enqueue (q, (point){i+1, j-1});
      conquista (matrix, i+1, j-1, nrows, ncols);}
    else if (matrix [i-1][j] == 1 && i > 0){
      enqueue (q, (point){i-1, j});
      conquista (matrix, i-1, j, nrows, ncols);}
    else if (matrix [i-1][j-1] == 1 && i > 0 & j > 0){
      enqueue (q, (point){i-1, j-1});
      conquista (matrix, i-1, j-1, nrows, ncols);}
    else if (matrix [i][j-1] == 1 && j > 0 && j > 0){
      enqueue (q, (point){i, j-1});
      conquista (matrix, i, j-1, nrows, ncols);}
    else if (matrix [i-1][j+1] == 1 && i > 0 && j < ncols){
      enqueue (q, (point){i-1, j+1});
      conquista (matrix, i-1, j+1, nrows, ncols);}
      
  }
  destroy (q); 
}

int count_islands (int **matrix, int nrows, int ncols) {
  int i, j, sum = 0;	
  for (i = 0; i < nrows; i++) {
    for (j = 0; j < ncols; j++) {
      if (matrix[i][j] == 1) {
        conquista (matrix, i, j, nrows, ncols); 
        sum++;    
      }	      
    }	     
  }
  return sum;
}

int main () {

  char *type = (char *)malloc(2 * sizeof(char));

  int ncols, nrows;

  /*No windows use o software https://www.irfanview.com/ para visualizar as imagens*/
  FILE *image_in  = fopen("parafusos.pbm", "r");

  /*Lendo as informações do cabeçalho da imagem:*/
  fscanf(image_in, "%s", type);

  fscanf(image_in, "%d %d", &ncols, &nrows);

  int **matrix = create_matrix (nrows, ncols);
  
  /*Lendo a imagem de entrada: 1 é objeto e 0 background!*/
  int i, j;
  for (i = 0; i < nrows; i++) {
    for (j = 0; j < ncols; j++) {
      fscanf(image_in, "%d", &matrix[i][j]);
    }
  }
  fclose(image_in);
  int ans = count_islands (matrix, nrows, ncols);
  printf("Número de ilhas: %d \n", ans);
 
  destroy_matrix (matrix, nrows, ncols);

  free (type);

  return 0; 
}
