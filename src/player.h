#include <raylib.h>

typedef struct Player
{
    Rectangle bounds;
    Vector2 velocity;
} Player;

void create_player (Player *player);
void draw_player (Player *player);