#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include "matrix.h"

matrix handlefiles(const char* filename);

typedef struct {
  int begin;
  int end;
  matrix a;
  matrix b;
  matrix result;
} thread_args;

void * thread_function(void* kargs) {
  thread_args* args = (thread_args*) kargs;
  int begin = args->begin;
  int end = args->end;
  matrix a = args->a;
  matrix b = args->b;
  matrix result = args->result;
  for(int i = begin; i < end; i++){
    for(int j = 0; j < b.column_count; j++){
      double entry = matrix_row_column(a, i, b, j);
      set(result, i, j, entry);
    }
  }
  
  printf("I'm a thread\n");
  return NULL;
}

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
    int first_batch = first.row_count % thread_count;
    int batch = (first.row_count + first_batch )/ thread_count;
    first_batch = first_batch == 0 ? thread_count : first_batch;
    
    pthread_t threads[thread_count];
    thread_args args;
    args.a = first;
    args.b = second;
    args.result = result;

    pthread_create(threads,NULL , thread_function, (void *) &args);
    for (int i = 1; i < thread_count ; i++)
    {
      pthread_create(threads + i, NULL, thread_function, (void *) &args);
    }

    for(int i = 0; i < first.row_count; i++){
      for(int j = 0; j < second.column_count; j++){
        double entry = matrix_row_column(first, i, second, j);
        set(result, i, j, entry);
      }
    }

    double partial_frobenious_norm_squared[thread_count];

    for (int i = 0; i < thread_count; i++)
    {
      pthread_join(threads[i], (void*) partial_frobenious_norm_squared + i);
    }

    double frobenius_norm = 0;
    for (int i = 0; i < thread_count; i++)
    {
      frobenius_norm += partial_frobenious_norm_squared[i];
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
