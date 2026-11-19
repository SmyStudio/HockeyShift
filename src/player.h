#include <raylib.h>

typedef struct Player
{
    Vector2 position;
    Vector2 velocity;
} Player;

void create_player (Player *player, int position);
void draw_player (Player *player);
