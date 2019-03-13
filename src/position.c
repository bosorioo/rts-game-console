#include "position.h"
#include <math.h>
#include <stdlib.h>
#define MAX(a, b) (a > b ? a : b)

Position Position_NewPosition(int x, int y)
{
    Position p;
    p.x = x;
    p.y = y;
    return p;
}

Position Position_Moved(Position p, enum Direction d)
{
    if (d == North)
        p.y--;
    else if (d == South)
        p.y++;
    else if (d == East)
        p.x++;
    else if (d == West)
        p.x--;

    return p;
}

int Position_IsInRange(Position a, Position b, int range)
{
    int distance_x = abs(a.x - b.x);
    int distance_y = abs(a.y - b.y);
    return MAX(distance_x, distance_y) <= range;
}

int Position_Equals(Position a, Position b)
{
    return a.x == b.x && a.y == b.y;
}
