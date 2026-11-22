#include "game.h"
#include "physics.h"
#include "state_machine.h"
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
        draw_player (&game->players[i], &game->config);
    }
}

void update_game (Game *game, float deltaTime)
{
    if (IsKeyPressed(KEY_F1))
    {
        game->config.shouldRenderDebugEntityData = !game->config.shouldRenderDebugEntityData;
    }
    update_state_machine(game->players, game->enemies, &game->puck);
    update_state_machine_behavior (
        game->players,
        &game->puck,
        deltaTime);
    update_puck (&game->puck, deltaTime);

    PhysicsBody bodies[1 + MAX_ENTITIES * 2] = {
        {
            .position = &game->puck.position,
            .velocity = &game->puck.velocity,
            .collider = &game->puck.collider,
            .inverseMass = 1.0f,
        },
    };

    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        update_player (&game->players[i], deltaTime);
        update_enemy (&game->enemies[i], deltaTime);
        bodies[1 + i] = (PhysicsBody){
            .position = &game->players[i].position,
            .velocity = &game->players[i].velocity,
            .collider = &game->players[i].collider,
            .inverseMass = 0.05f,
        };
        bodies[1 + MAX_ENTITIES + i] = (PhysicsBody){
            .position = &game->enemies[i].position,
            .velocity = &game->enemies[i].velocity,
            .collider = &game->enemies[i].collider,
            .inverseMass = 0.05f,
        };
    }

    physics_resolve_collisions (
        bodies, 1 + MAX_ENTITIES * 2,
        arena_get_colliders (&game->arena), ARENA_COLLIDER_COUNT);
}
