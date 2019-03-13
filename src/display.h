#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "player.h"
#include "map.h"
#include "engine.h"

typedef struct
{
    int rows, cols;
    long unsigned int* buffer;
    int color;
    int attributes;

} Display;

Display* Display_New();
void Display_Delete(Display* d);
void Display_Clear(Display* d);
void Display_Resize(Display* d);
void Display_Render(Display* d);
void Display_Draw(Display* d, long unsigned int model, int row, int col);
void Display_DrawHLine(Display* d, long unsigned int model, int row, int col, int length);
void Display_DrawVLine(Display* d, long unsigned int model, int row, int col, int length);
void Display_DrawBox(Display* d, int row, int col, int width, int height);
void Display_DrawPlayerInfo(Display* d, Player* p, float time);
void Display_DrawText(Display* d, char* text, int row, int col, int center);
void Display_GetCenter(Display* d, int* row, int* col);
void Display_SetColor(Display* d, short c1, short c2);
void Display_SetAttributes(Display* d, unsigned att);
void Display_DrawMap(Display* d, Map* m, Player* p, int x, int y, int xLimit, int yLimit, int cameraX, int cameraY);
void Display_DrawPlayerSelectionInfo(Display* d, Engine* e, Player* p, int y);
void Display_CheckDimensions(Display* d);
int Display_IsInsideMap(Display* d, Map* m, int row, int col);
int Display_DrawTrainUnits(Display* d, Player* p, TrainableUnitList* tu, int row, int col);

#endif // _DISPLAY_H
