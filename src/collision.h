#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>
#include <raylib.h>

typedef enum
{
    COLLIDER_CIRCLE,
    COLLIDER_SEGMENT,
    COLLIDER_ARC
} ColliderType;

typedef struct
{
    ColliderType type;
    float thickness;
    union
    {
        struct
        {
            float radius;
            Vector2 offset;
        } circle;
        struct
        {
            Vector2 start;
            Vector2 end;
            Vector2 inwardNormal;
        } segment;
        struct
        {
            Vector2 center;
            float radius;
            float startAngle;
            float endAngle;
            bool centerSideIsAllowed;
        } arc;
    } geometry;
} Collider;

typedef struct
{
    Vector2 normal;
    float penetration;
    int colliderIndex;
    int collidedIndex;
} CollisionContact;

bool collision_detect (const Collider *first, Vector2 firstPosition,
                       const Collider *second, Vector2 secondPosition,
                       CollisionContact *contact);
void collision_resolve (Vector2 *position, Vector2 *velocity,
                        CollisionContact contact, float restitution);
void collision_resolve_pair (Vector2 *firstPosition, Vector2 *firstVelocity,
                             float firstInverseMass, Vector2 *secondPosition,
                             Vector2 *secondVelocity, float secondInverseMass,
                             CollisionContact contact, float restitution);

#endif
