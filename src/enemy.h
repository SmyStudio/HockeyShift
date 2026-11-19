#include <raylib.h>

typedef struct Enemy
{
    Vector2 position;
    Vector2 velocity;
} Enemy;

void create_enemy (Enemy *enemy, int position);
void draw_enemy (Enemy *enemy);
