#include "raylib.h"
#include "raymath.h"
#include <stdint.h>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1000;
    const int screenHeight = 650;
    
    int AmountOfBoxes = 30;
    
    Rectangle Boxes[AmountOfBoxes];
    
    for(int i = 0; i < AmountOfBoxes; i++){
        Boxes[i].x = 10.0f + 90.0f *(i%10) + 10.0f *(i%10);
        Boxes[i].y = 20.0f + 90.0f *(i/10) + 10.0f *(i/10);
        Boxes[i].width = 70;
        Boxes[i].height = 30;
    }
    
    Vector2 BordPosition = { 450, 600};
    
    Vector2 BallPosition = { 525, 570};
    Vector2 BallSpeed = { -5, -5}; 
    
    int BordWidth = 150;
    int BordHight = 30;
    Color BordColor = WHITE;
    Color BordFrame = BLACK;
    
    int BallRadius = 5;
    Color BallColor = BLACK;

    InitWindow(screenWidth, screenHeight, "My block kuzushi game");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
     
        
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    { 
        // Update
        //----------------------------------------------------------------------------------
        
        // bool CheckCollisionCircleRec(Vector2 center, float radius, Rectangle rec);
        //Collition = CheckCollisionRecs(Bord, Ball);

        
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
        
        if((BallPosition.x >= (GetScreenWidth() - 5)) || (BallPosition.x <= 5)){ // bounce the ball in the oposite direction
            BallSpeed.x *= -1.0f;
        }
        
        if((BallPosition.y >= (GetScreenHeight() - 5)) || (BallPosition.y <= 5)){ // bounce the ball in the oposite direction
            BallSpeed.y *= -1.0f;
        }
                
        if(BallPosition.y >= (GetScreenHeight() - 5)){ // stops the ball when it hits the bottom edge
            BallSpeed.x = 0;
            BallSpeed.y = 0;
        }
        
        for(int i = 0; i < AmountOfBoxes; i++){
            if(BallPosition.y <= Boxes[i].y && BallPosition.y <= Boxes[i].y + Boxes[i].height && BallPosition.x >= Boxes[i].x && BallPosition.x <= Boxes[i].x + Boxes[i].width){
                BallSpeed.y *= -1.0f;
            }
        }
        
        //The Ball abounce of the bord
        if(BallPosition.y >= BordPosition.y && BallPosition.x >= BordPosition.x && BallPosition.x <= BordPosition.x + BordWidth){
            BallSpeed.y *= -1.0f;
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

            DrawCircle( BallPosition.x, BallPosition.y, BallRadius, BallColor);
            
            DrawRectangle( BordPosition.x, BordPosition.y, BordWidth, BordHight, BordColor);
            DrawRectangleLines( BordPosition.x, BordPosition.y, BordWidth, BordHight, BordFrame);
            
            for(int i = 0; i < AmountOfBoxes; i++){
                DrawRectangleRec(Boxes[i], GREEN);
            }
            
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