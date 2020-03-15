#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include "matrix.h"

matrix handlefiles(const char* filename);

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

    matrix first = handlefiles(first_file);
    matrix second = handlefiles(second_file);

    matrix result = create_matrix(first.row_count, second.column_count);
    // adding batching
    int last_batch = first.row_count % thread_count;
    int batch = (first.row_count + last_batch )/ thread_count;
    last_batch = last_batch == 0 ? thread_count : last_batch;
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

matrix handlefiles(const char* filename){

    FILE *file = fopen(filename, "r");
    if (file == NULL){
      perror("Error");
      exit(-1);
    }
    matrix tmp = parse_file_input(file);
    fclose(file);
    return tmp;
}
