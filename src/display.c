#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "display.h"
#include "color_manager.h"
#include "terminal_size.h"
#include "report.h"
#include "engine.h"
#include "unittype.h"

static inline int min(int a, int b)
{
    return a < b ? a : b;
}

Display* Display_New()
{
    Display* d = (Display*)malloc(sizeof(Display));
    if (d)
    {
        d->buffer = NULL;
        d->rows = 0;
        d->cols = 0;
        Display_Resize(d);
    }
    return d;
}

void Display_Delete(Display* d)
{
    if (!d)
        return;

    if (d->buffer)
        free(d->buffer);

    free(d);
}

void Display_Resize(Display* d)
{
    if (d)
    {
        int rows, cols;

        if (!GetTerminalSize(&cols, &rows))
        {
            return;
        }

        if (d->rows == rows && d->cols == cols)
            return;

        loginfo("Resized terminal %d %d", rows, cols);

        d->rows = rows;
        d->cols = cols;

        resize_term(rows, cols);

        if (d->buffer)
            free(d->buffer);

        if (rows <= 0 || cols <= 0)
            d->buffer = NULL;
        else
            d->buffer = (long unsigned int*)malloc(sizeof(long unsigned int) * rows * cols);

        Display_Clear(d);
        clear();
        // Display_Render(d);
    }
}

void Display_Clear(Display* d)
{
    if (!d || !d->buffer)
        return;

    int i;
    for (i = 0; i < d->rows * d->cols; i++)
        d->buffer[i] = (long unsigned int)' ';
}

void Display_Render(Display* d)
{
    if (!d)
        return;

    int rows, cols, i, j;

    clear();
    getmaxyx(stdscr, rows, cols);

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (i < d->rows && j < d->cols)
                mvaddch(i, j, d->buffer[i * d->cols + j]);
            else
                mvaddch(i, j, (long unsigned int)' ');
        }
    }

    refresh();
}

void Display_Draw(Display* d, long unsigned int model, int row, int col)
{
    if (!d || !d->buffer || row < 0 || col < 0 || row >= d->rows || col >= d->cols)
        return;

    long unsigned int modifiers = 0;

    if (d->color)
        modifiers |= d->color;

    if (d->attributes)
        modifiers |= d->attributes;

    d->buffer[row * d->cols + col] = model | modifiers;
}

void Display_DrawHLine(Display* d, long unsigned int model, int row, int col, int length)
{
    int i;
    for (i = 0; i < length; i++)
        Display_Draw(d, model, row, col + i);
}

void Display_DrawVLine(Display* d, long unsigned int model, int row, int col, int length)
{
    int i;
    for (i = 0; i < length; i++)
        Display_Draw(d, model, row + i, col);
}

void Display_DrawBox(Display* d, int row, int col, int width, int height)
{
    Display_SetAttributes(d, A_BOLD);

    /*
    Display_Draw(d, ACS_ULCORNER, row, col);
    Display_Draw(d, ACS_URCORNER, row, col + width);
    Display_Draw(d, ACS_LRCORNER, row + height, col + width);
    Display_Draw(d, ACS_LLCORNER, row + height, col);
    Display_DrawHLine(d, ACS_HLINE, row, col + 1, width - 1);
    Display_DrawHLine(d, ACS_HLINE, row + height, col + 1, width - 1);
    Display_DrawVLine(d, ACS_VLINE, row + 1, col, height - 1);
    Display_DrawVLine(d, ACS_VLINE, row + 1, col + width, height - 1);
    */

    Display_Draw(d, '+', row, col);
    Display_Draw(d, '+', row, col + width);
    Display_Draw(d, '+', row + height, col + width);
    Display_Draw(d, '+', row + height, col);
    Display_DrawHLine(d, '-', row, col + 1, width - 1);
    Display_DrawHLine(d, '-', row + height, col + 1, width - 1);
    Display_DrawVLine(d, '|', row + 1, col, height - 1);
    Display_DrawVLine(d, '|', row + 1, col + width, height - 1);

    Display_SetAttributes(d, 0);
}

void Display_DrawPlayerInfo(Display* d, Player* p, float time)
{
    if (!d || !p)
        return;

    char text[25];
    int money, food;
    int width = 0, temp;
    Player_GetResources(p, &money, &food);

    Display_SetColor(d, COLOR_GREEN, COLOR_BLACK);
    Display_DrawText(d, " Money: ", 1, 1, 0);
    width += 9;

    temp = sprintf(text, "%d", money);

    Display_SetColor(d, -1, -1);
    Display_DrawText(d, text, 1, width, 0);
    width += temp;

    Display_SetColor(d, -1, -1);
    Display_DrawText(d, " | ", 1, width, 0);
    width += 3;

    Display_SetColor(d, COLOR_RED, COLOR_BLACK);
    Display_DrawText(d, "Food: ", 1, width, 0);
    width += 6;

    temp = sprintf(text, "%d ", food);

    Display_SetColor(d, -1, -1);
    Display_DrawText(d, text, 1, width, 0);
    width += temp;

    Display_DrawBox(d, 0, 0, width, 2);
    width += 1;

    temp = snprintf(text, sizeof(text), " Game time: %.1f ", time);
    Display_DrawBox(d, 0, width, temp + 1, 2);
    width += 1;
    Display_DrawText(d, text, 1, width, 0);
    width += temp;

    temp = sprintf(text, " Units: %d ", Player_GetUnitCount(p));
    width += 1;
    Display_DrawBox(d, 0, width, temp + 1, 2);
    width += 1;
    Display_DrawText(d, text, 1, width, 0);
    width += temp;

    int box_start = width;
    float money_inc, food_inc;
    Player_GetIncome(p, &money_inc, &food_inc);
    temp = sprintf(text, " Income: ");
    width += 2;
    Display_DrawText(d, text, 1, width, 0);
    width += temp;
    Display_SetColor(d, COLOR_GREEN, COLOR_BLACK);
    temp = sprintf(text, "%g", money_inc);
    Display_DrawText(d, text, 1, width, 0);
    width += temp;
    Display_SetColor(d, -1, -1);
    Display_DrawText(d, "/", 1, width, 0);
    width += 1;
    Display_SetColor(d, COLOR_RED, COLOR_BLACK);
    temp = sprintf(text, "%g ", food_inc);
    Display_DrawText(d, text, 1, width, 0);
    width += temp;
    Display_SetColor(d, -1, -1);

    Display_DrawBox(d, 0, box_start, width - box_start, 2);
}

void Display_DrawText(Display* d, char* text, int row, int col, int center)
{
    if (!d || !text)
        return;

    int length = strlen(text);
    int i;

    if (center)
        col -= length/2;

    if (col < 0)
    {
        text -= col;
        col = 0;
    }

    long unsigned int modifiers;

    for (i = 0; i < length && i + col < d->cols; i++)
    {
        modifiers = 0;

        if (d->color)
            modifiers |= d->color;

        if (d->attributes)
            modifiers |= d->attributes;

        d->buffer[row * d->cols + col + i] = text[i] | modifiers;
    }
}

void Display_GetCenter(Display* d, int* row, int* col)
{
    if (!d || !row || !col)
        return;

    *row = d->rows / 2;
    *col = d->cols / 2;
}

void Display_SetColor(Display* d, short c1, short c2)
{
    if (!d || !has_colors())
        return;

    if (c1 == -1 || c2 == -1)
        d->color = 0;
    else
        d->color = Color_GetId(c1, c2);
}

void Display_SetAttributes(Display* d, unsigned att)
{
    if (!d)
        return;
   d->attributes = att;
}

void Display_DrawMap(
    Display* d, Map* m, Player* p,
    int x, int y,
    int xLimit, int yLimit,
    int cameraX, int cameraY
)
{
    if (!d || !m || !p)
        return;

    if (x < 0)
    {
        cameraX -= x;
        x = 0;
    }

    if (y < 0)
    {
        cameraY -= y;
        y = 0;
    }

    int col, row;
    int colTo, rowTo;

    int mapWidth, mapHeight;
    int screenWidth = d->cols;
    int screenHeight = d->rows;

    Map_GetSize(m, &mapWidth, &mapHeight);

    xLimit = screenWidth < xLimit ? screenWidth : xLimit;
    yLimit = screenHeight < yLimit ? screenHeight : yLimit;

    colTo = xLimit - x + 1;
    colTo = mapWidth < colTo ? mapWidth : colTo;

    rowTo = yLimit - y + 1;
    rowTo = mapHeight < rowTo ? mapHeight : rowTo;

    for (col = 0; col < colTo; col++)
    {
        for (row = 0; row < rowTo; row++)
        {
            Unit* unit = Map_GetUnit(m, Position_NewPosition(col + cameraX, row + cameraY));
            if (unit)
            {
                short c1 = COLOR_WHITE, c2 = COLOR_BLACK;
                unsigned att = 0;

                if (Player_GetSelectedUnit(p) == unit)
                {
                    c2 = COLOR_GREEN;
                    att = A_BOLD;
                }

                if (Unit_GetOwner(unit) != p)
                    c1 = COLOR_RED;

                if (Unit_GetTarget(Player_GetSelectedUnit(p)) == unit &&
                    Unit_GetOwner(unit) != p)
                {
                    c1 = COLOR_WHITE;
                    c2 = COLOR_RED;
                }

                Display_SetColor(d, c1, c2);
                Display_SetAttributes(d, att);

                Display_Draw(d, Unit_GetModel(unit), row + y, col + x);

                Display_SetColor(d, -1, -1);
                Display_SetAttributes(d, 0);
            }
        }
    }
}

void Display_DrawPlayerSelectionInfo(Display* d, Engine* e, Player* p, int y)
{
    if (!d || !p)
        return;

    char buffer[100];
    Unit* selection = Player_GetSelectedUnit(p);

    Display_DrawBox(d, y, 0, d->cols - 1, min(12, d->rows - y - 1));

    if (Player_GetHeadquarter(p) != selection && selection && Unit_GetOwner(selection) == p)
    {
        if (!strcmp(Unit_GetName(selection), "Worker"))
            Display_DrawText(d, "Press DEL to hide this unit in the HQ.", y + 7, 1, 0);
        else
            Display_DrawText(d, "Press DEL to sacrifice this unit.", y + 7, 1, 0);

        if (Unit_CanMove(selection))
            Display_DrawText(d, "Use arrow keys to move this unit.", y + 6, 1, 0);
    }

    snprintf(buffer, sizeof(buffer), "Selected unit: %s %s",
            selection ? Unit_GetName(selection) : "none",
            selection && Unit_GetOwner(selection) != p ? "(Enemy)" : "");
    y++;
    Display_DrawText(d, buffer, y, 1, 0);

    if (selection)
    {
        int isEnemy = Unit_IsAlly(selection, Engine_GetEnemyHeadquarter(e, p));
        float money, food;
        Unit_GetIncomePerSecond(selection, &money, &food);
        if (isEnemy)
            snprintf(buffer, sizeof(buffer), "Health: %d/%d",
                    Unit_GetHealth(selection), Unit_GetMaxHealth(selection));
        else
            snprintf(buffer, sizeof(buffer), "Health: %d/%d  Income: %g/%g",
                    Unit_GetHealth(selection), Unit_GetMaxHealth(selection),
                    money, food);
        y++;
        Display_DrawText(d, buffer, y, 1, 0);
        if (Unit_CanAttack(selection))
        {
            int min, max;
            Unit_GetAttackDamage(selection, &min, &max);
            snprintf(
                buffer, sizeof(buffer),
                "Attack: %d - %d  Range: %d",
                min, max, Unit_GetAttackRange(selection)
            );
            y++;
            Display_DrawText(d, buffer, y, 1, 0);
        }
        if (!isEnemy)
        {
            y++;
            if (Unit_IsTraining(selection))
            {
                sprintf(buffer, "Currently %s %s.",
                        Unit_IsBuilding(selection->training_unit) ? "building" : "training",
                        Unit_GetTrainingUnitName(selection));
                Display_DrawText(d, buffer, y, 1, 0);
                y++;

                float trainingTimeLeft = Unit_GetTrainingTimeLeft(selection);

                if (trainingTimeLeft > 0.)
                    snprintf(
                        buffer, sizeof(buffer),
                        "Will be ready in %.1f seconds",
                        trainingTimeLeft
                    );
                else
                    snprintf(buffer, sizeof(buffer), "Waiting enough room");

                Display_DrawText(d, buffer, y, 1, 0);
            }
            else
            {
                Display_DrawTrainUnits(d, p, &selection->trainable_units, y, 1);
            }
        }
    }
}

void Display_CheckDimensions(Display* d)
{
    if (!d)
        return;

    Display_Resize(d);
}

int Display_IsInsideMap(Display* d, Map* m, int row, int col)
{
    int rows, cols;
    Map_GetSize(m, &cols, &rows);

    row -= 4;
    col -= 1;

    if (rows > d->rows - 12)
        rows = d->rows - 12;

    if (cols > d->cols - 1)
        cols = d->cols - 1;

    int colOffset = (d->cols - cols) >> 1;

    col -= colOffset;

    return row >= 0 && row < rows && col >= 0 && col < cols;
}

int Display_DrawTrainUnits(Display* d, Player* p, TrainableUnitList* tul, int row, int col)
{
    if (!d || !tul || !p)
        return 0;

    char buffer[40];
    int index;

    for (index = 0; index < tul->count; index++)
    {
        TrainableUnit* unit = tul->units + index;

        UnitType* type = UnitType_GetType(unit->unit_name);

        if (type)
        {
            if (Player_HasResources(p, type->money_cost, type->food_cost))
                snprintf(
                    buffer, sizeof(buffer),
                    "Press %d to %s. Costs %d/%d.",
                    1 + index,
                    unit->train_message,
                    type->money_cost, type->food_cost
                );
            else
                snprintf(
                    buffer, sizeof(buffer),
                    "It costs %d/%d to %s.",
                    type->money_cost, type->food_cost,
                    unit->train_message
                );

            Display_DrawText(d, buffer, row + index, col, 0);
        }
        else
        {
            Display_DrawText(d, unit->unit_name, row + index, col, 0);
        }
    }

    return index;
}
