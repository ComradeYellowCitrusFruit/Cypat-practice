/*
*
*   include/isqrt.h   
*   Originally written by Alicia Antó Valencía - https://github.com/ComradeYellowCitrusFruit
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

#ifndef INTEGER_SQUARE_ROOT_H
#define INTEGER_SQUARE_ROOT_H

#include <stdint.h>

/* Integer square root, using code I stole from someone then modified the types of */
size_t isqrt(size_t x);
/* Integer power, I wrote the code, in other words op^exponent */
size_t ipow(size_t op, size_t exponent);

#endif