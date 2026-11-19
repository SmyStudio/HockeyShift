#include "player.h"
#include "config.h"
#include "palette.h"
#include <raylib.h>

#define PLAYER_SIZE 60
#define PLAYER_PLACEMENT_PADDING 40

static const Vector2 positions[3] = {(Vector2){.x = SCREEN_WIDTH / 2.0f - ARENA_CENTER_CIRCLE_RADIUS - PLAYER_PLACEMENT_PADDING,
                                        .y = SCREEN_HEIGHT / 2.0f - 2.0f * PLAYER_SIZE - PLAYER_PLACEMENT_PADDING},
                              (Vector2){.x = SCREEN_WIDTH / 2.0f - ARENA_CENTER_CIRCLE_RADIUS - PLAYER_SIZE - PLAYER_PLACEMENT_PADDING,
                                        .y = SCREEN_HEIGHT / 2.0f - PLAYER_SIZE / 2.0f},
                              (Vector2){.x = SCREEN_WIDTH / 2.0f - ARENA_CENTER_CIRCLE_RADIUS - PLAYER_PLACEMENT_PADDING,
                                        .y = SCREEN_HEIGHT / 2.0f + PLAYER_SIZE + PLAYER_PLACEMENT_PADDING}};

void create_player (Player *player, int position)
{
    *player = (Player){positions[position], (Vector2){0.0f, 0.0f}};
}

void draw_player (Player *player)
{
    DrawRectangleRec ((Rectangle){.x = player->position.x, .y = player->position.y, .height = PLAYER_SIZE, .width = PLAYER_SIZE}, PAL_PLAYER);
}
