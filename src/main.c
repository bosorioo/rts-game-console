#include <stdio.h>
#include <string.h>
#include "ncurses.h"
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
    nodelay(stdscr, TRUE);

    if (has_colors())
        start_color();

#ifndef _WIN32
    use_default_colors();
    curs_set(0);
    set_escdelay(50);
#endif

    UnitLoader_LoadAllUnits();
    Screen* screen = Screen_New();
    InitScreen_MainMenu(screen);

    unsigned long long start = Clock_GetTime(NULL);
    unsigned long long lastUpdate = start;
    unsigned long long delta;

    while (Screen_IsRunning(screen))
    {
        Display_CheckDimensions(screen->display);

        int keyIterationsLimit = 20;
        int shouldExit = 0;
        do
        {
            int key = getch();

            if (key == -1)
                break;

            if (key == 450) key = KEY_UP;
            else if (key == 456) key = KEY_DOWN;
            else if (key == 454) key = KEY_RIGHT;
            else if (key == 452) key = KEY_LEFT;

            const char* keyString = keyname(key);

            if (strcmp(keyString, "^C") == 0 &&
                (!screen->onExit || screen->onExit(screen)))
            {
                shouldExit = 1;
                break;
            }

            if (screen->onKeyInput)
                screen->onKeyInput(screen, key, keyString);
        } while (keyIterationsLimit-- > 0);

        if (shouldExit)
            break;

        unsigned long long now = Clock_GetTime(NULL);
        delta = now - lastUpdate;

        if (screen->onUpdate)
        {
            screen->onUpdate(screen,
                   (float)(now - start) * 0.001f,
                   (float)delta * 0.001f);
        }

        lastUpdate = Clock_GetTime(NULL);

        Display_Clear(screen->display);

        if (screen->onRender)
            screen->onRender(screen);

        Display_Render(screen->display);
        Clock_Sleep(50);
    }

    Display_Clear(screen->display);
    Display_Render(screen->display);

    endwin();
    UnitLoader_UnloadAllUnits();
    Screen_Delete(screen);
    return 0;
}
