#include "entity.h"
#include <raylib.h>

#define ENEMY_SIZE 60.0f
#define ENEMY_COLLISION_RADIUS (ENEMY_SIZE / 2.0f)

void create_enemy (Entity *enemy, int position);
void update_enemy (Entity *enemy, float deltaTime);
void draw_enemy (Entity *enemy);
