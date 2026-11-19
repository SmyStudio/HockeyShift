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
    create_puck (&game->puck);
}

void draw_game (Game *game)
{
    draw_arena ();
    draw_puck (&game->puck);
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        draw_enemy (&game->enemies[i]);
        draw_player (&game->players[i]);
    }
}

void update_game (Game *game, float deltaTime)
{
    update_puck (&game->puck, deltaTime);
}
