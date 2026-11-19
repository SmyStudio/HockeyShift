#include "config.h"
#include "game.h"
#include "palette.h"
#include <raylib.h>
#include <stdio.h>

int main ()
{
    InitWindow (SCREEN_WIDTH, SCREEN_HEIGHT, "HockeyShift");

    SetTargetFPS (60);

    Game game;
    create_game (&game);

    while (!WindowShouldClose ())
    {
        ClearBackground (PAL_BACKGROUND);

        BeginDrawing ();

        draw_game (&game);

        EndDrawing ();
    }

    CloseWindow ();

    return 0;
}
