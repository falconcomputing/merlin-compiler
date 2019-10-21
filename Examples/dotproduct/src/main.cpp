/****************************************************************************/
// main.cpp
// Copyright (C) 2017 Falcon Computing Solutions, Inc. - All rights reserved.
/****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#ifdef MCC_ACC
#include MCC_ACC_H_FILE
#else
extern void dot_kernel(const float *a,const float *b,float *c);
#endif

#define VS 4096

int main(int argc, char* argv[])
{   
    int i = 0;
    float * a = (float *)malloc(sizeof(float)*VS); 
    float * b = (float *)malloc(sizeof(float)*VS); 
    float * c = (float *)malloc(sizeof(float)*1); 
    float * c_acc = (float *)malloc(sizeof(float)*1);

    // init
    for(i = 0; i < VS; i++) {
        a[i] = float(i) / VS;
        b[i] = float(i * i) / VS;
    }    

    printf("Starting Dot Product Example \n");

    // execute original reference code
    c[0] = 0.f;
    for (int i = 0; i < VS; ++i) { 
        c[0] += a[i] * b[i];
    }

    // execute kernel code 
#ifdef MCC_ACC // use kernel binary file
    char* kernel_bin_file = argv[1];
    // load the binary file into the system
    __merlin_init(kernel_bin_file);
    // execute the kernel
    //__merlinwrapper_vec_mul_kernel(a, b, c_acc, num_elems);
    __merlin_dot_kernel(a, b, c_acc);
#else // execute kernel code on CPU
    dot_kernel(a, b, c_acc);
#endif

    // test results
    bool err = false;
    if ((c[0] - c_acc[0]) / c[0] > 1e-4) {
        err = true;
    }

    free(a);
    free(b);
    free(c);
    free(c_acc);

    if (err) {
        printf("Test failed %d\n",err);
        return 1;
    }
    else {
        printf("Test passed\n");
        return 0;
    }
}

