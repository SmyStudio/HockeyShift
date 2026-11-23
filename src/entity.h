#ifndef ENTITY_H
#define ENTITY_H

#include "collision.h"
#include "ai.h"
#include <raylib.h>
#include <stdbool.h>

typedef struct
{
    Vector2 position;
    Vector2 velocity;
    Collider bodyCollider;
    Collider puckReachArea;
    float rotation;
    int team;
    AIState state;
    EntityRole role;
    bool canPickupPuck;
} Entity;

#endif
