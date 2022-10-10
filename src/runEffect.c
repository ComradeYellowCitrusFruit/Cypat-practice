#include "include/eventLoop.h"
#include "include/guidefile.h"
#include "include/conditions.h"
#include "include/isqrt.h"

/* Execute an effect */
void runEffect(COND_effect_t effect)
{
    if(effect.varOrScore)
    {
        switch(effect.effect)
        {
            case 0xFF:
                /* Set var[effect.var.varCode] to effect.var.val */
                gf_state.vars[effect.var.varCode] = effect.var.val;
                break;
            case 0x01:
                /* Add effect.var.val to var[effect.var.varCode] */
                gf_state.vars[effect.var.varCode] += effect.var.val;
                break;
            case 0x02:
                /* Subtract effect.var.val to var[effect.var.varCode] */
                gf_state.vars[effect.var.varCode] -= effect.var.val;
                break;
            case 0x03:
                /* Multiply var[effect.var.varCode] by effect.var.val */
                gf_state.vars[effect.var.varCode] *= effect.var.val;
                break;
            case 0x04:
                /* Divide var[effect.var.varCode] by effect.var.val */
                gf_state.vars[effect.var.varCode] /= effect.var.val;
                break;
            case 0x10:
                /* OR var[effect.var.varCode] with effect.var.val */
                gf_state.vars[effect.var.varCode] |= effect.var.val;
                break;
            case 0x11:
                /* AND var[effect.var.varCode] with effect.var.val */
                gf_state.vars[effect.var.varCode] &= effect.var.val;
                break;
            case 0x12:
                /* XOR var[effect.var.varCode] with effect.var.val */
                gf_state.vars[effect.var.varCode] &= effect.var.val;
                break;
            case 0x13:
                /* NOT var[effect.var.varCode] */
                ~gf_state.vars[effect.var.varCode];
                break;
            case 0x14:
                /* Lshift var[effect.var.varCode] by effect.var.val */
                gf_state.vars[effect.var.varCode] <<= effect.var.val;
                break;
            case 0x15:
                /* Rshift var[effect.var.varCode] by effect.var.val */
                gf_state.vars[effect.var.varCode] >>= effect.var.val;
                break;
            case 0x20:
                /* Raise var[effect.var.varCode] to the power of effect.var.val */
                gf_state.vars[effect.var.varCode] = (var_t)ipow(gf_state.vars[effect.var.varCode], effect.var.val);
                break;
            case 0x21:
                /* Set var[effect.var.varCode] to it's square root */
                gf_state.vars[effect.var.varCode] = (var_t)isqrt(gf_state.vars[effect.var.varCode]);
                break;
        }
    }
    else
        score += effect.score;
}