#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <math.h>
#include "matrix.h"

matrix handlefiles(const char* filename);

typedef struct random_name_0{
  int begin;
  int end;
  matrix a;
  matrix b;
  matrix result;
} thread_args, *thread_args_ptr;

typedef struct dev_random {
  double square_of_partial_sum;
} thread_output, *thread_output_ptr;

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
  //sum of square
  thread_output_ptr answer = malloc(sizeof(thread_output) ); 
  for(int i = begin; i < end; i++){
    for(int j = 0; j < result.column_count; j++){
      double entry = get(result, i,j);
      answer->square_of_partial_sum += pow(entry,2);
    }
  }
  #ifdef DEBUG
    printf("Thread answer = %g\n", answer->square_of_partial_sum);
  #endif
  return (void*) answer;
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
    int batch = first.row_count/ thread_count;
    first_batch = first_batch == 0 ? batch : first_batch;
    
    pthread_t threads[thread_count];
    thread_output_ptr partial_frobenious_norm_squared[thread_count];
    thread_args* threads_input = malloc(thread_count * sizeof(thread_args));

    (threads_input[0]).begin = 0;
    (threads_input[0]).end = first_batch;
    (threads_input[0]).a = first;
    (threads_input[0]).b = second;
    (threads_input[0]).result = result;

    for(int i = 1, last = first_batch; i < thread_count; i++){
      (threads_input[i]).a = first;
      (threads_input[i]).b = second;
      (threads_input[i]).result = result;
      (threads_input[i]).begin = last;
      if (last >= first.row_count){
        (threads_input[i]).end = last;
      } else {
        (threads_input[i]).end = last + batch;
        last += batch;
      }
    }

    for (int i = 0; i < thread_count ; i++)
    {
      pthread_create(threads + i, NULL, thread_function, (void *) (threads_input + i) );
    }

    for (int i = 0; i < thread_count; i++)
    {
      pthread_join(threads[i], (void*) (partial_frobenious_norm_squared + i) );
    }
    free(threads_input);
    #ifdef DEBUG
      for(int i = 0 ; i < thread_count; i++){
        printf("%d partial sum %lf \n", i, (partial_frobenious_norm_squared[i])->square_of_partial_sum);
      }
    #endif

    double frobenius_norm = 0;
    for (int i = 0; i < thread_count; i++)
    {
      frobenius_norm += (partial_frobenious_norm_squared[i])->square_of_partial_sum;
      free(partial_frobenious_norm_squared[i]);
    }
    frobenius_norm = sqrt(frobenius_norm);

    printf("First Matrix\n");
    print_matrix(first);
    printf("*******\n");
    printf("Second Matrix\n");
    print_matrix(second);
    printf("*******\n");
    printf("Resulting Matrix\n");
    print_matrix(result);
    printf("*******\n");
    printf("Frobenius norm of resulting matrix = %g\n", frobenius_norm);

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
