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
    int * c_acc = (int *)alignedMalloc(sizeof(int)*VEC_SIZE); 

    // init
    for(i=0; i<VEC_SIZE; i++) {
	    a[i] = i;
	    b[i] = 2*i;
	    c[i] = 1;
	    c_acc[i] = 1;
    }    

    printf("Starting Vector Addition Example \n");

    // execute original reference code
    vec_add(a, b, c, inc);

    // execute kernel code 
#ifdef MCC_ACC
    __merlin_vec_add_kernel(a, b, c_acc, inc);
#else
    vec_add_kernel(a, b, c_acc, inc);
#endif

    // test results
    int err = 0;
    for(i=0; i<VEC_SIZE; i++) {
        if(c[i] != c_acc[i]) {
            err++;
        }
    }

    free(a);
    free(b);
    free(c);
    free(c_acc);

#ifdef MCC_ACC
    __merlin_release();
#endif

    if (err) {
        printf("Test failed %d\n",err);
        return 1;
    }
    else {
        printf("Test passed\n");
        return 0;
    }
}


