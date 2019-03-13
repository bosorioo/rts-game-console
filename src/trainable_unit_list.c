#include "trainable_unit_list.h"
#include <stdlib.h>
#include <string.h>

TrainableUnitList TrainableUnitList_Create(const char* descriptor)
{
    TrainableUnitList tu;

    tu.count = 0;
    tu.units = NULL;

    if (!descriptor)
    {
        return tu;
    }

    const char* ptr = descriptor;

    while (1)
    {
        if (*ptr == '|' || *ptr == '\0')
        {
            tu.count++;
            if (*ptr == '\0')
            {
                break;
            }
        }

        ptr++;
    }

    tu.count >>= 1;

    if (tu.count <= 0)
    {
        return tu;
    }

    tu.units = (TrainableUnit*)malloc(sizeof(TrainableUnit) * tu.count);

    TrainableUnit* unitPtr = tu.units;
    int length = 0;
    char readingMessage = 1;
    unitPtr->unit_name = NULL;
    unitPtr->train_message = NULL;

    ptr = descriptor;

    while (1)
    {
        if (*ptr == '|' || *ptr == '\0')
        {
            char* string = NULL;

            if (length > 0)
            {
                string = (char*)malloc((length + 1) * sizeof(char));
            }

            if (readingMessage)
            {
                unitPtr->train_message = string;
            }
            else
            {
                unitPtr->unit_name = string;
                unitPtr++;
                unitPtr->unit_name = NULL;
                unitPtr->train_message = NULL;
            }

            if (string)
            {
                memcpy(string, ptr - length, length);
                string[length] = '\0';
            }

            length = 0;

            if (*ptr == '\0')
            {
                break;
            }

            readingMessage = !readingMessage;
        }
        else
        {
            length++;
        }

        ptr++;
    }

    return tu;
}

TrainableUnit* TrainableUnitList_Get(TrainableUnitList* tu, int index)
{
    if (index >= 0 && tu && index < tu->count)
    {
        return tu->units + index;
    }

    return NULL;
}
