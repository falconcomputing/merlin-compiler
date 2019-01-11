/****************************************************************************/
// main.cpp
// Copyright (C) 2017 Falcon Computing Solutions, Inc. - All rights reserved.
/****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "vec_add.h"

#ifdef MCC_ACC
#include MCC_ACC_H_FILE
#endif

#define AOCL_ALIGNMENT 64

void *alignedMalloc(size_t size) {
  void *result = NULL;
  posix_memalign (&result, AOCL_ALIGNMENT, size);
  return result;
}

int main(int argc, char* argv[])
{   
#ifdef MCC_ACC
    char *bin_file = argv[1];
    __merlin_init(bin_file);
#endif

    int i=0;
    int inc = 1;
    int * a = (int *)alignedMalloc(sizeof(int)*VEC_SIZE); 
    int * b = (int *)alignedMalloc(sizeof(int)*VEC_SIZE); 
    int * c = (int *)alignedMalloc(sizeof(int)*VEC_SIZE); 

    // init
    for(i=0; i<VEC_SIZE; i++) {
	    a[i] = i;
	    b[i] = 2*i;
	    c[i] = 1;
    }    

    printf("Starting Vector Addition Example \n");

    // execute kernel code 
#ifdef MCC_ACC
    __merlin_vec_add_kernel(a, b, c, inc);
    __merlin_release();
#else
    vec_add_kernel(a, b, c, inc);
#endif

    // test results
    int err = 0;
    for(i=0; i<VEC_SIZE; i++) {
        if(c[i] != a[i] + b[i] + inc) {
            err++;
        }
    }

    free(a);
    free(b);
    free(c);

    if (err) {
        printf("Test failed %d\n",err);
        return 1;
    }
    else {
        printf("Test passed\n");
        return 0;
    }
}


