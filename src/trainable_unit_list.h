#ifndef _TRAINABLE_UNIT_LIST_H
#define _TRAINABLE_UNIT_LIST_H

typedef struct TrainableUnit
{
    char* unit_name;
    char* train_message;
} TrainableUnit;

typedef struct TrainableUnitList
{
    TrainableUnit* units;
    int count;
} TrainableUnitList;

TrainableUnitList TrainableUnitList_Create(const char* descriptor);
TrainableUnit* TrainableUnitList_Get(TrainableUnitList* tu, int index);

#endif
