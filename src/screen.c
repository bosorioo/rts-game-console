#include "screen.h"
#include <stdlib.h>

Screen* Screen_New()
{
    Screen* s = (Screen*)malloc(sizeof(Screen));
    if (s)
    {
        s->display = Display_New();

        if (!s->display)
        {
            free(s);
            return NULL;
        }

        Display_Resize(s->display);
        s->onRender = NULL;
        s->onUpdate = NULL;
        s->onKeyInput = NULL;
        s->onExit = NULL;
        s->running = 1;
    }
    return s;
}

void Screen_Delete(Screen* s)
{
    if (s)
    {
        Display_Delete(s->display);
        free(s);
    }
}

void Screen_Stop(Screen* s)
{
    if (s)
        s->running = 0;
}

int Screen_IsRunning(Screen* s)
{
    return s ? s->running : 0;
}
