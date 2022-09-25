#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/eventLoop.h"
#include "include/guidefile.h"
#include "include/log.h"

GF_STATE_T gf_state;

void initState(FILE *guidefile)
{
    fread(&(gf_state.header), sizeof(GF_Header_t), 1, guidefile);
    rewind(guideFile);
    log("Guidefile header read and initialized in gf_state at address %p.", (void*)&(gf_state.header));
    gf_state.score = &score;
    log("gf_state.score, located at address %p, initialized to address %p.", (void*)&(gf_state.score), (void*)&score);
    gf_state.vars = calloc(gf_state.header.varCount, sizeof(int32_t));
    log("%u bytes allocate for %u variables allocated at address %p.", gf_state.header.varCount * sizeof(int32_t), gf_state.header.varCount, (void*)(gf_state.vars));
    log("gf_state fully initalized.");
    return;
}