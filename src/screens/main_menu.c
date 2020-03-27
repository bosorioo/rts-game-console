#include <ncurses.h>
#include "screens.h"
#include "menu.h"
#include "display.h"
#include "report.h"

Menu* mainMenu = 0;

void MainMenu_Exit()
{
    Menu_Delete(mainMenu);
    mainMenu = 0;
}

void MainMenu_onRender(Screen* s)
{
    int row, col;
    Display_GetCenter(s->display, &row, &col);
    Menu_Draw(mainMenu, s->display, row, col);
}

void MainMenu_onUpdate(Screen* s, float total_time, float delta_time)
{
}

void MainMenu_onKeyInput(Screen* s, int key, const char* keyString)
{
    Menu_Input(mainMenu, key);

    if (key == 27)
        mainMenu->selected_option = 4;

    key = Menu_Click(mainMenu);

    switch (key)
    {
        case 1:
            MainMenu_Exit();
            InitScreen_GamePlay(s);
            break;

        case 2:
            MainMenu_Exit();
            InitScreen_LoadGame(s);
            break;

        case 3:
            MainMenu_Exit();
            InitScreen_HowToPlay(s);
            break;

        case 4:
            MainMenu_Exit();
            Screen_Stop(s);
            break;

        default:
            break;
    }
}

void InitScreen_MainMenu(Screen* s)
{
    if (!s)
        return;

    s->onRender = &MainMenu_onRender;
    s->onKeyInput = &MainMenu_onKeyInput;

    mainMenu = Menu_New("Main Menu");
    Menu_AddOption(mainMenu, "Start New Game");
    Menu_AddOption(mainMenu, "Load Saved Game");
    Menu_AddOption(mainMenu, "How to Play");
    Menu_AddOption(mainMenu, "Exit");
}
