/****************************************************************************/
// vec_add_kernel.cpp
// Copyright (C) 2017 Falcon Computing Solutions, Inc. - All rights reserved.
/****************************************************************************/

#include "vec_add.h"

#pragma ACCEL kernel
void vec_add_kernel(int a[VEC_SIZE], int b[VEC_SIZE], int c[VEC_SIZE], int inc)
{
    int j;
#pragma ACCEL parallel factor=16
    for (j = 0 ;j < VEC_SIZE; j++) { 
        c[j] = a[j]+b[j]+inc;
    }
}

