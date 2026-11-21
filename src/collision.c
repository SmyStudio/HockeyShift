#include "collision.h"

#include <math.h>
#include <raymath.h>

static bool collision_circle_vs_segment (Vector2 position, float radius,
                                         const CollisionShape *shape,
                                         CollisionContact *contact)
{
    Vector2 start = shape->geometry.segment.start;
    Vector2 end = shape->geometry.segment.end;
    Vector2 inwardNormal = shape->geometry.segment.inwardNormal;
    Vector2 edge = Vector2Subtract (end, start);
    float edgeLengthSquared = Vector2LengthSqr (edge);
    float combinedRadius = radius + shape->thickness / 2.0f;
    float amount = Vector2DotProduct (Vector2Subtract (position, start), edge) / edgeLengthSquared;

    if (amount >= 0.0f && amount <= 1.0f)
    {
        Vector2 closest = Vector2Add (start, Vector2Scale (edge, amount));
        float signedDistance = Vector2DotProduct (Vector2Subtract (position, closest), inwardNormal);
        if (signedDistance >= combinedRadius)
        {
            return false;
        }

        contact->normal = inwardNormal;
        contact->penetration = combinedRadius - signedDistance;
        return true;
    }

    amount = Clamp (amount, 0.0f, 1.0f);
    Vector2 closest = Vector2Add (start, Vector2Scale (edge, amount));
    Vector2 difference = Vector2Subtract (position, closest);
    float distanceSquared = Vector2LengthSqr (difference);
    if (distanceSquared >= combinedRadius * combinedRadius)
    {
        return false;
    }

    float distance = sqrtf (distanceSquared);
    contact->normal = distance > 0.0f
                          ? Vector2Scale (difference, 1.0f / distance)
                          : inwardNormal;
    contact->penetration = combinedRadius - distance;
    return true;
}

static bool angle_is_on_arc (float angle, float startAngle, float endAngle)
{
    return angle >= startAngle && angle <= endAngle;
}

static bool collision_circle_vs_arc (Vector2 position, float radius,
                                     const CollisionShape *shape,
                                     CollisionContact *contact)
{
    Vector2 center = shape->geometry.arc.center;
    Vector2 fromCenter = Vector2Subtract (position, center);
    float distance = Vector2Length (fromCenter);
    float angle = atan2f (fromCenter.y, fromCenter.x) * 57.29577951308232f;
    if (angle < 0.0f)
    {
        angle += 360.0f;
    }

    if (!angle_is_on_arc (angle, shape->geometry.arc.startAngle,
                          shape->geometry.arc.endAngle))
    {
        return false;
    }

    float combinedRadius = radius + shape->thickness / 2.0f;
    float arcRadius = shape->geometry.arc.radius;
    if (shape->geometry.arc.centerSideIsAllowed)
    {
        float maximumDistance = arcRadius - combinedRadius;
        if (distance <= maximumDistance)
        {
            return false;
        }

        contact->normal = Vector2Scale (fromCenter, -1.0f / distance);
        contact->penetration = distance - maximumDistance;
        return true;
    }

    float minimumDistance = arcRadius + combinedRadius;
    if (distance >= minimumDistance)
    {
        return false;
    }

    contact->normal = distance > 0.0f
                          ? Vector2Scale (fromCenter, 1.0f / distance)
                          : (Vector2){1.0f, 0.0f};
    contact->penetration = minimumDistance - distance;
    return true;
}

bool collision_circle_vs_shape (Vector2 position, float radius,
                                const CollisionShape *shape,
                                CollisionContact *contact)
{
    if (shape->type == COLLISION_SHAPE_SEGMENT)
    {
        return collision_circle_vs_segment (position, radius, shape, contact);
    }
    if (shape->type == COLLISION_SHAPE_ARC)
    {
        return collision_circle_vs_arc (position, radius, shape, contact);
    }
    return false;
}

void collision_resolve (Vector2 *position, Vector2 *velocity,
                        CollisionContact contact, float restitution)
{
    *position = Vector2Add (
        *position,
        Vector2Scale (contact.normal, contact.penetration));

    float velocityAlongNormal = Vector2DotProduct (*velocity, contact.normal);
    if (velocityAlongNormal < 0.0f)
    {
        *velocity = Vector2Subtract (
            *velocity,
            Vector2Scale (contact.normal, (1.0f + restitution) * velocityAlongNormal));
    }
}