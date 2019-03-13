#include <stdlib.h>
#include "player.h"

Player* Player_NewPlayer(unsigned initial_money, unsigned initial_food)
{
    Player* p = (Player*) malloc (sizeof(Player));
    if (p)
    {
        p->money = initial_money;
        p->food = initial_food;
        p->camera_row = p->camera_col = 0;
        p->money_income = p->food_income = 0.;
        p->unit_count = 0;
        p->headquarter = p->selected_unit = NULL;
    }
    return p;
}

void Player_DeletePlayer(Player* p)
{
    if (p)
        free(p);
}

int Player_HasResources(Player* p, int money, int food)
{
    return p && p->money >= money && p->food >= food;
}

void Player_AddResources(Player* p, int money, int food)
{
    if (p)
    {
        p->money += money;
        p->food += food;
    }
}

void Player_SetHeadquarter(Player* p, Unit* u)
{
    if (p)
        p->headquarter = u;
}

Unit* Player_GetHeadquarter(Player* p)
{
    return p ? p->headquarter : NULL;
}

void Player_GetResources(Player* p, int* money, int* food)
{
    if (!p || !money || !food)
        return;
    *money = p->money;
    *food = p->food;
}

void Player_GetCamera(Player* p, int* row, int* col)
{
    if (!p || !row || !col)
        return;
    *row = p->camera_row;
    *col = p->camera_col;
}

int Player_GetUnitCount(Player* p)
{
    return p ? p->unit_count : 0;
}

void Player_GetIncome(Player* p, float* money, float* food)
{
    if (!p || !money || !food)
        return;
    *money = p->money_income;
    *food = p->food_income;
}

void Player_AddUnit(Player* p, int count)
{
    if (p)
        p->unit_count += count;
}

void Player_AddIncome(Player* p, float money, float food)
{
    if (p)
    {
        p->money_income += money;
        p->food_income += food;
    }
}

void Player_SelectUnit(Player* p, Unit* u)
{
    if (p)
    {
        Unit_Reference(p->selected_unit, -1);
        p->selected_unit = u;
        Unit_Reference(u, 1);
    }
}

Unit* Player_GetSelectedUnit(Player* p)
{
    if (!p || !p->selected_unit)
        return NULL;

    if (!Unit_IsAlive(p->selected_unit))
        Player_SelectUnit(p, NULL);

    return p->selected_unit;
}

int Player_Pay(Player* p, int money, int food)
{
    if (p && p->money >= money && p->food >= food)
    {
        p->money -= money;
        p->food -= food;
        return 1;
    }
    return 0;
}
