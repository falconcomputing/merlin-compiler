/****************************************************************************/
// vec_add.cpp
// Copyright (C) 2017 Falcon Computing Solutions, Inc. - All rights reserved.
/****************************************************************************/

#include "vec_add.h"

void vec_add(int *a, int *b, int*c, int inc)
{
    int j;
    for (j = 0 ;j < VEC_SIZE; j++) { 
        c[j] = a[j]+b[j]+inc;
    }
}

