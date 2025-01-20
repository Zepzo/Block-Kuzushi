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
        Rectangle Bord = { BordPosition.x, BordPosition.y, 150, 30};
        Rectangle Ball = {BallPosition.x, BallPosition.y, 10, 10}; 
        
        bool Collition = false;

        // Update
        //----------------------------------------------------------------------------------
        
        // bool CheckCollisionCircleRec(Vector2 center, float radius, Rectangle rec);
        
        Collition = CheckCollisionRecs(Bord, Ball);

        
        if(BordPosition.x > 0){ // moves the board
            if (IsKeyDown(KEY_A)){
                BordPosition.x -= 6;
            }
        }
        
        if(BordPosition.x < 850){ // moves the board
            if (IsKeyDown(KEY_D)){
                BordPosition.x += 6;
            }
        }
    
        BallPosition.x += BallSpeed.x;
        BallPosition.y += BallSpeed.y;
        
        if((BallPosition.x >= (GetScreenWidth() - 10)) || (BallPosition.x <= 10)){ // bounce the ball in the oposite direction
            BallSpeed.x *= -1.0f;
        }
        
        if((BallPosition.y >= (GetScreenHeight() - 10)) || (BallPosition.y <= 10)){ // bounce the ball in the oposite direction
            BallSpeed.y *= -1.0f;
        }
        
        if(Collition){
            BallSpeed.x *= -1.0f;
            BallSpeed.y *= -1.0f;
        }
                
        if(BallPosition.y >= (GetScreenHeight() - 10)){ // stops the ball when it hits the bottom edge
            BallSpeed.x = 0;
            BallSpeed.y = 0;
        }
        
        if(IsKeyPressed(KEY_W)){ // bounce the ball again if it stops
            BallSpeed.x = 5;
            BallSpeed.y = -5;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            //DrawCircle( BallPosition.x, BallPosition.y, 5, BLACK);
            DrawRectangleRec(Ball, BLACK);
            
            //DrawRectangle( BordPosition.x, BordPosition.y, 150, 30, WHITE);
            DrawRectangleRec(Bord, WHITE);
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