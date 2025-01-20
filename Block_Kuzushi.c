#include "raylib.h"
#include "raymath.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1000;
    const int screenHeight = 650;

    InitWindow(screenWidth, screenHeight, "My block kuzushi game");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    Vector2 BordPosition = { 450, 600};
    
    Vector2 BallPosition = { 525, 570};
    Vector2 BallSpeed = { -5, -5};
    
        
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        
        if(BordPosition.x > 0){
            if (IsKeyDown(KEY_A)){
                BordPosition.x -= 6;
            }
        }
        
        if(BordPosition.x < 850){
            if (IsKeyDown(KEY_D)){
                BordPosition.x += 6;
            }
        }
    
        BallPosition.x += BallSpeed.x;
        BallPosition.y += BallSpeed.y;
        
        //if ((ballPosition.x >= (GetScreenWidth() - ballRadius)) || (ballPosition.x <= ballRadius)) ballSpeed.x *= -1.0f;
        //if ((ballPosition.y >= (GetScreenHeight() - ballRadius)) || (ballPosition.y <= ballRadius)) ballSpeed.y *= -1.0f;
        
        
        if((BallPosition.x >= (GetScreenWidth() - 10)) || (BallPosition.x <= 10)){
            BallSpeed.x *= -1.0f;
        }
        
        if((BallPosition.y >= (GetScreenHeight() - 10)) || (BallPosition.y <= 10)){
            BallSpeed.y *= -1.0f;
        }
                
        if(BallPosition.y >= (GetScreenHeight() - 10)){
            BallSpeed.x = 0;
            BallSpeed.y = 0;
        }
        
        if(IsKeyPressed(KEY_W)){
            BallSpeed.x = 5;
            BallSpeed.y = -5;
        }
        
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            DrawCircle( BallPosition.x, BallPosition.y, 5, BLACK);
            
            DrawRectangle( BordPosition.x, BordPosition.y, 150, 30, WHITE);
            DrawRectangleLines( BordPosition.x, BordPosition.y, 150, 30, BLACK);
        }    
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}