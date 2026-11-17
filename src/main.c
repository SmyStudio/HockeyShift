#include <raylib.h>
#include <stdio.h>
#include "arena.h"
#include "config.h"
#include "palette.h"
#include "puck.h"

int main ()
{
    InitWindow (SCREEN_WIDTH, SCREEN_HEIGHT, "HockeyShift");

    SetTargetFPS (60);
    Puck puck;
    create_puck (&puck);

    while (!WindowShouldClose ())
    {
        ClearBackground (PAL_BACKGROUND);

        BeginDrawing ();

        draw_arena ();
        draw_puck (&puck);

        EndDrawing ();
    }

    CloseWindow ();

    return 0;
}
