#pragma once

typedef struct matrix
{
  int column_count;
  int row_count;
  double* data;
} matrix, * matrix_ptr;
