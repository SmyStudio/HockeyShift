#include <raylib.h>
#include "collision.h"

#define ENEMY_SIZE 60.0f
#define ENEMY_COLLISION_RADIUS (ENEMY_SIZE / 2.0f)

typedef struct Enemy
{
    Vector2 position;
    Vector2 velocity;
    Collider collider;
} Enemy;

void create_enemy (Enemy *enemy, int position);
void update_enemy (Enemy *enemy, float deltaTime);
void draw_enemy (Enemy *enemy);
