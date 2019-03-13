#include <stdlib.h>
#include <string.h>
#include "unittype.h"
#include "unit.h"

struct UnitTypes
{
    char* id;
    UnitType* type;
    struct UnitTypes* next;
};

struct UnitTypes* UNIT_TYPES = NULL;

int UnitType_InitUnit(Unit* u, UnitType* utype)
{
    if (!utype || !u)
        return 0;

    Unit_SetName(u, utype->name);
    Unit_SetMaxHealth(u, utype->max_health);
    Unit_SetHealth(u, utype->max_health);

    Unit_SetAttackDamage(u, utype->attack_damage_min, utype->attack_damage_max);
    Unit_SetAttackRange(u, utype->attack_range);
    Unit_SetAttackSpeed(u, utype->attack_speed);

    Unit_SetMovementSpeed(u, utype->movement_speed);
    Unit_SetBuilding(u, utype->is_building);
    Unit_SetMoneyIncome(u, utype->money_income, utype->money_interval);
    Unit_SetFoodIncome(u, utype->food_income, utype->food_interval);
    Unit_SetModel(u, utype->model);
    u->trainable_units = utype->trainable_units;
    u->atk_type = utype->atk_type;
    u->def_type = utype->def_type;

    return 1;
}

UnitType* UnitType_GetType(char* type_name)
{
    struct UnitTypes* t = UNIT_TYPES;
    while (t)
    {
        if (!strcmp(t->id, type_name))
            return t->type;
        t = t->next;
    }
    return NULL;
}

int UnitType_AddType(char* type_name, UnitType type)
{
    struct UnitTypes* newType = (struct UnitTypes*)malloc(sizeof(struct UnitTypes));

    if (!newType)
        return 0;

    newType->type = (UnitType*)malloc(sizeof(UnitType));

    if (!newType->type)
    {
        free(newType);
        return 0;
    }

    *(newType->type) = type;
    newType->next = UNIT_TYPES;
    newType->id = (char*)malloc(sizeof(char) * (strlen(type_name) + 1));

    if (!newType->id)
    {
        free(newType->type);
        free(newType);
        return 0;
    }

    strcpy(newType->id, type_name);
    UNIT_TYPES = newType;

    return 1;
}

void UnitType_Clear()
{
    struct UnitTypes* iterator = UNIT_TYPES, *eraser;
    while (iterator)
    {
        eraser = iterator;
        iterator = iterator->next;
        free(eraser->type);
        free(eraser->id);
        free(eraser);
    }
    UNIT_TYPES = NULL;
}
