#ifndef _UNITLIST_H
#define _UNITLIST_H

#include "unit.h"

struct UnitList;
struct UnitListIterator;
typedef struct UnitList UnitList;
typedef struct UnitListIterator UnitListIterator;
typedef struct UnitListNode UnitListNode;

struct UnitListIterator
{
    UnitList* list;
    struct UnitListNode* node;
};

struct UnitListNode
{
    Unit* unit;
    struct UnitListNode* next, *previous;
};

struct UnitList
{
    struct UnitListNode* node;
    unsigned size;
};

UnitList* UnitList_NewUnitList();

void UnitList_ClearUnitList(UnitList* list);

void UnitList_DeleteUnitList(UnitList* list);

void UnitList_AddUnit(UnitList* list, Unit* u);

int UnitList_GetSize(UnitList* list);

UnitListIterator UnitListIterator_New(UnitList* list);
void UnitListIterator_Begin(UnitListIterator* iterator);
void UnitListIterator_Next(UnitListIterator* iterator);
void UnitListIterator_Erase(UnitListIterator* iterator);
int  UnitListIterator_HasNext(UnitListIterator* iterator);
int  UnitListIterator_Finished(UnitListIterator* iterator);
Unit* UnitListIterator_GetUnit(UnitListIterator* iterator);


#endif // _UNITLIST_H
