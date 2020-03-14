#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "matrix.h"

matrix create_matrix(int number_rows, int number_columns){
  matrix m;
  m.row_count = number_rows;
  m.column_count = number_columns;
  m.data = malloc(sizeof(*m.data) * number_rows * number_rows);
  return m;
}

double get(matrix m, int row, int column){
  return m.data[ m.row_count * row + column ];
}

matrix parse_file_input(FILE* input){
  int cols, rows;
  if (fscanf(input, "%d %d", &(rows), &(cols)) != 2){
    perror("Error");
    fprintf(stderr,"Error reading from filedescriptor \n");
    fprintf(stderr,"Function = %s\n", __FUNCTION__);
    exit(-1);
  } else {
    matrix m = create_matrix(rows, cols);
    for(int i = 0; i < m.row_count; i++){
      for(int j = 0; j < m.column_count; j++){
        fscanf(input, "%lf", m.data + (i*m.row_count + j) );
      }
    }
  return m;
  }
}

void destroy_matrix(matrix m){
  free(m.data);
}