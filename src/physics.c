#include "physics.h"

#include <math.h>
#include <raylib.h>
#include <raymath.h>

#define COLLISION_RESTITUTION 0.8f
#define COLLISION_SOLVER_ITERATIONS 3

void apply_friction (Vector2 *velocity, float drag, float deltaTime)
{
    float damping = expf (-drag * deltaTime);
    *velocity = Vector2Scale (*velocity, damping);

    if (Vector2LengthSqr (*velocity) < 0.01f)
    {
        *velocity = Vector2Zero ();
    }
}

void physics_resolve_collisions (PhysicsBody *bodies, size_t bodyCount,
                                 const Collider *staticColliders, size_t colliderCount)
{
    const Vector2 staticPosition = {0.0f, 0.0f};

    for (size_t iteration = 0; iteration < COLLISION_SOLVER_ITERATIONS; iteration++)
    {
        for (size_t bodyIndex = 0; bodyIndex < bodyCount; bodyIndex++)
        {
            PhysicsBody *body = &bodies[bodyIndex];

            for (size_t colliderIndex = 0; colliderIndex < colliderCount; colliderIndex++)
            {
                CollisionContact contact;
                if (collision_detect (
                        body->collider, *body->position,
                        &staticColliders[colliderIndex], staticPosition, &contact))
                {
                    collision_resolve (
                        body->position, body->velocity, contact, COLLISION_RESTITUTION);
                }
            }
        }

        for (size_t firstIndex = 0; firstIndex < bodyCount; firstIndex++)
        {
            for (size_t secondIndex = firstIndex + 1; secondIndex < bodyCount; secondIndex++)
            {
                PhysicsBody *first = &bodies[firstIndex];
                PhysicsBody *second = &bodies[secondIndex];
                CollisionContact contact;

                if (collision_detect (
                        first->collider, *first->position,
                        second->collider, *second->position, &contact))
                {
                    collision_resolve_pair (
                        first->position, first->velocity, first->inverseMass,
                        second->position, second->velocity, second->inverseMass,
                        contact, COLLISION_RESTITUTION);
                }
            }
        }
    }
}
