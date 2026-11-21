#include "arena.h"
#include "config.h"
#include "palette.h"
#include <raylib.h>

#define ARENA_PADDING 20.0f
#define ARENA_RADIUS 90.0f
#define ARENA_BORDER 8.0f

#define GOAL_WIDTH 240.0f

void arena_init (Arena *arena)
{
    float left = ARENA_PADDING;
    float top = ARENA_PADDING;
    float right = SCREEN_WIDTH - ARENA_PADDING;
    float bottom = SCREEN_HEIGHT - ARENA_PADDING;
    float centerY = SCREEN_HEIGHT / 2.0f;
    float goalTop = centerY - GOAL_WIDTH / 2.0f;
    float goalBottom = centerY + GOAL_WIDTH / 2.0f;
    float radius = ARENA_RADIUS;
    float thickness = ARENA_BORDER;

    arena->colliders[0] = (Collider){
        .type = COLLIDER_SEGMENT,
        .thickness = thickness,
        .geometry.segment = {{left + radius, top}, {right - radius, top}, {0.0f, 1.0f}},
    };
    arena->colliders[1] = (Collider){
        .type = COLLIDER_SEGMENT,
        .thickness = thickness,
        .geometry.segment = {{left + radius, bottom}, {right - radius, bottom}, {0.0f, -1.0f}},
    };

    arena->colliders[2] = (Collider){
        .type = COLLIDER_SEGMENT,
        .thickness = thickness,
        .geometry.segment = {{left, top + radius}, {left, goalTop}, {1.0f, 0.0f}},
    };
    arena->colliders[3] = (Collider){
        .type = COLLIDER_SEGMENT,
        .thickness = thickness,
        .geometry.segment = {{left, goalBottom}, {left, bottom - radius}, {1.0f, 0.0f}},
    };
    arena->colliders[4] = (Collider){
        .type = COLLIDER_SEGMENT,
        .thickness = thickness,
        .geometry.segment = {{right, top + radius}, {right, goalTop}, {-1.0f, 0.0f}},
    };
    arena->colliders[5] = (Collider){
        .type = COLLIDER_SEGMENT,
        .thickness = thickness,
        .geometry.segment = {{right, goalBottom}, {right, bottom - radius}, {-1.0f, 0.0f}},
    };

    arena->colliders[6] = (Collider){
        .type = COLLIDER_ARC,
        .thickness = thickness,
        .geometry.arc = {{left + radius, top + radius}, radius, 180.0f, 270.0f, true},
    };
    arena->colliders[7] = (Collider){
        .type = COLLIDER_ARC,
        .thickness = thickness,
        .geometry.arc = {{right - radius, top + radius}, radius, 270.0f, 360.0f, true},
    };
    arena->colliders[8] = (Collider){
        .type = COLLIDER_ARC,
        .thickness = thickness,
        .geometry.arc = {{right - radius, bottom - radius}, radius, 0.0f, 90.0f, true},
    };
    arena->colliders[9] = (Collider){
        .type = COLLIDER_ARC,
        .thickness = thickness,
        .geometry.arc = {{left + radius, bottom - radius}, radius, 90.0f, 180.0f, true},
    };
}

const Collider *arena_get_colliders (const Arena *arena)
{
    return arena->colliders;
}

void draw_arena (const Arena *arena)
{
    for (int i = 0; i < ARENA_COLLIDER_COUNT; i++)
    {
        const Collider *shape = &arena->colliders[i];
        if (shape->type == COLLIDER_SEGMENT)
        {
            DrawLineEx (shape->geometry.segment.start, shape->geometry.segment.end,
                        shape->thickness, PAL_ELEMENT);
        }
        else
        {
            DrawRing (shape->geometry.arc.center,
                      shape->geometry.arc.radius - shape->thickness / 2.0f,
                      shape->geometry.arc.radius + shape->thickness / 2.0f,
                      shape->geometry.arc.startAngle, shape->geometry.arc.endAngle,
                      32, PAL_ELEMENT);
        }
    }

    DrawCircleLinesEx ((Vector2){SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f},
                       ARENA_CENTER_CIRCLE_RADIUS, 10, PAL_HIGHLIGHT);
}
