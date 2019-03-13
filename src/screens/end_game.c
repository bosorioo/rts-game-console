#include "screens.h"
#include "display.h"
#include "menu.h"
#include <stdio.h>
#include <ncurses.h>

Menu* endGameMenu = 0;
int winning = 0;

void EndGame_onRender(Screen* s)
{
    int row, col;
    Display_GetCenter(s->display, &row, &col);
    Menu_Draw(endGameMenu, s->display, row, col);
}

void EndGame_Exit()
{
    Menu_Delete(endGameMenu);
    endGameMenu = 0;
}

void EndGame_onKeyInput(Screen* s, int input, const char* keyString)
{
    Menu_Input(endGameMenu, input);

    if (input == 27)
        endGameMenu->selected_option = 4;

    input = Menu_Click(endGameMenu);

    if (!winning)
        input++;

    switch (input)
    {
        case 1:
            EndGame_Exit();
            ResumeScreen_GamePlay(s);
            break;

        case 2:
            EndGame_Exit();
            InitScreen_GamePlay(s);
            break;

        case 3:
            EndGame_Exit();
            InitScreen_MainMenu(s);
            break;

        case 4:
            EndGame_Exit();
            Screen_Stop(s);
            break;

        default:
            break;
    }
}

void InitScreen_EndGame(Screen* s, int finish)
{
    s->onRender = EndGame_onRender;
    s->onKeyInput = EndGame_onKeyInput;

    winning = finish == 2;

    endGameMenu = Menu_New(winning ?
                           "Game Over - You Won!" :
                           "Game Over - You Lost!");

    if (winning)
        Menu_AddOption(endGameMenu, "Keep Playing");

    Menu_AddOption(endGameMenu, "Play Again");
    Menu_AddOption(endGameMenu, "Return to Main Menu");
    Menu_AddOption(endGameMenu, "Exit");
}
