#ifndef _UNITTYPE_H
#define _UNITTYPE_H

#include "trainable_unit_list.h"
#include "unit.h"
#include "attacktype.h"

struct UnitType
{
    int code;

    char* name;
    int max_health;

    int attack_damage_min;
    int attack_damage_max;
    int attack_range;
    float attack_speed;

    float movement_speed;
    char is_building;

    int money_income;
    float money_interval;

    int food_income;
    float food_interval;

    int money_cost, food_cost;
    float train_time;

    TrainableUnitList trainable_units;
    char model;
    enum AttackType atk_type;
    enum DefenseType def_type;
};

typedef struct UnitType UnitType;

int UnitType_InitUnit(Unit* u, UnitType* utype);
UnitType*  UnitType_GetType(char* type_name);
int  UnitType_AddType(char* type_name, UnitType type);
void UnitType_Clear();

#endif // _UNITTYPE_H
