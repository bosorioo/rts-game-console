#include "screens.h"
#include "display.h"
#include <ncurses.h>

char* text[] = {
    "How to play",
    "",
    "Your objective is to destroy the enemy headquarter.",
    "To do so, you need to train units to gather resources",
    "and train military units to attack the enemy. Resources",
    "can be obtained over time based on your units and buildings",
    "You must use the mouse to select units to view their status",
    "and decide what those units must do next. Onde a unit is selected",
    "you can move it using arrow keys, destroy it using the DEL key",
    "and issue orders with the numbers keys 1, 2, 3...",
    "You can also use the right mouse button to select targets.",
    "Have fun!",
    "",
    "You can pause the game by pressing ESC.",
    "Press ESC to go back."
};

void HowToPlay_onRender(Screen* s)
{
    int row, col;
    Display_GetCenter(s->display, &row, &col);

    int lines = sizeof(text) / sizeof(char*);
    int i;

    for (i = 0; i < lines; i++)
    {
        Display_DrawText(s->display, text[i], row - lines / 2 + i, col, 1);
    }
}

void HowToPlay_onKeyInput(Screen* s, int input, const char* keyString)
{
    if (input == 27)
        InitScreen_MainMenu(s);
}

void InitScreen_HowToPlay(Screen* s)
{
    if (!s)
        return;

    s->onRender = &HowToPlay_onRender;
    s->onKeyInput = &HowToPlay_onKeyInput;
}
