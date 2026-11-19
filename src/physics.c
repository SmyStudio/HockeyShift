#include <math.h>
#include <raylib.h>
#include <raymath.h>

void apply_friction (Vector2 *velocity, float drag, float deltaTime)
{
    float damping = expf (-drag * deltaTime);
    *velocity = Vector2Scale (*velocity, damping);

    if (Vector2LengthSqr (*velocity) < 0.01f)
    {
        *velocity = Vector2Zero ();
    }
}
