#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include "matrix.h"

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    printf("Missing filenames\n");
  } else if( argc < 3){
    printf("Missing 2nd filename");
  } else {
  FILE *file = fopen(argv[1], "r");
  if (file == NULL){
    perror("Error");
    exit(-1);
  }
  matrix first = parse_file_input(file);
  fclose(file);

  file = fopen(argv[1], "r");
  if (file == NULL){
    perror("Error");
    exit(-1);
  }
  matrix second = parse_file_input(file);
  fclose(file);

  double result = matrix_row_column(first, 0, second, 0);
  printf("answer = %lf\n", result);

  destroy_matrix(first);
  destroy_matrix(second);
  return 0;
  }
  return -1;
}