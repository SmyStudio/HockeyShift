#include "puck.h"
#include "config.h"
#include "palette.h"
#include "physics.h"
#include <raylib.h>
#include <raymath.h>

void create_puck (Puck *puck)
{
    *puck = (Puck){
        .position = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f},
        .velocity = {0.0f, 0.0f},
        .collider = {
            .type = COLLIDER_CIRCLE,
            .geometry.circle = {PUCK_RADIUS, {0.0f, 0.0f}},
        },
    };
}

void draw_puck (Puck *puck)
{
    DrawCircleV (puck->position, puck->collider.geometry.circle.radius, PAL_PUCK);
}

void update_puck (Puck *puck, float deltaTime)
{
    if (IsKeyPressed(KEY_LEFT))
    {
        puck->velocity = Vector2Add(puck->velocity, (Vector2){-100.0f, 0.0f});
    }
    if (IsKeyPressed(KEY_RIGHT))
    {
        puck->velocity = Vector2Add(puck->velocity, (Vector2){100.0f, 0.0f});
    }
    if (IsKeyPressed(KEY_UP))
    {
        puck->velocity = Vector2Add(puck->velocity, (Vector2){0.0f, -100.0f});
    }
    if (IsKeyPressed(KEY_DOWN))
    {
        puck->velocity = Vector2Add(puck->velocity, (Vector2){0.0f, 100.0f});
    }
    const float drag = 1.5f;
    puck->position = Vector2Add (puck->position, Vector2Scale (puck->velocity, deltaTime));

    apply_friction (&puck->velocity, drag, deltaTime);
}
