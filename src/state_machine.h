#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "puck.h"
#include "player.h"
#include "enemy.h"

void update_state_machine (Entity players[], Entity enemies[], const Puck *puck);
void update_state_machine_behavior (Entity players[], const Puck *puck,
                                    float deltaTime);

#endif
