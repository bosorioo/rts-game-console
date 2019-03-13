#include "screens.h"
#include "display.h"
#include "engine.h"
#include "menu.h"
#include <stdio.h>
#include <ncurses.h>

Menu* saveGameMenu = 0;

void SaveGame_Exit()
{
    Menu_Delete(saveGameMenu);
    saveGameMenu = 0;
}

void SaveGame_onRender(Screen* s)
{
    int row, col;
    Display_GetCenter(s->display, &row, &col);
    Menu_Draw(saveGameMenu, s->display, row, col);
}

void SaveGame_onKeyInput(Screen* s, int input, const char* keyString)
{
    Menu_Input(saveGameMenu, input);

    if (input == 27)
        saveGameMenu->selected_option = 3;

    input = Menu_Click(saveGameMenu);

    switch (input)
    {
        case 1:
            SaveGame_Exit();
            ResumeScreen_GamePlay(s);
            break;

        case 2:
            SaveGame_Exit();
            InitScreen_MainMenu(s);
            break;

        case 3:
            SaveGame_Exit();
            Screen_Stop(s);
            break;

        default:
            break;
    }
}

void InitScreen_SaveGame(Screen* s, Engine* engine)
{
    int row, col;
    Display_GetCenter(s->display, &row, &col);
    Display_Clear(s->display);
    Display_DrawText(s->display, "Saving...", row, col, 1);
    Display_Render(s->display);

    s->onRender = NULL;
    s->onKeyInput = NULL;

    FILE* file = fopen("RTS-SAVED-GAME.bin", "wb");

    if (file)
    {
        Engine_SaveToFile(engine, file);
        fclose(file);
    }

    s->onRender = SaveGame_onRender;
    s->onKeyInput = SaveGame_onKeyInput;

    saveGameMenu = Menu_New("Game Saved Sucessfully");
    Menu_AddOption(saveGameMenu, "Resume Game");
    Menu_AddOption(saveGameMenu, "Return to Main Menu");
    Menu_AddOption(saveGameMenu, "Exit");
}
