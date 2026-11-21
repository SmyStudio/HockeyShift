#include <raylib.h>

#define PUCK_RADIUS 24.0f

typedef struct Puck
{
    Vector2 position;
    Vector2 velocity;
} Puck;

void create_puck (Puck *puck);
void draw_puck(Puck *puck);
void update_puck(Puck *puck, float deltaTime);