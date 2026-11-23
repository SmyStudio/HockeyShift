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

typedef struct
{
    Vector2 *position;
    Vector2 *velocity;
    const Collider *collider;
} PhysicsArea;

void apply_friction (Vector2 *velocity, float drag, float deltaTime);
void physics_resolve_body_collisions (PhysicsBody *bodies, size_t bodyCount,
                                 const Collider *staticColliders, size_t colliderCount);
void physics_resolve_area_collisions (PhysicsArea areas[], size_t areaCount, CollisionContact collisions[], int *collisionCount);

#endif
