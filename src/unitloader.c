#include "unitloader.h"
#include "unittype.h"
#include "report.h"
#include "attacktype.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int LOADED = 0;

UnitType UnitLoader_LoadUnitFromFile(FILE* f)
{
    char field[32];
    char value[128];
    int valueLength;

    UnitType result;

    result.name = NULL;
    result.max_health = 0;
    result.attack_damage_min = 0;
    result.attack_damage_max = 0;
    result.attack_range = 0;
    result.attack_speed = 0.;

    result.movement_speed = 0.;
    result.is_building = 0;

    result.money_income = 0;
    result.money_interval = 0.;

    result.food_income = 0;
    result.food_interval = 0.;

    result.money_cost = 0;
    result.food_cost = 0;
    result.train_time = 0.;

    result.trainable_units.count = 0;
    result.model = '?';
    result.atk_type = Attack_None;
    result.def_type = Defense_None;

    int limit = 240;

    while (limit-- > 0)
    {
        int read = fscanf(
            f, "%31s%*[ \t]=%*[ \t]%127[^\r\n]%n%*[\r\n]",
            field, value, &valueLength
        );

        if (read != 2)
        {
            break;
        }

        #define IF_FIELD(fieldName) \
            if (strcmp(field, #fieldName) == 0)

        #define IF_FIELD_STRING(fieldName) \
            if (strcmp(field, #fieldName) == 0) \
            { \
                result.fieldName = (char*)malloc((valueLength + 1) * sizeof(char)); \
                strcpy(result.fieldName, value); \
            }

        #define IF_FIELD_INT(fieldName) \
            if (strcmp(field, #fieldName) == 0) \
            { \
                result.fieldName = atoi(value); \
            }

        #define IF_FIELD_FLOAT(fieldName) \
            if (strcmp(field, #fieldName) == 0) \
            { \
                result.fieldName = atof(value); \
            }

        #define IF_FIELD_BOOL(fieldName) \
            if (strcmp(field, #fieldName) == 0) \
            { \
                result.fieldName = value[0] == 1 || value[0] == 't' || value[0] == 'y'; \
            }

        #define IF_FIELD_CHAR(fieldName) \
            if (strcmp(field, #fieldName) == 0) \
            { \
                result.fieldName = value[0]; \
            }

        IF_FIELD_STRING(name)
        else IF_FIELD_INT(max_health)
        else IF_FIELD_INT(attack_damage_min)
        else IF_FIELD_INT(attack_damage_max)
        else IF_FIELD_INT(attack_range)
        else IF_FIELD_FLOAT(attack_speed)
        else IF_FIELD_FLOAT(movement_speed)
        else IF_FIELD_BOOL(is_building)
        else IF_FIELD_INT(money_income)
        else IF_FIELD_FLOAT(money_interval)
        else IF_FIELD_INT(food_income)
        else IF_FIELD_FLOAT(food_interval)
        else IF_FIELD_INT(money_cost)
        else IF_FIELD_INT(food_cost)
        else IF_FIELD_FLOAT(train_time)
        else IF_FIELD_CHAR(model)
        else IF_FIELD(trainable_units)
        {
            result.trainable_units = TrainableUnitList_Create(value);
        }
        else
        {
            loginfo("Invalid field of unit type \"%s\" = %s.", field, value);
            continue;
        }

        loginfo("Parsed field \"%s\" = %s.", field, value);

        // enum AttackType atk_type;
        // enum DefenseType def_type;
    }

    return result;
}

void UnitLoader_LoadAllUnits()
{
    if (LOADED)
        return;

    FILE* unitsIndexFile = fopen("data/units.txt", "r");
    char line[512];
    char buffer[512];
    char log[512];

    int errors = 0;
    int unitLimit = 100;

    RASSERT(unitsIndexFile, Failed to open units index file at \\"data/units.txt\\");

    loginfo("Loading units...");

    while (unitLimit-- > 0 && fscanf(unitsIndexFile, "%511[^\n]%*[\r\n]", line) == 1)
    {
        loginfo(line);

        if (line[0] == '@' && line[1])
        {
            snprintf(buffer, sizeof(buffer), "data/%s", line + 1);

            FILE* unitFile = fopen(buffer, "r");

            if (!unitFile)
            {
                snprintf(log, sizeof(log), "Failed to open unit data file \"%s\".\n", buffer);
                ReportError(log, 0);
                errors++;
                continue;
            }

            UnitType result = UnitLoader_LoadUnitFromFile(unitFile);

            if (!UnitType_AddType(result.name, result))
            {
                loginfo("Failed to add unit type.\n");
            }
            else
            {
                loginfo("Done.\n");
            }

            fclose(unitFile);
        }
    }

    fclose(unitsIndexFile);

    if (errors)
    {
        snprintf(log, sizeof(log), "Unit loading produced %d error(s).\n", errors);
        ReportError(log, 0);
        exit(0);
    }

    LOADED = 1;
}

void UnitLoader_UnloadAllUnits()
{
    if (!LOADED)
        return;

    UnitType_Clear();
    LOADED = 0;
}
