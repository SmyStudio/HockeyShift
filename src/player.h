#include <raylib.h>
#include "collision.h"

#define PLAYER_SIZE 60.0f
#define PLAYER_COLLISION_RADIUS (PLAYER_SIZE / 2.0f)

typedef struct Player
{
    Vector2 position;
    Vector2 velocity;
    Collider collider;
} Player;

void create_player (Player *player, int position);
void update_player (Player *player, float deltaTime);
void draw_player (Player *player);
