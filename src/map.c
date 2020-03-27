#include <stdlib.h>
#include "map.h"
#include "unit.h"
#define ABS(x) (x>0?x:-(x))
struct MapNode
{
    Unit* unit;
};

struct Map
{
    struct MapNode* nodes;
    MapProperties props;
};

Map* Map_NewMap(MapProperties props)
{
    unsigned i, map_size;

    Map* m = (Map*)malloc(sizeof(Map));

    if (!m)
        return NULL;

    map_size = props.width * props.height;

    m->props = props;
    m->nodes = (struct MapNode*)malloc(sizeof(struct MapNode) * map_size);

    if (!m->nodes)
    {
        free(m);
        return NULL;
    }

    for (i = 0; i < map_size; i++)
        m->nodes[i].unit = NULL;

    return m;
}

void Map_GetSize(Map* m, int* out_width, int* out_height)
{
    if (!m)
        return;

    if (out_width)
        *out_width = m->props.width;

    if (out_height)
        *out_height = m->props.height;
}

int Map_OutOfBounds(Map* m, Position p)
{
    return p.x < 0 || p.y < 0 || p.x >= m->props.width || p.y >= m->props.height;
}

void Map_Delete(Map* m)
{
    if (m)
    {
        free(m->nodes);
        free(m);
    }
}

void Map_AddUnit(Map* m, Unit* u)
{
    if (!m || !u)
        return;

    Position p = Unit_GetPosition(u);

    if (Map_OutOfBounds(m, p))
        return;

    m->nodes[p.y * m->props.width + p.x].unit = u;
}

void Map_RemoveUnit(Map* m, Position p)
{
    if (m && !Map_OutOfBounds(m, p))
        m->nodes[p.y * m->props.width + p.x].unit = NULL;
}

Unit* Map_GetUnit(Map* m, Position p)
{
    return m && !Map_OutOfBounds(m, p) ? m->nodes[p.y * m->props.width + p.x].unit : NULL;
}

int Map_CanWalk(Map* m, Position p)
{
    return m && !Map_OutOfBounds(m, p) ? m->nodes[p.y * m->props.width + p.x].unit == NULL : 0;
}
void Map_MoveUnit(Map* m, Unit* u, enum Direction d)
{
    if (!m || !u)
        return;

    Position old = Unit_GetPosition(u);
    Position p = Position_Moved(old, d);

    if (!Map_CanWalk(m, p))
        return;

    Unit_SetPosition(u, p);
    Map_RemoveUnit(m, old);
    Map_AddUnit(m, u);
}

Unit* Map_GetClosestEnemy(Map* m, Unit* u, int maxRange)
{
    if (!m || !u || maxRange <= 0)
        return NULL;

    Unit* enemy = NULL;
    Position p = Unit_GetPosition(u);
    int dx, dy;
    int range = 1;

    while (range++ < maxRange)
    {
        for (dx = -range; dx <= range; dx++)
        {
            for (dy = -range; dy <= range; dy++)
            {
                Position newPosition = Position_NewPosition(p.x + dx, p.y + dy);

                if (Map_OutOfBounds(m, newPosition))
                    continue;

                enemy = Map_GetUnit(m, newPosition);

                if (enemy && !Unit_IsAlly(u, enemy))
                    return enemy;
            }
        }
    }

    return NULL;
}

enum Direction Map_GetDirectionTo(Map* m, Position start, Position goal)
{
    if (Position_Equals(start, goal))
        return None;

    if (Position_IsInRange(start, goal, 1) && !Map_CanWalk(m, goal))
        return None;

    enum Direction directions[2];
    int can_walk[2];

    directions[0] = goal.x > start.x ? East : West;
    directions[1] = goal.y > start.y ? South : North;
    can_walk[0] = goal.x != start.x && Map_CanWalk(m, Position_Moved(start, directions[0]));
    can_walk[1] = goal.y != start.y && Map_CanWalk(m, Position_Moved(start, directions[1]));

    if (can_walk[0] && !can_walk[1])
        return directions[0];
    else if (!can_walk[0] && can_walk[1])
        return directions[1];
    else if (can_walk[0] && can_walk[1])
        return directions[rand() % 2];
    else if (ABS(goal.x - start.x) > ABS(goal.y - start.y))
        return (rand() % 2) ? North : South;

    return rand() % 2 ? West : East;
};

MapProperties Map_DefaultMap()
{
    MapProperties p;
    p.food = 12;
    p.money = 45;
    p.width = 65;
    p.height = 15;
    return p;
}

int Map_GetClosestFreePosition(Map* m, Position* pos)
{
    if (!m || !pos)
        return 0;

    int i, j;
    for (i = -1; i <= 1; i++)
    {
        for (j = -1; j <= 1; j++)
        {
            if (!i && !j)
                continue;

            Position p = Position_NewPosition(pos->x + i, pos->y + j);
            if (Map_CanWalk(m, p))
            {
                *pos = p;
                return 1;
            }
        }
    }
    return 0;
}
