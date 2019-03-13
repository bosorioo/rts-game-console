#include <ncurses.h>
#include "color_manager.h"
#define MAX_COLORS 16

typedef struct
{
    int id;
    short c1, c2;
} _Color;

_Color _COLORS[MAX_COLORS];
int ID = 1;

int Color_GetId(short c1, short c2)
{
    static int init = 0;

    if (!init)
    {
        for (init = 0; init < MAX_COLORS; init++)
            _COLORS[init].id = -1;
    }

    int i;
    for (i = 0; i < MAX_COLORS; i++)
    {
        if (_COLORS[i].id == -1)
        {
            _COLORS[i].id = ID++;
            _COLORS[i].c1 = c1;
            _COLORS[i].c2 = c2;
            init_pair(_COLORS[i].id, _COLORS[i].c1, _COLORS[i].c2);
            return COLOR_PAIR(_COLORS[i].id);
        }
        else if (_COLORS[i].c1 == c1 && _COLORS[i].c2 == c2)
            return COLOR_PAIR(_COLORS[i].id);
    }
    return COLOR_PAIR(1);
}
