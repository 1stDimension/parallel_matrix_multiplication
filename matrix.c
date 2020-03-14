#include "matrix.h"
#include <stdlib.h>

matrix create_matrix(int number_columns, int number_rows){
  matrix m;
  m.column_count = number_columns;
  m.row_count = number_rows;
  m.data = malloc(sizeof(*m.data) * number_rows * number_columns);
  return m;
}

double get(matrix m, int row, int column){
  return m.data[ m.row_count * row + column ];
}

void destroy_matrix(matrix m){
  free(m.data);
}