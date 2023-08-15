#ifndef _UNIT_H
#define _UNIT_H

struct Unit;
typedef struct Unit Unit;

#include "player.h"
#include "position.h"
#include "engine.h"
#include "attacktype.h"
#include "trainable_unit_list.h"
#include <stdio.h>

struct Unit
{
    int health, max_health;

    int attack_damage_min;
    int attack_damage_max;
    int attack_range;
    float attack_speed;
    float attack_last_tick;

    float movement_speed;
    float movement_last_tick;
    enum Direction movement_next;

    char is_building;

    float money_income;
    float money_interval;
    float money_income_last_tick;

    float food_income;
    float food_interval;
    float food_income_last_tick;

    float training_time_left;
    TrainableUnitList trainable_units;
    Unit* training_unit;
    char model;
    char* name;
    int custom_name;

    Unit* target;
    Position position;
    Player* owner;

    enum AttackType atk_type;
    enum DefenseType def_type;

    int references;
};

Unit* Unit_NewUnit();
Unit* Unit_NewUnitByTypeName(char* type_name);
void Unit_DeleteUnit(Unit* u);
void Unit_Reference(Unit* u, int ref);
int  Unit_GetReferences(Unit* u);
void Unit_SetName(Unit* u, char* pointer);
void Unit_SetCustomName(Unit* u, char* name);
char* Unit_GetName(Unit* u);
Player* Unit_GetOwner(Unit* u);
void Unit_SetOwner(Unit* u, Player* p);
Position Unit_GetPosition(Unit* u);
void Unit_SetPosition(Unit* u, Position p);
void Unit_MoveDirection(Unit* u, enum Direction d);
char Unit_CanMove(Unit* u);
char Unit_IsMovementExhausted(Unit* u, float time);
void Unit_SetLastMoveTick(Unit* u, float time);
int Unit_GetHealth(Unit* u);
int Unit_GetMaxHealth(Unit* u);
void Unit_SetHealth(Unit* u, int health);
void Unit_AddHealth(Unit* u, int delta);
void Unit_SetMaxHealth(Unit* u, int max);
void Unit_Kill(Unit* u);
char Unit_IsAlive(Unit* u);
void Unit_SetAttackDamage(Unit* u, int damage_min, int damage_max);
void Unit_GetAttackDamage(Unit* u, int* out_damage_min, int* out_damage_max);
void Unit_SetAttackRange(Unit* u, int range);
int Unit_GetAttackRange(Unit* u);
void Unit_SetAttackSpeed(Unit* u, float speed);
float Unit_GetAttackSpeed(Unit* u);
void Unit_SetMovementSpeed(Unit* u, float speed);
void Unit_SetModel(Unit* u, char model);
char Unit_GetModel(Unit* u);
void Unit_SetBuilding(Unit* u, int b);
int Unit_IsBuilding(Unit* u);
void Unit_SetTarget(Unit* u, Unit* target);
Unit* Unit_GetTarget(Unit* u);
void Unit_SetMoneyIncome(Unit* u, float income, float interval);
void Unit_GetMoneyIncome(Unit* u, float* out_income, float* out_interval);
void Unit_SetFoodIncome(Unit* u, float income, float interval);
void Unit_GetFoodIncome(Unit* u, float* out_income, float* out_interval);
void Unit_GenerateIncome(Unit* u, float time);
void Unit_GetIncomePerSecond(Unit* u, float* money, float* food);
char Unit_IsAlly(Unit* u, Unit* target);
char Unit_CanAttack(Unit* u);
char Unit_IsAttackExhausted(Unit* u, float time);
int Unit_CalculateHitDamage(Unit* u, Unit* target);
void Unit_Attack(Unit* u, Unit* target);
void Unit_SetLastAttack(Unit* u, float time);
void Unit_TrainUnit(Unit* u, int index);
int Unit_IsTraining(Unit* u);
Unit* Unit_CheckTraining(Unit* u, float time);
char* Unit_GetTrainingUnitName(Unit* u);
float Unit_GetTrainingTimeLeft(Unit* u);
void Unit_CancelTraining(Unit* u);
void Unit_SaveToFile(Unit* u, FILE* f, Player* e);
Unit* Unit_LoadFromFile(FILE* f);
#endif
