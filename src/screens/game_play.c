#include "screens.h"
#include "display.h"
#include "menu.h"
#include "engine.h"
#include "map.h"
#include "report.h"
#define NCURSES_MOUSE_VERSION
#include <ncurses.h>
#include <string.h>

Engine* engine = 0;
Menu* pauseMenu = 0;
float time = 0.0f;
int paused = 0;

static int MAP_OFFSET_Y = 3;

void GamePlay_Exit()
{
    if (engine)
        Engine_Delete(engine);

    if (pauseMenu)
        Menu_Delete(pauseMenu);

    engine = 0;
    pauseMenu = 0;
}

static void GamePlay_TogglePause()
{
    paused = !paused;

    if (paused)
        pauseMenu->selected_option = 1;
}

static void GamePlay_Pause()
{
    paused = 1;
    pauseMenu->selected_option = 1;
}


static int getCenteredOffsetX(Screen* s, int width)
{
    Display* display = s->display;
    return (display->cols - width) >> 1;
}

static int getMapOffsetX(Screen* s)
{
    int mapWidth;
    Map_GetSize(Engine_GetMap(engine), &mapWidth, NULL);
    return getCenteredOffsetX(s, mapWidth + 2);
}

static void mapCoordinatesToMapXY(Screen* s, int* x, int* y)
{
    if (x)
        *x = *x - getMapOffsetX(s) - 1;

    if (y)
        *y = *y - MAP_OFFSET_Y - 1;
}

char GamePlay_onExit(Screen* s)
{
    if (!paused)
    {
        GamePlay_Pause();
        return 0;
    }

    return 1;
}

void GamePlay_onRender(Screen* s)
{
    if (!engine)
        return;

    if (paused)
    {
        int row, col;
        Display_GetCenter(s->display, &row, &col);
        Menu_Draw(pauseMenu, s->display, row, col);
        return;
    }

    Display* display = s->display;
    Map* map = Engine_GetMap(engine);
    Player* player = Engine_GetPlayer(engine);

    int cameraX, cameraY;
    int mapX = getMapOffsetX(s);
    int mapWidth, mapHeight;

    Player_GetCamera(Engine_GetPlayer(engine), &cameraX, &cameraY);
    Map_GetSize(map, &mapWidth, &mapHeight);

    Display_DrawPlayerInfo(display, player, engine->time);
    Display_DrawBox(display, MAP_OFFSET_Y, mapX, mapWidth + 2, mapHeight + 1);
    Display_DrawMap(
        display, map, player,
        mapX + 1, MAP_OFFSET_Y + 1,
        mapX + mapWidth + 1, MAP_OFFSET_Y + mapHeight + 2,
        cameraX, cameraY
    );
    Display_DrawPlayerSelectionInfo(display, engine, player, MAP_OFFSET_Y + mapHeight + 2);
}

void GamePlay_onUpdate(Screen* s, float total_time, float delta_time)
{
    time += delta_time;

    Engine_AdvanceTime(engine, delta_time);

    if (Engine_HasFinished(engine))
        InitScreen_EndGame(s, 1);
}

void GamePlay_onKeyInput(Screen* s, int input, const char* keyString)
{
    if (!engine)
        return;


    if (input == 27)
    {
        GamePlay_TogglePause();
        return;
    }


    if (paused && input)
    {
        Menu_Input(pauseMenu, input);
        int click = Menu_Click(pauseMenu);
        switch (click)
        {
            case 1: paused = 0; return;
            case 2: InitScreen_GamePlay(s); return;
            case 3: GamePlay_Exit(); InitScreen_MainMenu(s); return;
            case 4: InitScreen_SaveGame(s, engine); paused = 0; break;
            case 5: Screen_Stop(s); GamePlay_Exit(); return;
            default: break;
        }
        return;
    }

    if (input == KEY_MOUSE)
    {
        MEVENT event;
        if (getmouse(&event) == OK)
        {
            int mapX = event.x;
            int mapY = event.y;
            mapCoordinatesToMapXY(s, &mapX, &mapY);

            if (event.bstate & (BUTTON1_CLICKED | BUTTON1_PRESSED))
            {
                // loginfo("Mouse click %d/%d -> %d/%d", event.x, event.y, mapX, mapY);

                Unit* u = Engine_GetUnitFromPos(
                    engine,
                    Position_NewPosition(mapX, mapY)
                );

                Player_SelectUnit(Engine_GetPlayer(engine), u);
            }
            else if (event.bstate & (BUTTON3_CLICKED | BUTTON3_PRESSED))
            {
                Unit* unit = Player_GetSelectedUnit(Engine_GetPlayer(engine));
                Unit* target = Engine_GetUnitFromPos(
                    engine,
                    Position_NewPosition(mapX, mapY)
                );

                Engine_UnitSetTarget(engine, unit, target);
            }
        }
    }
    else
    {
        Player* p = Engine_GetPlayer(engine);
        Unit* u = Player_GetSelectedUnit(p);

        if (Unit_GetOwner(u) == p)
        {
            if (input == KEY_DC && Player_GetHeadquarter(p) != u)
            {
                if (!strcmp(Unit_GetName(u), "Worker"))
                {
                    Engine_HideUnit(engine, u);
                    Player_SelectUnit(p, Player_GetHeadquarter(p));
                }
                else
                    Engine_KillUnit(engine, u, NULL);
            }
            else if (input >= '0' && input <= '9')
            {
                int num = input - '1';
                if (u && Unit_GetOwner(u) == p)
                {
                    if (num >= 0 && num < u->trainable_units.count)
                        Unit_TrainUnit(u, num);
                }
            }
            else
            {
                switch (input)
                {
                    case KEY_UP: Engine_MoveUnit(engine, u, North); break;
                    case KEY_DOWN: Engine_MoveUnit(engine, u, South); break;
                    case KEY_RIGHT: Engine_MoveUnit(engine, u, East); break;
                    case KEY_LEFT: Engine_MoveUnit(engine, u, West); break;
                    default:
                        break;
                }
            }
        }
    }
}

void InitScreen_GamePlay(Screen* s)
{
    if (!s)
        return;

    GamePlay_Exit();

    paused = 0;
    time = 0.0f;

    s->onRender = &GamePlay_onRender;
    s->onUpdate = &GamePlay_onUpdate;
    s->onKeyInput = &GamePlay_onKeyInput;
    s->onExit = &GamePlay_onExit;

    engine = Engine_NewEngine();
    Engine_StartGame(engine, Map_DefaultMap());

    pauseMenu = Menu_New("Paused");
    Menu_AddOption(pauseMenu, "Return to Game (ESC)");
    Menu_AddOption(pauseMenu, "Restart Game");
    Menu_AddOption(pauseMenu, "Return to Main Menu");
    Menu_AddOption(pauseMenu, "Save Game");
    Menu_AddOption(pauseMenu, "Exit");

    Player_SelectUnit(Engine_GetPlayer(engine), Player_GetHeadquarter(Engine_GetPlayer(engine)));
}

void ResumeScreen_GamePlay(Screen* s)
{
    s->onRender = &GamePlay_onRender;
    s->onUpdate = &GamePlay_onUpdate;
    engine->finished = 0;
}

void GamePlay_SetEngine(Engine* e)
{
    if (!e)
        return;

    if (engine)
        Engine_Delete(engine);

    engine = e;
}
