#include "arena.h"
#include "entity.h"
#include "player.h"
#include "enemy.h"
#include "puck.h"
#include "config.h"

typedef struct
{
    Arena arena;
    Entity players[MAX_ENTITIES];
    Entity enemies[MAX_ENTITIES];
    Puck puck;
} Game;

void create_game (Game *game);
void draw_game (Game *game);
void update_game (Game *game, float deltaTime);
