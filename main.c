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
  matrix m = parse_file_input(file);
  fclose(file);
  destroy_matrix(m);
  return 0;
  }
  return -1;
}