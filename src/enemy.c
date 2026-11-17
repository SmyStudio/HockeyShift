#include "enemy.h"
#include "palette.h"
#include <raylib.h>

#define ENEMY_SIZE 60

void create_enemy (Enemy *enemy)
{
    *enemy = (Enemy){(Rectangle){1000, 100, ENEMY_SIZE, ENEMY_SIZE},
                     (Vector2){0.0f, 0.0f}};
}

void draw_enemy (Enemy *enemy)
{
    DrawRectangleRec (enemy->bounds, PAL_ENEMY);
}
