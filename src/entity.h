#ifndef ENTITY_H
#define ENTITY_H

#include "collision.h"
#include "ai.h"
#include <raylib.h>

typedef struct
{
    Vector2 position; // TODO: this corresponds to top-left corner instead of center, this needs to be fixed
    Vector2 velocity;
    Collider collider;
    float rotation;
    int team;
    AIState state;
    EntityRole role;
} Entity;

#endif
