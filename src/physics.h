#ifndef PHYSICS_H
#define PHYSICS_H

#include "collision.h"
#include <stddef.h>

typedef struct
{
    Vector2 *position;
    Vector2 *velocity;
    const Collider *collider;
    float inverseMass;
} PhysicsBody;

void apply_friction (Vector2 *velocity, float drag, float deltaTime);
void physics_resolve_collisions (PhysicsBody *bodies, size_t bodyCount,
                                 const Collider *staticColliders, size_t colliderCount);

#endif
