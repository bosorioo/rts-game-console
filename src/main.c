#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include "display.h"
#include "clock.h"
#include "screens.h"
#include "unitloader.h"

int main(int argc, char* args[])
{
    initscr();
    cbreak();
    noecho();
    raw();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    resize_term(29, 85);
    nodelay(stdscr, 1);

    if (has_colors())
        start_color();

    UnitLoader_LoadAllUnits();
    Screen* screen = Screen_New();
    InitScreen_MainMenu(screen);

    unsigned long long start = Clock_GetTime(NULL);
    unsigned long long lastUpdate = Clock_GetTime(NULL);
    unsigned long long delta;

    while (Screen_IsRunning(screen))
    {
        Display_CheckDimensions(screen->display);
        delta = Clock_GetTime(NULL);
        lastUpdate = Clock_GetTime(&lastUpdate);

        int key = getch();

        if (key == 450) key = KEY_UP;
        else if (key == 456) key = KEY_DOWN;
        else if (key == 454) key = KEY_RIGHT;
        else if (key == 452) key = KEY_LEFT;

        const char* keyString = keyname(key);

        if (key != -1 && strcmp(keyString, "^C") == 0 &&
            (!screen->onExit || screen->onExit(screen)))
        {
            break;
        }

        if (screen->onKeyInput)
            screen->onKeyInput(screen, key, keyString);

        if (screen->onUpdate)
            screen->onUpdate(screen,
                   (float)Clock_GetTime(&start) * 0.001f,
                   (float)lastUpdate * 0.001f);

        lastUpdate = Clock_GetTime(NULL);
        Display_Clear(screen->display);

        if (screen->onRender)
            screen->onRender(screen);

        Display_Render(screen->display);
        delta = Clock_GetTime(&delta);

        if (delta < 20)
            Clock_Sleep(20 - delta);
    }

    Display_Clear(screen->display);
    Display_Render(screen->display);

    endwin();
    UnitLoader_UnloadAllUnits();
    Screen_Delete(screen);
    return 0;
}
