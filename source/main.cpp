#include "raylib.h"

#define PLAYER_LIVES 5
#define BRICKS_LINES 5
#define BRICKS_PER_LINE 20
#define BRICKS_POS_Y 50

enum GameScreen
{
    LOGO,
    TITLE,
    GAMEPLAY,
    ENDING
};

struct Player
{
    Vector2 pos;
    Vector2 speed;
    Vector2 size;
    Rectangle bounds;
    int lives;
};

struct Ball
{
    Vector2 pos;
    Vector2 speed;
    Vector2 size;
    float radius;
    bool active;
};

struct Brick
{
    Vector2 pos;
    Vector2 size;
    Rectangle bounds;
    int res;
    bool active;
};


int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    GameScreen screen = LOGO;

    unsigned int framesCounter = 0;
    int gameResult = -1;
    bool gamePaused = false;

    Player player = { 0 };
    Ball ball = { 0 };
    Brick bricks[BRICKS_LINES][BRICKS_PER_LINE] = { 0 };

    player.pos.x = screenWidth / 2;
    player.pos.y = screenWidth / 2;
    player.speed.x = 8.0f;
    player.speed.y = 0.0f;
    player.size.x = 100;
    player.size.y = 24;
    player.lives = PLAYER_LIVES;

    ball.radius = 10.0f;
    ball.active = false;
    ball.pos.x = player.pos.x + player.size.x/2;
    ball.pos.y = player.pos.y - ball.radius*2;
    ball.speed.x = 4.0f;
    ball.speed.y = 4.0f;

    for (int j = 0; j < BRICKS_LINES; j++)
    {
        for (int i = 0; i < BRICKS_PER_LINE; i++)
        {
            bricks[j][i].size.x = screenWidth/BRICKS_PER_LINE;
            bricks[j][i].size.y = 20;
            bricks[j][i].pos.x = i*bricks[j][i].size.x;
            bricks[j][i].pos.y = j*bricks[j][i].size.y + BRICKS_POS_Y;
            bricks[j][i].bounds.x = bricks[j][i].pos.x;
            bricks[j][i].bounds.y = bricks[j][i].pos.y;
            bricks[j][i].bounds.width = bricks[j][i].size.x;
            bricks[j][i].bounds.height = bricks[j][i].size.y;
            bricks[j][i].active = true;
        }
    }

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        framesCounter++;

        switch (screen)
        {
        case LOGO:
            if (framesCounter > 180)
            {
                screen = TITLE;
                framesCounter = 0;
            }
            
            break;
        
        case TITLE:
            if (IsKeyPressed(KEY_ENTER)) screen = GAMEPLAY;
            
            break;
        
        case GAMEPLAY:
            if(!gamePaused)
            {

            }
            if (IsKeyPressed(KEY_ENTER)) screen = ENDING;
            
            break;
        
        case ENDING:
            if(IsKeyPressed(KEY_ENTER)) screen = TITLE;
            
            break;

        default:
            break;
        }


        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            switch (screen)
            {
            case LOGO:
                DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
                DrawText("WAIT for 3 SECONDS...", 290, 220, 20, GRAY);
                
                break;
            
            case TITLE:
                DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
                DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
                DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);

                break;

            case GAMEPLAY:
                DrawRectangle(player.pos.x, player.pos.y, player.size.x, player.size.y, BLACK); // Draw player bar
                DrawCircleV(ball.pos, ball.radius, MAROON);

                for (int j = 0; j < BRICKS_LINES; j++)
                {
                    for (int i = 0; i < BRICKS_PER_LINE; i++)
                    {
                        if (bricks[j][i].active)
                        {
                            if ((i + j) % 2 == 0)
                                DrawRectangle(bricks[j][i].pos.x, bricks[j][i].pos.y, bricks[j][i].size.x, bricks[j][i].size.y, GRAY);
                            else
                                DrawRectangle(bricks[j][i].pos.x, bricks[j][i].pos.y, bricks[j][i].size.x, bricks[j][i].size.y, DARKGRAY);
                        }
                    }
                }

                for (int i = 0; i < player.lives; i++) DrawRectangle(20 + 40*i, screenHeight - 30, 35, 10, LIGHTGRAY);
                
                if (gamePaused) DrawText("GAME PAUSED", screenWidth/2 - MeasureText("GAME PAUSED", 40)/2, screenHeight/2 + 60, 40, GRAY);

                break;

            case ENDING:
                DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
                DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
                DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
                
                break;

            default:
                break;
            }

        EndDrawing();
    }
    
    CloseWindow();        // Close window and OpenGL context

    return 0;
}