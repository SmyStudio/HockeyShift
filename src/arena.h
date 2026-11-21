#ifndef ARENA_H
#define ARENA_H

#include "collision.h"
#include <raylib.h>

#define ARENA_COLLIDER_COUNT 10

typedef struct
{
    CollisionShape colliders[ARENA_COLLIDER_COUNT];
} Arena;

void arena_init (Arena *arena);
const CollisionShape *arena_get_colliders (const Arena *arena);
void draw_arena (const Arena *arena);

#endif
