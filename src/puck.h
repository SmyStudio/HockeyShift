#ifndef PUCK_H
#define PUCK_H

#include <raylib.h>
#include "collision.h"

#define PUCK_RADIUS 24.0f

typedef enum
{
    PUCK_LOOSE,
    PUCK_CONTROLLED
} PuckState;

typedef struct Puck
{
    Vector2 position;
    Vector2 velocity;
    Collider collider;

    PuckState state;
    int ownerTeam;
    int ownerPlayer;
} Puck;

void create_puck (Puck *puck);
void draw_puck(Puck *puck);
void update_puck(Puck *puck, float deltaTime);

#endif
