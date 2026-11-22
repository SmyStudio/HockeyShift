#ifndef AI_H
#define AI_H

typedef enum
{
    AI_NONE,
    AI_MOVING,
    AI_HAS_PUCK,
    AI_PASSING,
    AI_SHOOTING,
    AI_MARKING
} AIState;

typedef enum
{
    ROLE_NONE,
    ROLE_CHASE_PUCK,
    ROLE_SUPPORT_PUCK,
    ROLE_ATTACK_LEFT,
    ROLE_ATTACK_RIGHT,
    ROLE_DEFEND_LEFT,
    ROLE_DEFEND_RIGHT,
    ROLE_MARK_OPPONENT
} EntityRole;

typedef struct
{
    int playerIndex;
    EntityRole role;
    float score;
} AIAssignment;

const char *entity_role_to_string (EntityRole role);

#endif
