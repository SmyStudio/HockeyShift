#include "enemy.h"
#include "ai.h"
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

void create_enemy (Entity *enemy, int position)
{
    *enemy = (Entity){
        .position = positions[position],
        .velocity = {0.0f, 0.0f},
        .collider = {
            .type = COLLIDER_CIRCLE,
            .geometry.circle = {
                ENEMY_COLLISION_RADIUS,
                {ENEMY_COLLISION_RADIUS, ENEMY_COLLISION_RADIUS},
            },
        },
        .team = 1,
        .state = AI_NONE,
        .role = ROLE_NONE
    };
}

void update_enemy (Entity *enemy, float deltaTime)
{
    const float drag = 2.0f;
    enemy->position = Vector2Add (
        enemy->position,
        Vector2Scale (enemy->velocity, deltaTime));
    apply_friction (&enemy->velocity, drag, deltaTime);
}

void draw_enemy (Entity *enemy)
{
    DrawRectangleRec ((Rectangle){.x = enemy->position.x, .y = enemy->position.y, .width = ENEMY_SIZE, .height = ENEMY_SIZE}, PAL_ENEMY);
}
