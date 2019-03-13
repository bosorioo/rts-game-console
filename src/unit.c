#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "unit.h"
#include "unitlist.h"
#include "unittype.h"
#include "report.h"

Unit* Unit_NewUnit()
{
    Unit* u = (Unit*)malloc(sizeof(Unit));

    if (u)
    {
        u->health = 0;
        u->max_health = 0;

        u->attack_damage_min = 0;
        u->attack_damage_max = 0;
        u->attack_range = 0;
        u->attack_speed = 0.;
        u->attack_last_tick = 0.;

        u->movement_speed = 0.;
        u->movement_last_tick = 0.;

        u->is_building = 0;

        u->money_income = 0.;
        u->money_interval = 0.;
        u->money_income_last_tick = 0.;

        u->food_income = 0.;
        u->food_interval = 0.;
        u->food_income_last_tick = 0.;

        u->training_time_left = 0.;
        u->trainable_units = TrainableUnitList_Create(NULL);
        u->training_unit = NULL;
        u->model = '?';
        u->name = "No Unit";
        u->custom_name = 0;

        u->target = 0;
        u->position = Position_NewPosition(0, 0);
        u->owner = NULL;

        u->atk_type = Attack_None;
        u->def_type = Defense_None;

        u->references = 0;
    }

    return u;
}

Unit* Unit_NewUnitByTypeName(char* type_name)
{
    Unit* u = Unit_NewUnit();

    if (u && type_name)
    {
        UnitType* utype = UnitType_GetType(type_name);
        UnitType_InitUnit(u, utype);
    }

    return u;
}

void Unit_DeleteUnit(Unit* u)
{
    if (u)
        free(u);
}

void Unit_Reference(Unit* u, int ref)
{
    if (!u)
        return;

    u->references += ref >= 0 ? 1 : -1;
}

int Unit_GetReferences(Unit* u)
{
    return u ? u->references : -1;
}

void Unit_SetName(Unit* u, char* pointer)
{
    if (u)
    {
        if (u->name && u->custom_name)
            free(u->name);
        u->name = pointer;
        u->custom_name = 0;
    }
}

void Unit_SetCustomName(Unit* u, char* name)
{
    if (u)
    {
        if (u->name && u->custom_name)
            free(u->name);
        u->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
        if (u->name)
        {
            strcpy(u->name, name);
            u->custom_name = 1;
        }
    }
}

char* Unit_GetName(Unit* u)
{
    return u ? u->name : NULL;
}

Player* Unit_GetOwner(Unit* u)
{
    return u ? u->owner : NULL;
}

void Unit_SetOwner(Unit* u, Player* p)
{
    if (u && p)
        u->owner = p;
}

Position Unit_GetPosition(Unit* u)
{
    return u ? u->position : Position_NewPosition(-1, -1);
}

void Unit_SetPosition(Unit* u, Position p)
{
    if (u)
        u->position = p;
}

void Unit_MoveDirection(Unit* u, enum Direction d)
{
    if (u)
    {
        u->position = Position_Moved(u->position, d);
    }
}

char Unit_CanMove(Unit* u)
{
    return u && u->training_time_left <= 0. && u->movement_speed > 0.;
}

float Unit_GetMovementExhaustion(Unit* u, float time)
{
    if (!u || u->movement_speed <= 0.)
    {
        return INFINITY;
    }

    return time - u->movement_last_tick;
}

char Unit_IsMovementExhausted(Unit* u, float time)
{
    return Unit_GetMovementExhaustion(u, time) < 0;
}

void Unit_SetLastMoveTick(Unit* u, float time)
{
    if (u)
        u->movement_last_tick = time + 1. / u->movement_speed;
}

int Unit_GetHealth(Unit* u)
{
    return u ? u->health : 0;
}

int Unit_GetMaxHealth(Unit* u)
{
    return u ? u->max_health : 0;
}

void Unit_SetHealth(Unit* u, int health)
{
    if (u)
        u->health = health > u->max_health ? u->max_health : health;
}

void Unit_AddHealth(Unit* u, int delta)
{
    Unit_SetHealth(u, delta + Unit_GetHealth(u));
}

void Unit_SetMaxHealth(Unit* u, int max)
{
    if (u)
    {
        u->max_health = max;
        if (u->health > max)
            u->health = max;
    }
}

void Unit_Kill(Unit* u)
{
    if (u)
        Unit_SetHealth(u, 0);
}

char Unit_IsAlive(Unit* u)
{
    return u && u->health > 0;
}

void Unit_SetAttackDamage(Unit* u, int damage_min, int damage_max)
{
    if (u)
    {
        u->attack_damage_min = damage_min;
        u->attack_damage_max = damage_max;
    }
}

void Unit_GetAttackDamage(Unit* u, int* out_damage_min, int* out_damage_max)
{
    if (!u)
        return;

    if (out_damage_min)
        *out_damage_min = u->attack_damage_min;

    if (out_damage_max)
        *out_damage_max = u->attack_damage_max;
}

void Unit_SetAttackRange(Unit* u, int range)
{
    if (u)
    {
        u->attack_range = range;
    }
}

int Unit_GetAttackRange(Unit* u)
{
    return u ? u->attack_range : -1;
}

void Unit_SetAttackSpeed(Unit* u, float speed)
{
    if (u)
    {
        u->attack_speed = speed;
    }
}

float Unit_GetAttackSpeed(Unit* u)
{
    return u ? u->attack_speed : -1;
}

void Unit_SetMovementSpeed(Unit* u, float speed)
{
    if (u)
        u->movement_speed = speed;
}

void Unit_SetModel(Unit* u, char model)
{
    if (u)
        u->model = model;
}

char Unit_GetModel(Unit* u)
{
    return u ? u->model : 0;
}

void Unit_SetBuilding(Unit* u, int b)
{
    if (u)
        u->is_building = b;
}

int Unit_IsBuilding(Unit* u)
{
    return u ? u->is_building : 0;
}

void Unit_SetTarget(Unit* u, Unit* target)
{
    if (u)
    {
        if (u->target)
            Unit_Reference(u->target, -1);

        if (target && Unit_IsAlive(target))
        {
            Unit_Reference(target, 1);
            u->target = target;
        }
        else
            u->target = NULL;
    }
}

Unit* Unit_GetTarget(Unit* u)
{
    if (!u || !u->target)
        return NULL;

    if (!Unit_IsAlive(u->target))
    {
        Unit_Reference(u->target, -1);
        u->target = NULL;
    }

    return u->target;
}

void Unit_SetMoneyIncome(Unit* u, float income, float interval)
{
    if (u)
    {
        u->money_income = income;
        u->money_interval = interval;
    }
}

void Unit_GetMoneyIncome(Unit* u, float* out_income, float* out_interval)
{
    if (!u)
        return;

    if (out_income)
        *out_income = u->money_income;

    if (out_interval)
        *out_interval = u->money_interval;
}

void Unit_SetFoodIncome(Unit* u, float income, float interval)
{
    if (u)
    {
        u->food_income = income;
        u->food_interval = interval;
    }
}

void Unit_GetFoodIncome(Unit* u, float* out_income, float* out_interval)
{
    if (!u)
        return;

    if (out_income)
        *out_income = u->food_income;

    if (out_interval)
        *out_interval = u->food_interval;
}

void Unit_GenerateIncome(Unit* u, float time)
{
    if (u && u->owner)
    {
        if (u->money_income_last_tick + u->money_interval <= time)
        {
            u->money_income_last_tick = time;
            Player_AddResources(u->owner, u->money_income, 0);
        }

        if (u->food_income_last_tick + u->food_interval <= time)
        {
            u->food_income_last_tick = time;
            Player_AddResources(u->owner, 0, u->food_income);
        }
    }
}

void Unit_GetIncomePerSecond(Unit* u, float* out_money, float* out_food)
{
    if (u)
    {
        if (out_money)
            *out_money = u->money_interval ? u->money_income / u->money_interval : 0;

        if (out_food)
            *out_food = u->food_interval ? u->food_income / u->food_interval : 0;
    }
}

char Unit_IsAlly(Unit* u, Unit* target)
{
    return u && target && u->owner == target->owner;
}

char Unit_CanAttack(Unit* u)
{
    return u && u->attack_speed > 0 && u->attack_damage_min > 0 && u->attack_damage_max >= u->attack_damage_min && u->attack_range > 0;
}

float Unit_GetAttackExhaustion(Unit* u, float time)
{
    if (!u || u->attack_speed <= 0.)
    {
        return INFINITY;
    }

    return time - u->attack_last_tick;
}

char Unit_IsAttackExhausted(Unit* u, float time)
{
    return Unit_GetAttackExhaustion(u, time) < 0.;
}

int Unit_CalculateHitDamage(Unit* u, Unit* target)
{
    if (!u || !target)
        return 0;

    int damage = (u->attack_damage_max - u->attack_damage_min + 1);

    if (damage > 1)
    {
        damage = (rand() % damage);
    }

    damage += u->attack_damage_min;

    return damage * AttackType_GetMultiplier(u->atk_type, target->def_type);
}

void Unit_Attack(Unit* u, Unit* target)
{
    if (!u || !target || !Unit_IsAlive(u) || !Unit_IsAlive(target))
        return;

    int damage = Unit_CalculateHitDamage(u, target);

    if (damage > 0)
        Unit_AddHealth(target, -damage);
}

void Unit_SetLastAttack(Unit* u, float time)
{
    if (u)
        u->attack_last_tick = time + 1. / u->attack_speed;
}

void Unit_TrainUnit(Unit* u, int index)
{
    if (!u || Unit_IsTraining(u))
        return;

    TrainableUnit* tu = TrainableUnitList_Get(&u->trainable_units, index);

    if (!tu)
        return;

    UnitType* type = UnitType_GetType(tu->unit_name);

    if (type && Player_Pay(Unit_GetOwner(u), type->money_cost, type->food_cost))
    {
        u->training_unit = Unit_NewUnit();
        u->training_time_left = type->train_time;
        UnitType_InitUnit(u->training_unit, type);
        Unit_SetOwner(u->training_unit, u->owner);
    }
}

int Unit_IsTraining(Unit* u)
{
    return u && u->training_unit && Unit_IsAlive(u);
}

Unit* Unit_CheckTraining(Unit* u, float delta)
{
    if (!u || !Unit_IsAlive(u))
        return NULL;

    if (u->training_time_left > 0.)
        u->training_time_left -= delta;

    if (u->training_time_left <= 0.)
        return u->training_unit;

    return NULL;
}

char* Unit_GetTrainingUnitName(Unit* u)
{
    return u && Unit_IsTraining(u) ? Unit_GetName(u->training_unit) : NULL;
}

float Unit_GetTrainingTimeLeft(Unit* u)
{
    return u ? u->training_time_left : -1.;
}

void Unit_CancelTraining(Unit* u)
{
    if (u)
    {
        u->training_unit = NULL;
        u->training_time_left = -1;
    }
}

void Unit_SaveToFile(Unit* u, FILE* f, Player* p)
{
    if (!f || !u)
        return;

    // int int_value;

    // int_value = strlen(u->name);
    // fwrite(&int_value, sizeof(int), 1, f);
    // fwrite(u->name, sizeof(char), int_value, f);
    // fwrite(&u->position.x, sizeof(int), 1, f);
    // fwrite(&u->position.y, sizeof(int), 1, f);
    // fwrite(&u->health, sizeof(int), 1, f);
    // fwrite(&u->last_move, sizeof(int), 1, f);
    // fwrite(&u->last_attack, sizeof(int), 1, f);
    // fwrite(&u->last_money_income, sizeof(int), 1, f);
    // fwrite(&u->last_food_income, sizeof(int), 1, f);
    // fwrite(&u->train_time, sizeof(int), 1, f);
    // fwrite(&u->references, sizeof(int), 1, f);
    // int_value = p == u->owner;
    // fwrite(&int_value, sizeof(int), 1, f);
    // int_value = u->training_unit != NULL;
    // fwrite(&int_value, sizeof(int), 1, f);
    // if (int_value)
        // Unit_SaveToFile(u->training_unit, f, p);
}

Unit* Unit_LoadFromFile(FILE* f)
{
    // if (!f)
        // return NULL;

    // int int_value;
    // char buffer[100];

    // if (!fread(&int_value, sizeof(int), 1, f) ||
        // !fread(buffer, sizeof(char), int_value, f))
        // return NULL;

    // buffer[int_value] = '\0';

    // Unit* u = Unit_NewUnit(buffer);
    // RASSERT(u != NULL, Failed to allocate memory to load unit from file.);

    // if(!fread(&u->position.x, sizeof(int), 1, f) ||
       // !fread(&u->position.y, sizeof(int), 1, f) ||
       // !fread(&u->health, sizeof(int), 1, f) ||
       // !fread(&u->last_move, sizeof(int), 1, f) ||
       // !fread(&u->last_attack, sizeof(int), 1, f) ||
       // !fread(&u->last_money_income, sizeof(int), 1, f) ||
       // !fread(&u->last_food_income, sizeof(int), 1, f) ||
       // !fread(&u->train_time, sizeof(int), 1, f) ||
       // !fread(&u->references, sizeof(int), 1, f) ||
       // !fread(&u->owner, sizeof(int), 1, f) ||
       // !fread(&u->training_unit, sizeof(Unit*), 1, f))
    // {
        // Unit_DeleteUnit(u);
        // return NULL;
    // }

    // if (u->training_unit)
        // u->training_unit = Unit_LoadFromFile(f);

    // return u;

    return NULL;
}
