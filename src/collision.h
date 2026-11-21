#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>
#include <raylib.h>

typedef enum
{
    COLLISION_SHAPE_SEGMENT,
    COLLISION_SHAPE_ARC
} CollisionShapeType;

typedef struct
{
    CollisionShapeType type;
    float thickness;
    union
    {
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
} CollisionShape;

typedef struct
{
    Vector2 normal;
    float penetration;
} CollisionContact;

bool collision_circle_vs_shape (Vector2 position, float radius,
                                const CollisionShape *shape,
                                CollisionContact *contact);
void collision_resolve (Vector2 *position, Vector2 *velocity,
                        CollisionContact contact, float restitution);

#endif
