/*
*
*   src/runEffect.c   
*   Originally written by Alicia Antó Valencía - https://github.com/ComradeYellowCitrusFruit
*
*   Cyber Competition Suite - A collection of programs for cybersecurity competitions and practices
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