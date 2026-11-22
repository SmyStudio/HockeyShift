#include "state_machine.h"
#include "ai.h"
#include "config.h"
#include "entity.h"
#include "raylib.h"
#include "raymath.h"
#include <stdbool.h>

static void move_entity_toward (Entity *entity, Vector2 target, float deltaTime)
{
    const float maxSpeed = 320.0f;
    const float maxAcceleration = 900.0f;
    const float brakingDistance = 110.0f;

    Vector2 center = Vector2Add (
        entity->position,
        entity->collider.geometry.circle.offset);
    Vector2 toTarget = Vector2Subtract (target, center);
    float distance = Vector2Length (toTarget);

    if (distance <= 1.0f)
    {
        entity->velocity = Vector2Zero ();
        return;
    }

    float desiredSpeed = maxSpeed;
    if (distance < brakingDistance)
    {
        desiredSpeed *= distance / brakingDistance;
    }

    Vector2 desiredVelocity = Vector2Scale (
        Vector2Normalize (toTarget),
        desiredSpeed);
    Vector2 acceleration = Vector2Subtract (
        desiredVelocity,
        entity->velocity);

    float accelerationLength = Vector2Length (acceleration);
    if (accelerationLength > maxAcceleration * deltaTime)
    {
        acceleration = Vector2Scale (
            Vector2Normalize (acceleration),
            maxAcceleration * deltaTime);
    }

    entity->velocity = Vector2Add (entity->velocity, acceleration);
}

int find_best_puck_chaser (Entity players[], const Puck *puck)
{
    float minDestination = 5000;
    int bestPlayer = -1;
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        float distance = Vector2Distance(players[i].position, puck->position);
        if (distance < minDestination)
        {
            minDestination = distance;
            bestPlayer = i;
        }
    }

    return bestPlayer;
}

void update_state_machine (Entity players[], Entity enemies[], const Puck *puck)
{
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        players->role = ROLE_NONE;
    }

    bool assigned[MAX_ENTITIES] = {false};

    if (puck->state == PUCK_LOOSE)
    {
        int chaser = find_best_puck_chaser(players, puck);
        players[chaser].role = ROLE_CHASE_PUCK;
        assigned[chaser] = true;
    }
}

void update_state_machine_behavior (
    Entity players[],
    const Puck *puck,
    float deltaTime)
{
    if (puck->state != PUCK_LOOSE)
    {
        return;
    }

    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        switch (players[i].role)
        {
            case ROLE_CHASE_PUCK:
            {
                const float predictionTime = 0.2f;
                Vector2 predictedPuckPosition = Vector2Add (
                    puck->position,
                    Vector2Scale (puck->velocity, predictionTime));

                move_entity_toward (
                    &players[i],
                    predictedPuckPosition,
                    deltaTime);
                break;
            }

            default:
                break;
        }
    }
}
