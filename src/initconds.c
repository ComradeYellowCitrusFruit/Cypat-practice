#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "include/guidefile.h"
#include "include/conditions.h"
#include "include/eventLoop.h"
#include "include/log.h"

void runInitConds()
{
    log("Starting to execute initconditions.");
    fseek(guideFile, gf_state.header.offset, SEEK_SET);
    for(size_t i = 0; i < gf_state.header.conditionCount; i++)
    {
        COND_Header_t header;
        fread(&header, sizeof(COND_Header_t), 1, guideFile);
        if(header.typeCode == 0xFE)
        {
            COND_Initcond_t cond;
            fread(&cond, sizeof(COND_Initcond_t), 1, guideFile);
            COND_var_t *vars = malloc(sizeof(COND_var_t) * cond.varCount);
            fread(vars, sizeof(COND_var_t), cond.varCount, guideFile);
            for(uint16_t j = 0; j < cond.varCount; i++)
            {
                gf_state.vars[vars[j].varCode] = vars[j].val;
                log("Var %"PRIu16" has been initalized to %"PRId32, vars[j].varCode, vars[j].val);
            }
        }
        fseek(guideFile, header.nextOffset, SEEK_SET);
    }
    rewind(guideFile);
    log("Finished executing initconditions.");
    return;
}