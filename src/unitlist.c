#include <stdlib.h>
#include <assert.h>
#include "unit.h"
#include "unitlist.h"

UnitList* UnitList_NewUnitList()
{
    UnitList* u = (UnitList*)malloc(sizeof(UnitList));
    if (u)
    {
        u->node = 0;
        u->size = 0;
    }
    return u;
}

void UnitList_ClearUnitList(UnitList* list)
{
    if (!list)
        return;

    UnitListIterator it = UnitListIterator_New(list);
    do
    {
        UnitListIterator_Erase(&it);
    } while (!UnitListIterator_Finished(&it));
}

void UnitList_DeleteUnitList(UnitList* list)
{
    if (!list)
        return;

    UnitList_ClearUnitList(list);
    free(list);
}

UnitListNode* newNode(Unit* u)
{
    UnitListNode* node = (UnitListNode*)malloc(sizeof(UnitListNode));
    if (node)
    {
        node->next = node->previous = NULL;
        node->unit = u;
    }
    return node;
}

void UnitList_AddUnit(UnitList* l, Unit* u)
{

    if (!u || !l)
        return;

    UnitListNode* node = newNode(u);

    if (!node)
        return;

    if (l->node)
    {
        l->node->previous = node;
        node->next = l->node;
        l->node = node;
    }
    else
        l->node = node;

    l->size++;
}

int UnitList_GetSize(UnitList* list)
{
    return list ? list->size : 0;
}

UnitListIterator UnitListIterator_New(UnitList* list)
{
    UnitListIterator iterator;
    iterator.list = list;
    iterator.node = list ? list->node : NULL;
    return iterator;
}

void UnitListIterator_Begin(UnitListIterator* iterator)
{
    if (iterator)
        iterator->node = iterator->list ? iterator->list->node : NULL;
}

void UnitListIterator_Next(UnitListIterator* iterator)
{
    if (iterator && iterator->node)
        iterator->node = iterator->node->next;
}

void UnitListIterator_Erase(UnitListIterator* iterator)
{
    if (iterator && iterator->node)
    {
        UnitListNode* erased = iterator->node;
        UnitListIterator_Next(iterator);

        if (iterator->list->node == erased)
            iterator->list->node = erased->next;

        if (erased->previous)
            erased->previous->next = erased->next;

        if (erased->next)
            erased->next->previous = erased->previous;

        free(erased);
        iterator->list->size--;
    }
}

int UnitListIterator_HasNext(UnitListIterator* iterator)
{
    return iterator && iterator->node && iterator->node->next;
}

int UnitListIterator_Finished(UnitListIterator* iterator)
{
    return iterator && iterator->node == NULL;
}

Unit* UnitListIterator_GetUnit(UnitListIterator* iterator)
{
    return iterator && iterator->node ? iterator->node->unit : NULL;
}
