#include "collision.h"

#include <math.h>
#include <raymath.h>

static bool collision_circle_vs_segment (Vector2 position, float radius,
                                         Vector2 shapePosition, const Collider *shape,
                                         CollisionContact *contact)
{
    Vector2 start = Vector2Add (shapePosition, shape->geometry.segment.start);
    Vector2 end = Vector2Add (shapePosition, shape->geometry.segment.end);
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
                                     Vector2 shapePosition, const Collider *shape,
                                     CollisionContact *contact)
{
    Vector2 center = Vector2Add (shapePosition, shape->geometry.arc.center);
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

static bool collision_circle_vs_collider (Vector2 position, float radius,
                                          Vector2 colliderPosition,
                                          const Collider *collider,
                                          CollisionContact *contact)
{
    if (collider->type == COLLIDER_SEGMENT)
    {
        return collision_circle_vs_segment (position, radius, colliderPosition, collider, contact);
    }
    if (collider->type == COLLIDER_ARC)
    {
        return collision_circle_vs_arc (position, radius, colliderPosition, collider, contact);
    }
    return false;
}

bool collision_detect (const Collider *first, Vector2 firstPosition,
                       const Collider *second, Vector2 secondPosition,
                       CollisionContact *contact)
{
    if (first->type == COLLIDER_CIRCLE && second->type == COLLIDER_CIRCLE)
    {
        Vector2 firstCenter = Vector2Add (firstPosition, first->geometry.circle.offset);
        Vector2 secondCenter = Vector2Add (secondPosition, second->geometry.circle.offset);
        Vector2 difference = Vector2Subtract (firstCenter, secondCenter);
        float distanceSquared = Vector2LengthSqr (difference);
        float radiusSum = first->geometry.circle.radius + second->geometry.circle.radius;
        if (distanceSquared >= radiusSum * radiusSum)
        {
            return false;
        }

        float distance = sqrtf (distanceSquared);
        contact->normal = distance > 0.0f
                              ? Vector2Scale (difference, 1.0f / distance)
                              : (Vector2){1.0f, 0.0f};
        contact->penetration = radiusSum - distance;
        return true;
    }

    if (first->type == COLLIDER_CIRCLE)
    {
        Vector2 center = Vector2Add (firstPosition, first->geometry.circle.offset);
        return collision_circle_vs_collider (
            center, first->geometry.circle.radius, secondPosition, second, contact);
    }

    if (second->type == COLLIDER_CIRCLE)
    {
        Vector2 center = Vector2Add (secondPosition, second->geometry.circle.offset);
        if (!collision_circle_vs_collider (
                center, second->geometry.circle.radius, firstPosition, first, contact))
        {
            return false;
        }

        contact->normal = Vector2Scale (contact->normal, -1.0f);
        return true;
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

void collision_resolve_pair (Vector2 *firstPosition, Vector2 *firstVelocity,
                             float firstInverseMass, Vector2 *secondPosition,
                             Vector2 *secondVelocity, float secondInverseMass,
                             CollisionContact contact, float restitution)
{
    float totalInverseMass = firstInverseMass + secondInverseMass;
    if (totalInverseMass <= 0.0f)
    {
        return;
    }

    float firstShare = firstInverseMass / totalInverseMass;
    float secondShare = secondInverseMass / totalInverseMass;
    *firstPosition = Vector2Add (
        *firstPosition,
        Vector2Scale (contact.normal, contact.penetration * firstShare));
    *secondPosition = Vector2Subtract (
        *secondPosition,
        Vector2Scale (contact.normal, contact.penetration * secondShare));

    Vector2 relativeVelocity = Vector2Subtract (*firstVelocity, *secondVelocity);
    float velocityAlongNormal = Vector2DotProduct (relativeVelocity, contact.normal);
    if (velocityAlongNormal >= 0.0f)
    {
        return;
    }

    float impulseMagnitude = -(1.0f + restitution) * velocityAlongNormal / totalInverseMass;
    Vector2 impulse = Vector2Scale (contact.normal, impulseMagnitude);
    *firstVelocity = Vector2Add (
        *firstVelocity,
        Vector2Scale (impulse, firstInverseMass));
    *secondVelocity = Vector2Subtract (
        *secondVelocity,
        Vector2Scale (impulse, secondInverseMass));
}