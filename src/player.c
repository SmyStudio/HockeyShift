#include "player.h"
#include "palette.h"
#include <raylib.h>

#define PLAYER_SIZE 60

void create_player (Player *player)
{
    *player = (Player){(Rectangle){100, 100, PLAYER_SIZE, PLAYER_SIZE},
                       (Vector2){0.0f, 0.0f}};
}

void draw_player (Player *player)
{
    DrawRectangleRec (player->bounds, PAL_PLAYER);
}
