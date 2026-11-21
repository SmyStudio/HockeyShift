#include "game.h"
#include "collision.h"
#include <raylib.h>

void create_game (Game *game)
{
    *game = (Game){0};
    arena_init (&game->arena);
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        create_player (&game->players[i], i);
        create_enemy (&game->enemies[i], i);
    }
    create_puck (&game->puck);
}

void draw_game (Game *game)
{
    draw_arena (&game->arena);
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

    const CollisionShape *colliders = arena_get_colliders (&game->arena);

    for (int i = 0; i < ARENA_COLLIDER_COUNT; i++)
    {
        CollisionContact contact;
        if (collision_circle_vs_shape (game->puck.position, PUCK_RADIUS,
                                       &colliders[i], &contact))
        {
            collision_resolve (&game->puck.position, &game->puck.velocity,
                               contact, 0.9f);
        }
    }
}
