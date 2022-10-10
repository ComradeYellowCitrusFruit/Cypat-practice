/*
*
*   src/isqrt.c   
*   Originally from https://github.com/AlanCxxx/isqrt/blob/master/isqrt.c
*   Originally written by https://github.com/AlanCxxx
*
*   A collection of programs for cybersecurity competitions and practices
*   Copyright (C) 2022  Alicia Antó Valencía
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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