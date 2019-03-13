#ifndef _ENGINE_H
#define _ENGINE_H

struct Engine;
typedef struct Engine Engine;

#include "map.h"
#include "unitlist.h"
#include <stdio.h>

struct Engine
{
    Player *player, *cpu;
    Map* map;
    UnitList* units;
    float time;
    float last_delta;
    char finished;
};

Engine* Engine_NewEngine();

void Engine_Clear();
void Engine_Delete(Engine* e);
void Engine_StartGame(Engine* e, MapProperties props);
void Engine_AdvanceTime(Engine* e, float delta);
void Engine_KillUnit(Engine* e, Unit* u, Unit* killer);
void Engine_HideUnit(Engine* e, Unit* u);
void Engine_CheckUnitTraining(Engine* e, Unit* u);
void Engine_CheckUnitAttack(Engine* e, Unit* u);
void Engine_MoveUnit(Engine* e, Unit* u, enum Direction dir);
Map* Engine_GetMap(Engine* e);
Player* Engine_GetPlayer(Engine* e);
float Engine_GetTime(Engine* e);
Unit* Engine_GetUnitFromPos(Engine* e, Position p);
Unit* Engine_GetEnemyHeadquarter(Engine* e, Player* p);
void Engine_CheckCPUAI(Engine* e);
char Engine_HasFinished(Engine* e);
int Engine_SaveToFile(Engine* e, FILE* f);
Engine* Engine_LoadFromFile(FILE* f);

void Engine_UnitSetTarget(Engine* e, Unit* u, Unit* target);

#endif // _ENGINE_H
