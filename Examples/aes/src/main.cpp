//#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <assert.h>

#define WRITE_OUTPUT
#define CHECK_OUTPUT

#include "support.h"
#ifdef MCC_ACC
#include MCC_ACC_H_FILE
#endif

int main(int argc, char **argv)
{
  // Parse command line.
  char *in_file;
  char *check_file;

#ifdef MCC_ACC
  assert( argc<5 && "Usage: ./aesapp <input_file> <check_file> <kernel_binary>" );
#else
  assert( argc<4 && "Usage: ./aesapp <input_file> <check_file>" );
#endif

  in_file = argv[1];
  check_file = argv[2];

#ifdef MCC_ACC
  char *kernel_binary_file = argv[3];

  __merlin_init(kernel_binary_file);
#endif

  // Load input data
  int in_fd;
  char *data;
  posix_memalign ((void**)&data, 64, INPUT_SIZE);
  assert( data!=NULL && "Out of memory" );
  in_fd = open( in_file, O_RDONLY );
  assert( in_fd>0 && "Couldn't open input data file");
  input_to_data(in_fd, data);

  // Unpack and call
  run_benchmark( data );

  int out_fd;
  out_fd = open("./output.data", O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
  assert( out_fd>0 && "Couldn't open output data file" );
  data_to_output(out_fd, data);
  close(out_fd);

  // Load check data
  int check_fd;
  char *ref;
  //ref = malloc(INPUT_SIZE);
  ref = (char *) malloc(INPUT_SIZE);
  assert( ref!=NULL && "Out of memory" );
  check_fd = open( check_file, O_RDONLY );
  assert( check_fd>0 && "Couldn't open check data file");
  output_to_data(check_fd, ref);

  // Validate benchmark results
  int status = 0;
  if( !check_data(data, ref) ) {
    fprintf(stderr, "Benchmark results are incorrect\n");
    char file_name[256] = "fail.o";
    FILE *fp=fopen(file_name,"ab+");
    if(fp==NULL) printf("can't create file %s!", file_name);
    status = -1;
  }

#ifdef MCC_ACC
  printf("__merlin_release()\n");
  __merlin_release();
#endif

  if (status == 0) {
    printf("Success.\n");
    char file_name_s[256] = "pass.o";
    FILE *fp_s=fopen(file_name_s,"ab+");
    if(fp_s==NULL) printf("can't create file %s!", file_name_s);
    return 0;
  }
  return(status);
}

