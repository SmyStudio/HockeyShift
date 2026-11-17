#include "arena.h"
#include "config.h"
#include "palette.h"
#include "player.h"
#include "puck.h"
#include <raylib.h>
#include <stdio.h>

int main ()
{
    InitWindow (SCREEN_WIDTH, SCREEN_HEIGHT, "HockeyShift");

    SetTargetFPS (60);
    Puck puck;
    create_puck (&puck);

    Player player;
    create_player (&player);

    while (!WindowShouldClose ())
    {
        ClearBackground (PAL_BACKGROUND);

        BeginDrawing ();

        draw_arena ();
        draw_puck (&puck);
        draw_player(&player);

        EndDrawing ();
    }

    CloseWindow ();

    return 0;
}
