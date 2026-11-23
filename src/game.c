#include "game.h"
#include "collision.h"
#include "config.h"
#include "physics.h"
#include "state_machine.h"
#include <raylib.h>
#include <stdbool.h>

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
        draw_enemy (&game->enemies[i], &game->config);
        draw_player (&game->players[i], &game->config);
    }
}

void handle_input (Game *game)
{
    if (IsKeyPressed(KEY_F1))
    {
        game->config.shouldRenderDebugEntityData = !game->config.shouldRenderDebugEntityData;
    }
}

void get_all_physics_bodies (Game *game, PhysicsBody bodies[])
{
    bodies[0] = (PhysicsBody){
        .position = &game->puck.position,
        .velocity = &game->puck.velocity,
        .collider = &game->puck.collider,
        .inverseMass = 1.0f,
    };

    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        bodies[1 + i] = (PhysicsBody){
            .position = &game->players[i].position,
            .velocity = &game->players[i].velocity,
            .collider = &game->players[i].bodyCollider,
            .inverseMass = 0.05f,
        };
        bodies[1 + MAX_ENTITIES + i] = (PhysicsBody){
            .position = &game->enemies[i].position,
            .velocity = &game->enemies[i].velocity,
            .collider = &game->enemies[i].bodyCollider,
            .inverseMass = 0.05f,
        };
    }
}

void handle_body_physics (Game *game)
{
    PhysicsBody bodies[1 + MAX_ENTITIES * 2] = {0};
    get_all_physics_bodies (game, bodies);
    physics_resolve_body_collisions (
        bodies, 1 + MAX_ENTITIES * 2,
        arena_get_colliders (&game->arena), ARENA_COLLIDER_COUNT);
}

void get_all_physics_areas (Game *game, PhysicsArea areas[])
{
    areas[0] = (PhysicsArea){
        .position = &game->puck.position,
        .velocity = &game->puck.velocity,
        .collider = &game->puck.collider
    };

    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        areas[1 + i] = (PhysicsArea){
            .position = &game->players[i].position,
            .velocity = &game->players[i].velocity,
            .collider = &game->players[i].puckReachArea
        };
        areas[1 + MAX_ENTITIES + i] = (PhysicsArea){
            .position = &game->enemies[i].position,
            .velocity = &game->enemies[i].velocity,
            .collider = &game->enemies[i].puckReachArea
        };
    }
}

void handle_grabable_puck (Game *game, CollisionContact collisionContacts[], int collisionCount)
{
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        game->players[i].canPickupPuck = false;
        game->enemies[i].canPickupPuck = false;
    }

    if (collisionCount == 0)
        return;

    int puckContactingPlayerIds[128] = {0};
    int puckContactingPlayerCount = 0;
    for (int i = 1; i < collisionCount; i++)
    {
        CollisionContact placeholder = collisionContacts[i];
        if (placeholder.collidedIndex == 0)
        {
            if (collisionContacts[i].colliderIndex >= 1 && collisionContacts[i].colliderIndex <= 3) // Player
            {
                game->players[collisionContacts[i].colliderIndex - 1].canPickupPuck = true;
            } else if (collisionContacts[i].colliderIndex >= 4 && collisionContacts[i].colliderIndex <= 6) {
                game->enemies[collisionContacts[i].colliderIndex - 4].canPickupPuck = true;
            }
        }
    }
}

void handle_area_physics (Game *game)
{
    PhysicsArea areas[1 + MAX_ENTITIES * 2] = {0};
    CollisionContact collisionContacts[128] = {0};
    int collisionCount = 0;
    get_all_physics_areas (game, areas);
    physics_resolve_area_collisions (areas, 1 + MAX_ENTITIES * 2, collisionContacts, &collisionCount);
    handle_grabable_puck (game, collisionContacts, collisionCount);
}

void update_game (Game *game, float deltaTime)
{
    handle_input(game);
    update_state_machine(game->players, game->enemies, &game->puck);
    update_state_machine_behavior (
        game->players,
        &game->puck,
        deltaTime);
    update_puck (&game->puck, deltaTime);

    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        update_player (&game->players[i], deltaTime);
        update_enemy (&game->enemies[i], deltaTime);
    }

    handle_body_physics (game);
    handle_area_physics (game);
}
