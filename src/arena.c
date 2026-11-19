#include "arena.h"
#include "config.h"
#include "palette.h"
#include <raylib.h>
#include <stdio.h>

#define ARENA_PADDING 20.0f
#define ARENA_RADIUS 90.0f
#define ARENA_BORDER 8.0f

#define GOAL_WIDTH 240.0f

void draw_arena_borders ()
{
    float left = ARENA_PADDING;
    float top = ARENA_PADDING;
    float right = SCREEN_WIDTH - ARENA_PADDING;
    float bottom = SCREEN_HEIGHT - ARENA_PADDING;

    float centerY = SCREEN_HEIGHT / 2.0f;
    float halfGoal = GOAL_WIDTH / 2.0f;

    float goalTop = centerY - halfGoal;
    float goalBottom = centerY + halfGoal;

    float radius = ARENA_RADIUS;

    // Top border
    DrawLineEx ((Vector2){left + radius, top}, (Vector2){right - radius, top},
                ARENA_BORDER, PAL_ELEMENT);

    // Bottom border
    DrawLineEx ((Vector2){left + radius, bottom},
                (Vector2){right - radius, bottom}, ARENA_BORDER, PAL_ELEMENT);

    // Left border (goal opening in the middle)
    DrawLineEx ((Vector2){left, top + radius}, (Vector2){left, goalTop},
                ARENA_BORDER, PAL_ELEMENT);

    DrawLineEx ((Vector2){left, goalBottom}, (Vector2){left, bottom - radius},
                ARENA_BORDER, PAL_ELEMENT);

    // Right border (goal opening in the middle)
    DrawLineEx ((Vector2){right, top + radius}, (Vector2){right, goalTop},
                ARENA_BORDER, PAL_ELEMENT);

    DrawLineEx ((Vector2){right, goalBottom}, (Vector2){right, bottom - radius},
                ARENA_BORDER, PAL_ELEMENT);

    // Rounded corners
    // Top-left
    DrawRing ((Vector2){left + radius, top + radius},
              radius - ARENA_BORDER / 2.0f, radius + ARENA_BORDER / 2.0f,
              180.0f, 270.0f, 32, PAL_ELEMENT);

    // Top-right
    DrawRing ((Vector2){right - radius, top + radius},
              radius - ARENA_BORDER / 2.0f, radius + ARENA_BORDER / 2.0f,
              270.0f, 360.0f, 32, PAL_ELEMENT);

    // Bottom-right
    DrawRing ((Vector2){right - radius, bottom - radius},
              radius - ARENA_BORDER / 2.0f, radius + ARENA_BORDER / 2.0f, 0.0f,
              90.0f, 32, PAL_ELEMENT);

    // Bottom-left
    DrawRing ((Vector2){left + radius, bottom - radius},
              radius - ARENA_BORDER / 2.0f, radius + ARENA_BORDER / 2.0f, 90.0f,
              180.0f, 32, PAL_ELEMENT);

    // Center circle
    DrawCircleLinesEx ((Vector2){SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f},
                       ARENA_CENTER_CIRCLE_RADIUS, 10, PAL_HIGHLIGHT);
}

void draw_arena ()
{
    draw_arena_borders ();
}
