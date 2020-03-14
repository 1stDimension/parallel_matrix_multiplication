#include "matrix.h"
#include <stdlib.h>

matrix create_matrix(int number_columns, int number_rows){
  matrix m;
  m.column_count = number_columns;
  m.row_count = number_rows;
  m.data = malloc(sizeof(*m.data) * number_rows * number_columns);
  return m;
}

void destroy_matrix(matrix m){
  free(m.data);
}