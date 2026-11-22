#include "entity.h"
#include "config.h"
#include <raylib.h>

#define PLAYER_SIZE 60.0f
#define PLAYER_COLLISION_RADIUS (PLAYER_SIZE / 2.0f)

void create_player (Entity *player, int position);
void update_player (Entity *player, float deltaTime);
void draw_player (Entity *player, DynamicConfig *config);
