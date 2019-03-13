#include "attacktype.h"

/* Matriz com os multiplicadores dos tipos. */
float _atk_multipliers[4][4] = {
    {1.f, 0.7f, 0.5f, 1.4f},
    {1.5f, 1.f, 0.7f, 1.8f},
    {0.8f, 0.5f, 2.8f, 0.9f},
    {1.f, 1.f, 1.f, 1.f}
};

float AttackType_GetMultiplier(enum AttackType atk, enum DefenseType def)
{
    return _atk_multipliers[(int)atk][(int)def];
}
