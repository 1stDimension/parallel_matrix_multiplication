#pragma once

typedef struct matrix
{
  int column_count;
  int row_count;
  double* data;
} matrix, * matrix_ptr;

matrix create_matrix(int number_columns, int number_rows);

matrix matrix_multiply(matrix first, matrix second);

double get(matrix m, int row, int column);

matrix parse_file_input(FILE* input);

void destroy_matrix(matrix m);