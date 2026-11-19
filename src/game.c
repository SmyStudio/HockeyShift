#include "game.h"
#include "arena.h"
#include <raylib.h>

void create_game (Game *game)
{
    *game = (Game){0};
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        create_player (&game->players[i], i);
        create_enemy (&game->enemies[i], i);
    }
}

void draw_game (Game *game)
{
    draw_arena ();
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        draw_enemy (&game->enemies[i]);
        draw_player (&game->players[i]);
    }
}
