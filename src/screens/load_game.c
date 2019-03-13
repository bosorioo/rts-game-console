#include "screens.h"
#include "display.h"
#include "engine.h"
#include <stdio.h>
#include <ncurses.h>

int loaded = 0;
Engine* eng;

void LoadGame_onRender(Screen* s)
{
    int row, col;
    Display_GetCenter(s->display, &row, &col);

    if (loaded)
    {
        Display_DrawText(s->display, "Loading complete.", row, col, 1);
        Display_DrawText(s->display, "Press ENTER to resume game.", row + 1, col, 1);
    }
    else
    {
        Display_DrawText(s->display, "Loading failed.", row, col, 1);
        Display_DrawText(s->display, "Press ENTER to go back to main menu.", row + 1, col, 1);
    }
}

void LoadGame_onKeyInput(Screen* s, int input, const char* keyString)
{
    if (input == KEY_ENTER || input == 10 || input == 13)
    {
        if (loaded && eng)
        {
            InitScreen_GamePlay(s);
            GamePlay_SetEngine(eng);
            eng = NULL;
            loaded = 0;
        }
        else
        {
            InitScreen_MainMenu(s);
        }
    }
}

void InitScreen_LoadGame(Screen* s)
{
    int row, col;
    Display_GetCenter(s->display, &row, &col);
    Display_Clear(s->display);
    Display_DrawText(s->display, "Loading...", row, col, 1);
    Display_Render(s->display);

    s->onRender = NULL;
    s->onKeyInput = NULL;

    FILE* file = fopen("RTS-SAVED-GAME.bin", "rb");

    if (file)
    {
        eng = Engine_LoadFromFile(file);
        loaded = 1;
        fclose(file);
    }

    s->onRender = LoadGame_onRender;
    s->onKeyInput = LoadGame_onKeyInput;
}
