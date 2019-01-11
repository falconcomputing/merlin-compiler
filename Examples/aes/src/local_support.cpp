#include <string.h>
#include <sys/time.h>
#include "aes.h"

int INPUT_SIZE = sizeof(struct bench_args_t);

#ifdef MCC_ACC
#include MCC_ACC_H_FILE
#else
void aes256_encrypt_ecb_kernel( uint8_t* key, uint8_t* data);
#endif

void run_benchmark( void *vargs ) {
  struct bench_args_t *args = (struct bench_args_t *)vargs;

  int size = BATCH*16;
  uint8_t *data;
  posix_memalign ((void**)&data, 64, size);
  for (int i=0; i<size; i+=16)
    memcpy(data + i, args->buf, sizeof(args->buf));

  //------------------------------------------------------
  printf("INFO: Starting processing %d bytes data...\n", size);
  struct timeval tv_start, tv_end;
  double kernel_time;
  gettimeofday (&tv_start, NULL);

#ifdef MCC_ACC
  __merlin_aes256_encrypt_ecb_kernel( args->k, data);
#else
  aes256_encrypt_ecb_kernel( args->k, data);
#endif


  //stop the timer
  gettimeofday (&tv_end, NULL);
  printf("INFO: Kernel execution completed.\n");
  kernel_time = (tv_end.tv_sec - tv_start.tv_sec) * 1000.0 +
    (tv_end.tv_usec - tv_start.tv_usec)/1000.0;

  printf("INFO: Kernel execution time=%f ms\n", kernel_time);
  //------------------------------------------------------

  memcpy(args->buf, data, sizeof(args->buf));
}

/* Input format:
   %%: Section 1
   uint8_t[32]: key
   %%: Section 2
   uint8_t[16]: input-text
   */

void input_to_data(int fd, void *vdata) 
{
  struct bench_args_t *data = (struct bench_args_t *)vdata;
  char *p, *s;
  // Zero-out everything.
  memset(vdata,0,sizeof(struct bench_args_t));
  // Load input string
  p = readfile(fd);
  // Section 1: key
  s = find_section_start(p,1);
  parse_uint8_t_array(s, data->k, 32);
  // Section 2: input-text
  s = find_section_start(p,2);
  parse_uint8_t_array(s, data->buf, 16);
}

void data_to_input(int fd, void *vdata) {
  struct bench_args_t *data = (struct bench_args_t *)vdata;
  // Section 1
  write_section_header(fd);
  write_uint8_t_array(fd, data->k, 32);
  // Section 2
  write_section_header(fd);
  write_uint8_t_array(fd, data->buf, 16);
}

/* Output format:
   %% Section 1
   uint8_t[16]: output-text
   */
void output_to_data(int fd, void *vdata) 
{
  struct bench_args_t *data = (struct bench_args_t *)vdata;

  char *p, *s;
  // Zero-out everything.
  memset(vdata,0,sizeof(struct bench_args_t));
  // Load input string
  p = readfile(fd);
  // Section 1: output-text
  s = find_section_start(p,1);
  parse_uint8_t_array(s, data->buf, 16);
}

void data_to_output(int fd, void *vdata) {
  struct bench_args_t *data = (struct bench_args_t *)vdata;
  // Section 1
  write_section_header(fd);
  write_uint8_t_array(fd, data->buf, 16);
}

int check_data( void *vdata, void *vref ) 
{
  struct bench_args_t *data = (struct bench_args_t *)vdata;
  struct bench_args_t *ref = (struct bench_args_t *)vref;
  int has_errors = 0;

  // Exact compare encrypted output buffers
  has_errors |= memcmp(&data->buf, &ref->buf, 16*sizeof(uint8_t));

  // Return true if it's correct.
  return !has_errors;
}
