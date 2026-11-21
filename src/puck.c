#include "puck.h"
#include "config.h"
#include "palette.h"
#include "physics.h"
#include <raylib.h>
#include <raymath.h>

void create_puck (Puck *puck)
{
    *puck = (Puck){(Vector2){SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f}, (Vector2){2000.0f, 1000.0f}};
}

void draw_puck (Puck *puck)
{
    DrawCircleV (puck->position, PUCK_RADIUS, PAL_PUCK);
}

void update_puck (Puck *puck, float deltaTime)
{
    const float drag = 1.5f;
    puck->position = Vector2Add (puck->position, Vector2Scale (puck->velocity, deltaTime));

    apply_friction (&puck->velocity, drag, deltaTime);
}
