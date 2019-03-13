#ifndef _ATTACK_TYPE_H
#define _ATTACK_TYPE_H

enum AttackType
{
    Attack_None,
    Attack_Arrow,
    Attack_Sword,
    Attack_Cannon,
    Attack_Normal
};

enum DefenseType
{
    Defense_None,
    Defense_Shield,
    Defense_Metal,
    Defense_Mobile
};

float AttackType_GetMultiplier(enum AttackType atk, enum DefenseType def);

#endif // _ATTACK_TYPE_H
