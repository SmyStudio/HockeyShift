#include <raylib.h>

typedef struct Enemy
{
    Rectangle bounds;
    Vector2 velocity;
} Enemy;

void create_enemy (Enemy *enemy);
void draw_enemy (Enemy *enemy);
