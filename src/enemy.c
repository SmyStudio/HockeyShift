#include "enemy.h"
#include "config.h"
#include "palette.h"
#include <raylib.h>

#define ENEMY_SIZE 60

static const Vector2 positions[3] = {(Vector2){.x = SCREEN_WIDTH / 2.0f + ARENA_CENTER_CIRCLE_RADIUS + ENTITY_PLACEMENT_PADDING,
                                               .y = SCREEN_HEIGHT / 2.0f - 2.0f * ENEMY_SIZE - ENTITY_PLACEMENT_PADDING},
                                     (Vector2){.x = SCREEN_WIDTH / 2.0f + ARENA_CENTER_CIRCLE_RADIUS + ENEMY_SIZE + ENTITY_PLACEMENT_PADDING,
                                               .y = SCREEN_HEIGHT / 2.0f - ENEMY_SIZE / 2.0f},
                                     (Vector2){.x = SCREEN_WIDTH / 2.0f + ARENA_CENTER_CIRCLE_RADIUS + ENTITY_PLACEMENT_PADDING,
                                               .y = SCREEN_HEIGHT / 2.0f + ENEMY_SIZE + ENTITY_PLACEMENT_PADDING}};

void create_enemy (Enemy *enemy, int position)
{
    *enemy = (Enemy){positions[position], (Vector2){0.0f, 0.0f}};
}

void draw_enemy (Enemy *enemy)
{
    DrawRectangleRec ((Rectangle){.x = enemy->position.x, .y = enemy->position.y, .width = ENEMY_SIZE, .height = ENEMY_SIZE}, PAL_ENEMY);
}
