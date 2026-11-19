#include "config.h"
#include "game.h"
#include "palette.h"
#include <raylib.h>

int main ()
{
    InitWindow (SCREEN_WIDTH, SCREEN_HEIGHT, "HockeyShift");

    SetTargetFPS (60);

    Game game;
    create_game (&game);

    while (!WindowShouldClose ())
    {
        float deltaTime = GetFrameTime ();
        update_game (&game, deltaTime);

        ClearBackground (PAL_BACKGROUND);

        BeginDrawing ();

        draw_game (&game);

        EndDrawing ();
    }

    CloseWindow ();

    return 0;
}
