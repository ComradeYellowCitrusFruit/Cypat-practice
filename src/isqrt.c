#include <stdint.h>
#include "include/isqrt.h"

/* Integer square root, using code I stole from someone then modified the types of */
size_t isqrt(size_t x)
{
  size_t opr=(size_t)x;
  size_t res=0;
  size_t one=1<<30;

  while (one>opr) one>>=2;
  while (one!=0) {
    if (opr>=res+one) {
      opr=opr-res-one;
      res=res+(one<<1);
    }
    res>>=1;
    one>>=2;
  }
  // if (opr>res) res++; // Round up
  return (int)res;
}

/* Integer power, I wrote the code, in other words op^exponent */
size_t ipow(size_t op, size_t exponent)
{
    size_t ret = 1;
    if(exponent)
    {
        for(size_t i = 0; i < exponent; i++)
            ret *= op;
    }
    return ret;
}