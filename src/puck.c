#include "puck.h"
#include "config.h"
#include "palette.h"
#include <raylib.h>
#include <raymath.h>

#define PUCK_SIZE 24

void create_puck (Puck *puck)
{
    *puck = (Puck){(Vector2){SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f},
                   (Vector2){0.0f, 0.0f}};
}

void draw_puck (Puck *puck)
{
    DrawCircleV (puck->position, PUCK_SIZE, PAL_PUCK);
}

void update_puck (Puck *puck, float deltaTime)
{
}
