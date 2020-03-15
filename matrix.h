#pragma once

typedef struct matrix
{
  int column_count;
  int row_count;
  double* data;
} matrix, * matrix_ptr;

matrix create_matrix(int number_columns, int number_rows);

double matrix_row_column(matrix first, int row, matrix second, int column);

double get(matrix m, int row, int column);

void set(matrix m, int row, int column, double value);

void print_matrix(matrix m);

matrix parse_file_input(FILE* input);

void destroy_matrix(matrix m);