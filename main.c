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
    int thread_count = atoi(argv[1]);
    const char * first_file = argv[2];
    const char * second_file = argv[3];

    FILE *file = fopen(first_file, "r");
    if (file == NULL){
      perror("Error");
      exit(-1);
    }
    matrix first = parse_file_input(file);
    fclose(file);

    file = fopen(second_file, "r");
    if (file == NULL){
      perror("Error");
      exit(-1);
    }
    matrix second = parse_file_input(file);
    fclose(file);
    matrix result = create_matrix(first.row_count, second.column_count);
    // adding batching
    // Adding thread creation
    for(int i = 0; i < first.row_count; i++){
      for(int j = 0; j < second.column_count; j++){
        double entry = matrix_row_column(first, i, second, j);
        set(result, i, j, entry);
      }
    }
    printf("First\n");
    printf("*******\n");
    print_matrix(first);
    printf("*******\n");
    printf("Second\n");
    printf("*******\n");
    print_matrix(second);
    printf("*******\n");

    printf("Result\n");
    printf("*******\n");
    print_matrix(result);
    printf("*******\n");


    destroy_matrix(first);
    destroy_matrix(second);
    destroy_matrix(result);
    return 0;
    }
  return -1;
}