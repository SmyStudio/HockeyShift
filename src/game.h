#include "player.h"
#include "enemy.h"
#include "puck.h"

#define MAX_ENTITIES 3

typedef struct
{
    Player players[MAX_ENTITIES];
    Enemy enemies[MAX_ENTITIES];
    Puck puck;
} Game;

void create_game (Game *game);
void draw_game (Game *game);
void update_game (Game *game, float deltaTime);
