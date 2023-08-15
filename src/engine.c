#include <stdlib.h>
#include "engine.h"
#include "player.h"
#include "unit.h"
#include "unitlist.h"
#include "map.h"
#include "display.h"
#include "report.h"

void Engine_Init(Engine* e)
{
    if (e)
    {
        e->player = e->cpu = NULL;
        e->units = NULL;
        e->time = 0.;
        e->map = NULL;
        e->finished = 0;
    }
}

Engine* Engine_NewEngine()
{
    Engine* e = (Engine*)malloc(sizeof(Engine));
    Engine_Init(e);
    return e;
}

void Engine_Clear(Engine* e)
{
    if (!e)
        return;

    if (e->player)
        Player_DeletePlayer(e->player);

    if (e->cpu)
        Player_DeletePlayer(e->cpu);

    if (e->units)
        UnitList_DeleteUnitList(e->units);

    if (e->map)
        Map_Delete(e->map);

    Engine_Init(e);
}

void Engine_Delete(Engine* e)
{
    if (!e)
        return;

    Engine_Clear(e);
    free(e);
}

void Engine_StartGame(Engine* e, MapProperties props)
{
    if (!e)
        return;

    Engine_Clear(e);
    Engine_Init(e);

    e->map = Map_NewMap(props);
    e->player = Player_NewPlayer(props.money, props.food);
    e->cpu = Player_NewPlayer(props.money, props.food);
    e->units = UnitList_NewUnitList();

    Unit *player_hq = Unit_NewUnitByTypeName("Headquarter"),
         *cpu_hq    = Unit_NewUnitByTypeName("Headquarter");

    float money, food;

    Unit_SetOwner(player_hq, e->player);
    Unit_SetOwner(cpu_hq, e->cpu);

    Player_SetHeadquarter(e->player, player_hq);
    Player_SetHeadquarter(e->cpu, cpu_hq);

    Unit_GetIncomePerSecond(player_hq, &money, &food);

    Player_AddUnit(e->player, 1);
    Player_AddIncome(e->player, money, food);
    Player_AddUnit(e->cpu, 1);
    Player_AddIncome(e->cpu, money, food);

    Unit_SetPosition(player_hq, Position_NewPosition(6, 3));
    Unit_SetPosition(cpu_hq, Position_NewPosition(props.width - 7, props.height - 4));

    Map_AddUnit(e->map, player_hq);
    Map_AddUnit(e->map, cpu_hq);

    UnitList_AddUnit(e->units, player_hq);
    UnitList_AddUnit(e->units, cpu_hq);
}

void Engine_AdvanceTime(Engine* e, float delta)
{
    if (!e)
        return;

    e->last_delta = delta;
    e->time += delta;

    Engine_CheckCPUAI(e);

    UnitListIterator ulit = UnitListIterator_New(e->units);

    while (!UnitListIterator_Finished(&ulit))
    {
        Unit* unit = UnitListIterator_GetUnit(&ulit);

        if (!Unit_IsAlive(unit))
        {
            if (Unit_GetReferences(unit) == 0)
                UnitListIterator_Erase(&ulit);
            else
                UnitListIterator_Next(&ulit);
            continue;
        }

        if (unit->movement_next != None)
        {
            Engine_MoveUnit(e, unit, unit->movement_next);
        }

        Engine_CheckUnitAttack(e, unit);
        Engine_CheckUnitTraining(e, unit);
        Unit_GenerateIncome(unit, e->time);
        UnitListIterator_Next(&ulit);
    }
}

void Engine_CheckCPUAI(Engine* e)
{
    if (!e || !e->cpu)
        return;

    Player* p = e->cpu;

    int workers = 0;
    int archers = 0;
    int warriors = 0;
    int farms = 0;

    UnitListIterator it = UnitListIterator_New(e->units);
    while (!UnitListIterator_Finished(&it))
    {
        Unit* u = UnitListIterator_GetUnit(&it);

        if (Unit_GetOwner(u) == p)
        {
            char model = Unit_GetModel(u);
            if (model == 'v')
            {
                workers++;

                if (workers / 3 > farms)
                    Unit_TrainUnit(u, 0);
                else
                    Engine_HideUnit(e, u);
            }
            else if (model == 'a')
                archers++;
            else if (model == 'w')
                warriors++;
            else if (model == 'F')
                farms++;
        }

        UnitListIterator_Next(&it);
    }

    if (workers <= 1 || archers + warriors > workers / 3)
        Unit_TrainUnit(Player_GetHeadquarter(p), 0);
    else
        Unit_TrainUnit(Player_GetHeadquarter(p), 1 + (rand() % 2));

}

Unit* Engine_GetEnemyHeadquarter(Engine* e, Player* p)
{
    if (!e || !p)
        return NULL;

    if (p == e->cpu)
        return Player_GetHeadquarter(e->player);
    else if (p == e->player)
        return Player_GetHeadquarter(e->cpu);

    return NULL;
}

void Engine_UnitSetTarget(Engine* e, Unit* u, Unit* target)
{
    if (!e || !u || !Unit_IsAlive(u) || !Unit_CanAttack(u))
    {
        return;
    }

    if (!Unit_IsAlive(target) || Unit_IsAlly(u, target))
        target = NULL;

    Unit_SetTarget(u, target);
}

void Engine_CheckUnitAttack(Engine* e, Unit* u)
{
    if (!e || !u)
        return;

    if (!Unit_IsAlive(u) || !Unit_CanAttack(u) || Unit_IsAttackExhausted(u, e->time))
        return;

    Unit* target = Unit_GetTarget(u);

    if (!target)
    {
        target = Map_GetClosestEnemy(e->map, u, 8);

        if (!target)
            target = Engine_GetEnemyHeadquarter(e, u->owner);

        Unit_SetTarget(u, target);
    }
    else if (target == Engine_GetEnemyHeadquarter(e, u->owner))
    {
        Unit* betterTarget = Map_GetClosestEnemy(e->map, u, 36);
        if (betterTarget)
        {
            target = betterTarget;
            Unit_SetTarget(u, betterTarget);
        }
    }

    if (target && Unit_IsAlive(target))
    {
        Position unitPosition = Unit_GetPosition(u);
        Position targetPosition = Unit_GetPosition(target);

        if (Position_IsInRange(unitPosition, targetPosition, Unit_GetAttackRange(u)))
        {
            Unit_Attack(u, target);
            Unit_SetLastAttack(u, e->time);

            if (!Unit_IsAlive(target))
            {
                Engine_KillUnit(e, target, NULL);
                Unit_SetTarget(u, NULL);
            }
        }
        else if (Player_GetSelectedUnit(Unit_GetOwner(u)) != u)
        {
            enum Direction dir = Map_GetDirectionTo(e->map, unitPosition, targetPosition);
            Engine_MoveUnit(e, u, dir);
        }
    }
}

void Engine_MoveUnit(Engine* e, Unit* u, enum Direction dir)
{
    if (!e || !Unit_IsAlive(u) || dir == None)
        return;

    if (Unit_CanMove(u) &&
        Map_CanWalk(e->map, Position_Moved(Unit_GetPosition(u), dir)))
    {
        if (Unit_IsMovementExhausted(u, e->time))
        {
            u->movement_next = dir;
        }
        else
        {
            Map_MoveUnit(e->map, u, dir);
            Unit_SetLastMoveTick(u, e->time);
            u->movement_next = None;
        }
    }
}

void Engine_KillUnit(Engine* e, Unit* u, Unit* killer)
{
    if (!e || !u)
        return;

    Map_RemoveUnit(e->map, Unit_GetPosition(u));
    Player_AddUnit(Unit_GetOwner(u), -1);
    float money, food;
    Unit_GetIncomePerSecond(u, &money, &food);
    Player_AddIncome(Unit_GetOwner(u), -money, -food);
    Unit_Kill(u);

    if (u == Player_GetHeadquarter(e->player))
        e->finished = 1;
    else if (u == Player_GetHeadquarter(e->cpu))
        e->finished = 2;
}

void Engine_HideUnit(Engine* e, Unit* u)
{
    if (!e || !u)
        return;

    Map_RemoveUnit(e->map, Unit_GetPosition(u));
    Unit_SetPosition(u, Position_NewPosition(-2, -2));
}

void Engine_CheckUnitTraining(Engine* e, Unit* u)
{
    if (!e || !u)
        return;

    Unit* trained = Unit_CheckTraining(u, e->last_delta);

    if (!trained)
        return;

    Position pos = Unit_GetPosition(u);

    if (!Map_GetClosestFreePosition(e->map, &pos))
        return;

    float money, food;
    Unit_GetIncomePerSecond(trained, &money, &food);
    Player_AddUnit(Unit_GetOwner(trained), 1);
    Player_AddIncome(Unit_GetOwner(trained), money, food);
    Unit_SetPosition(trained, pos);
    Map_AddUnit(e->map, trained);
    UnitList_AddUnit(e->units, trained);
    Unit_CancelTraining(u);
}

Map* Engine_GetMap(Engine* e)
{
    return e ? e->map : NULL;
}

Player* Engine_GetPlayer(Engine* e)
{
    return e ? e->player : NULL;
}

float Engine_GetTime(Engine* e)
{
    return e ? e->time : 0.;
}

Unit* Engine_GetUnitFromPos(Engine* e, Position p)
{
    Unit* u = e && e->map ? Map_GetUnit(e->map, p) : NULL;
    return Unit_IsAlive(u) ? u : NULL;
}

char Engine_HasFinished(Engine* e)
{
    return e ? e->finished : 0;
}

int Engine_SaveToFile(Engine* e, FILE* f)
{
    if (!f || !e)
        return 0;

    int money, food, temp;
    float inc_money, inc_food;

    Position selection_pos = Unit_GetPosition(Player_GetSelectedUnit(e->player));
    Player_SelectUnit(e->player, NULL);

    Player_GetResources(e->player, &money, &food);
    Player_GetIncome(e->player, &inc_money, &inc_food);
    temp = Player_GetUnitCount(e->player);

    fwrite(&selection_pos.x, sizeof(int), 1, f);
    fwrite(&selection_pos.y, sizeof(int), 1, f);
    fwrite(&e->time, sizeof(int), 1, f);
    fwrite(&money, sizeof(int), 1, f);
    fwrite(&food, sizeof(int), 1, f);
    fwrite(&temp, sizeof(int), 1, f);
    fwrite(&inc_money, sizeof(float), 1, f);
    fwrite(&inc_food, sizeof(float), 1, f);

    Player_GetResources(e->cpu, &money, &food);
    Player_GetIncome(e->cpu, &inc_money, &inc_food);
    temp = Player_GetUnitCount(e->cpu);

    fwrite(&money, sizeof(int), 1, f);
    fwrite(&food, sizeof(int), 1, f);
    fwrite(&temp, sizeof(int), 1, f);
    fwrite(&inc_money, sizeof(float), 1, f);
    fwrite(&inc_food, sizeof(float), 1, f);

    UnitListIterator it = UnitListIterator_New(e->units);

    temp = 0;

    while (!UnitListIterator_Finished(&it))
    {
        if (Unit_IsAlive(UnitListIterator_GetUnit(&it)))
            temp++;
        UnitListIterator_Next(&it);
    }

    fwrite(&temp, sizeof(int), 1, f);

    UnitListIterator_Begin(&it);

    while (!UnitListIterator_Finished(&it))
    {
        if (Unit_IsAlive(UnitListIterator_GetUnit(&it)))
            Unit_SaveToFile(UnitListIterator_GetUnit(&it), f, e->player);
        UnitListIterator_Next(&it);
    }

    UnitListIterator_Begin(&it);

    while (!UnitListIterator_Finished(&it))
    {
        if (Unit_IsAlive(UnitListIterator_GetUnit(&it)))
        {
            Unit* target = Unit_GetTarget(UnitListIterator_GetUnit(&it));
            Position p = target ? Unit_GetPosition(target) : Position_NewPosition(-1, -1);
            fwrite(&p.x, sizeof(int), 1, f);
            fwrite(&p.y, sizeof(int), 1, f);
        }
        UnitListIterator_Next(&it);
    }

    return 1;
}

Engine* Engine_LoadFromFile(FILE* f)
{
    if (!f)
        return NULL;

    Engine* e = Engine_NewEngine();

    if (!e)
        return NULL;

    e->map = Map_NewMap(Map_DefaultMap());
    e->player = Player_NewPlayer(0, 0);
    e->cpu = Player_NewPlayer(0, 0);
    e->units = UnitList_NewUnitList();

    int money, food, temp;
    float inc_money, inc_food;
    Position selection_pos;

    if (!fread(&selection_pos.x, sizeof(int), 1, f) ||
        !fread(&selection_pos.y, sizeof(int), 1, f) ||
        !fread(&e->time, sizeof(int), 1, f) ||
        !fread(&money, sizeof(int), 1, f) ||
        !fread(&food, sizeof(int), 1, f) ||
        !fread(&temp, sizeof(int), 1, f) ||
        !fread(&inc_money, sizeof(float), 1, f) ||
        !fread(&inc_food, sizeof(float), 1, f))
    {
        Engine_Delete(e);
        return NULL;
    }

    Player_AddResources(e->player, money, food);
    Player_AddUnit(e->player, temp);
    Player_AddIncome(e->player, inc_money, inc_food);

    if (!fread(&money, sizeof(int), 1, f) ||
        !fread(&food, sizeof(int), 1, f) ||
        !fread(&temp, sizeof(int), 1, f) ||
        !fread(&inc_money, sizeof(float), 1, f) ||
        !fread(&inc_food, sizeof(float), 1, f))
    {
        Engine_Delete(e);
        return NULL;
    }

    Player_AddResources(e->cpu, money, food);
    Player_AddUnit(e->cpu, temp);
    Player_AddIncome(e->cpu, inc_money, inc_food);

    if (!fread(&temp, sizeof(int), 1, f))
    {
        Engine_Delete(e);
        return NULL;
    }

    int i;

    for (i = 0; i < temp; i++)
    {
        Unit* u = Unit_LoadFromFile(f);

        if (u)
        {
            Unit_SetOwner(u, Unit_GetOwner(u) ? e->player : e->cpu);

            if (Unit_GetModel(u) == 'H')
                Player_SetHeadquarter(Unit_GetOwner(u), u);

            UnitList_AddUnit(e->units, u);
            Map_AddUnit(e->map, u);
        }
    }

    Position pos[temp];

    for (i = 0; i < temp; i++)
    {
        if (!fread(&pos[i].x, sizeof(int), 1, f) ||
            !fread(&pos[i].y, sizeof(int), 1, f))
        {
            Engine_Delete(e);
            return NULL;
        }
    }

    UnitListIterator it = UnitListIterator_New(e->units);

    while (temp-- > 0)
    {
        i--;
        Unit* target = Map_GetUnit(e->map, pos[i]);
        if (target)
        {
            Unit_SetTarget(UnitListIterator_GetUnit(&it), target);
            Unit_Reference(target, -1);
        }
        UnitListIterator_Next(&it);
    }

    Player_SelectUnit(e->player, Engine_GetUnitFromPos(e, selection_pos));

    return e;
}
