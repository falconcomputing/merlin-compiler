#include <assert.h>

#define VS 4096

typedef float DT;

#pragma ACCEL kernel
void dot_kernel(const DT a[VS], const DT b[VS], DT c[1]) {
   DT prod = 0;

#pragma ACCEL parallel factor=64
 for (int i = 0; i < VS; i++)
       prod += a[i]*b[i];
  *c = prod;
}
