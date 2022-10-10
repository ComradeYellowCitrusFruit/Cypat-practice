#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "include/guidefile.h"
#include "include/conditions.h"
#include "include/eventLoop.h"
#include "include/log.h"

void runMetacond(COND_Metacond_t *cond)
{
    COND_effect_t *effect = (COND_effect_t*)((uintptr_t)cond +  sizeof(uint16_t));
    for(int i = 0; i < cond->varCount; i++, effect++)
        runEffect(*effect);
}