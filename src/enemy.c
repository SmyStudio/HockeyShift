#include "enemy.h"
#include "config.h"
#include "palette.h"
#include "physics.h"
#include <raylib.h>
#include <raymath.h>

static const Vector2 positions[3] = {
    (Vector2){.x = SCREEN_WIDTH / 2.0f + ARENA_CENTER_CIRCLE_RADIUS + ENTITY_PLACEMENT_PADDING - ENEMY_SIZE,
              .y = SCREEN_HEIGHT / 2.0f - 2.0f * ENEMY_SIZE - ENTITY_PLACEMENT_PADDING},
    (Vector2){.x = SCREEN_WIDTH / 2.0f + ARENA_CENTER_CIRCLE_RADIUS + ENEMY_SIZE + ENTITY_PLACEMENT_PADDING - ENEMY_SIZE,
              .y = SCREEN_HEIGHT / 2.0f - ENEMY_SIZE / 2.0f},
    (Vector2){.x = SCREEN_WIDTH / 2.0f + ARENA_CENTER_CIRCLE_RADIUS + ENTITY_PLACEMENT_PADDING - ENEMY_SIZE,
              .y = SCREEN_HEIGHT / 2.0f + ENEMY_SIZE + ENTITY_PLACEMENT_PADDING}};

void create_enemy (Enemy *enemy, int position)
{
    *enemy = (Enemy){
        .position = positions[position],
        .velocity = {0.0f, 0.0f},
        .collider = {
            .type = COLLIDER_CIRCLE,
            .geometry.circle = {
                ENEMY_COLLISION_RADIUS,
                {ENEMY_COLLISION_RADIUS, ENEMY_COLLISION_RADIUS},
            },
        },
    };
}

void update_enemy (Enemy *enemy, float deltaTime)
{
    const float drag = 2.0f;
    enemy->position = Vector2Add (
        enemy->position,
        Vector2Scale (enemy->velocity, deltaTime));
    apply_friction (&enemy->velocity, drag, deltaTime);
}

void draw_enemy (Enemy *enemy)
{
    DrawRectangleRec ((Rectangle){.x = enemy->position.x, .y = enemy->position.y, .width = ENEMY_SIZE, .height = ENEMY_SIZE}, PAL_ENEMY);
}
