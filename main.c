#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include "matrix.h"

int main(int argc, char **argv)
{
  if (argc < 2) {
    printf("Missing thread count\n");
  } else if(argc < 3)
  {
    printf("Missing filenames\n");
  } else if( argc < 4){
    printf("Missing 2nd filename");
  } else {
    FILE *file = fopen(argv[2], "r");
    if (file == NULL){
      perror("Error");
      exit(-1);
    }
    matrix first = parse_file_input(file);
    fclose(file);

    file = fopen(argv[3], "r");
    if (file == NULL){
      perror("Error");
      exit(-1);
    }
    matrix second = parse_file_input(file);
    fclose(file);
    matrix result = create_matrix(first.row_count, second.column_count);
    for(int i = 0; i < first.row_count; i++){
      for(int j = 0; j < second.column_count; j++){
        double entry = matrix_row_column(first, i, second, j);
        set(result, i, j, entry);
      }
    }


    destroy_matrix(first);
    destroy_matrix(second);
    return 0;
    }
  return -1;
}