#pragma once

typedef struct matrix
{
  int column_count;
  int row_count;
  double* data;
} matrix, * matrix_ptr;

matrix create_matrix(int number_columns, int number_rows);

double get(matrix m, int row, int column);


void destroy_matrix(matrix m);