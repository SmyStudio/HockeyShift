#include "ai.h"

const char *entity_role_to_string (EntityRole role)
{
    switch (role) {
        case ROLE_NONE: return "None";
        case ROLE_CHASE_PUCK: return "Chase puck";
        default: return "Invalid";
    }
}
