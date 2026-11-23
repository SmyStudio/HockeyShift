#include "player.h"
#include "ai.h"
#include "collision.h"
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
        .bodyCollider = {
            .type = COLLIDER_CIRCLE,
            .geometry.circle = {
                PLAYER_COLLISION_RADIUS,
                {0.0f, 0.0f},
            },
        },
        .puckReachArea = {
            .type = COLLIDER_CIRCLE,
            .geometry.circle = {
                PLAYER_COLLISION_RADIUS * 2.0f,
                {0.0f, 0.0f}
            }
        },
        .rotation = 0.0f,
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

void draw_player (Entity *player, DynamicConfig *config)
{
    DrawRing((Vector2){
            .x = player->position.x,
            .y = player->position.y
        },
        PLAYER_SIZE * 2.0f - 1.0f,
        PLAYER_SIZE * 2.0f,
        0.0f,
        360.0f,
        32,
        PAL_ELEMENT);

    DrawRectanglePro ((Rectangle){
        .x = player->position.x,
        .y = player->position.y,
        .height = PLAYER_SIZE,
        .width = PLAYER_SIZE},
        (Vector2){
            .x = PLAYER_SIZE / 2.0f,
            .y = PLAYER_SIZE / 2.0f
        },
        player->rotation,
        PAL_PLAYER);

    if (config->shouldRenderDebugEntityData)
    {
        const char *stateText = TextFormat("State: %s", entity_role_to_string(player->role));
        DrawText(stateText, player->position.x - PLAYER_SIZE / 2.0f, player->position.y - PLAYER_SIZE / 2.0f - 12.0f * 1.0f, 12, RAYWHITE);

        const char *canPickupPuckText = TextFormat("CanPickupPuck: %b", player->canPickupPuck);
        DrawText(canPickupPuckText, player->position.x - PLAYER_SIZE / 2.0f, player->position.y - PLAYER_SIZE / 2.0f - 12.0f * 2.0f, 12, RAYWHITE);
    }
}
