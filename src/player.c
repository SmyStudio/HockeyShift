#include "player.h"
#include "ai.h"
#include "config.h"
#include "palette.h"
#include "physics.h"
#include <raylib.h>
#include <raymath.h>

static const Vector2 positions[3] = {(Vector2){.x = SCREEN_WIDTH / 2.0f - ARENA_CENTER_CIRCLE_RADIUS - ENTITY_PLACEMENT_PADDING,
                                               .y = SCREEN_HEIGHT / 2.0f - 2.0f * PLAYER_SIZE - ENTITY_PLACEMENT_PADDING},
                                     (Vector2){.x = SCREEN_WIDTH / 2.0f - ARENA_CENTER_CIRCLE_RADIUS - PLAYER_SIZE - ENTITY_PLACEMENT_PADDING,
                                               .y = SCREEN_HEIGHT / 2.0f - PLAYER_SIZE / 2.0f},
                                     (Vector2){.x = SCREEN_WIDTH / 2.0f - ARENA_CENTER_CIRCLE_RADIUS - ENTITY_PLACEMENT_PADDING,
                                               .y = SCREEN_HEIGHT / 2.0f + PLAYER_SIZE + ENTITY_PLACEMENT_PADDING}};

void create_player (Entity *player, int position)
{
    *player = (Entity){
        .position = positions[position],
        .velocity = {0.0f, 0.0f},
        .collider = {
            .type = COLLIDER_CIRCLE,
            .geometry.circle = {
                PLAYER_COLLISION_RADIUS,
                {PLAYER_COLLISION_RADIUS, PLAYER_COLLISION_RADIUS},
            },
        },
        .team = 0,
        .state = AI_NONE,
        .role = ROLE_NONE
    };
}

void update_player (Entity *player, float deltaTime)
{
    const float drag = 2.0f;
    player->position = Vector2Add (
        player->position,
        Vector2Scale (player->velocity, deltaTime));
    apply_friction (&player->velocity, drag, deltaTime);
}

void draw_player (Entity *player)
{
    DrawRectangleRec ((Rectangle){.x = player->position.x, .y = player->position.y, .height = PLAYER_SIZE, .width = PLAYER_SIZE}, PAL_PLAYER);
}
