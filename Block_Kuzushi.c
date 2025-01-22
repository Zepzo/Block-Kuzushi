#include "raylib.h"
#include "raymath.h"
#include <stdint.h>
#include <stdlib.h>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

typedef struct Box{
    float x;                
    float y;                
    float width;           
    float height;
    bool On;
}Box;

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1000;
    const int screenHeight = 650;
    
    int AmountOfBoxes = 20;
    
    Box Boxes[AmountOfBoxes];
    
    for(int i = 0; i < AmountOfBoxes; i++){
        Boxes[i].x = 10.0f + 90.0f *(i%10) + 10.0f *(i%10);
        Boxes[i].y = 20.0f + 90.0f *(i/10) + 10.0f *(i/10);
        Boxes[i].width = 70;
        Boxes[i].height = 30;
        Boxes[i].On = true;
    }
            
    Vector2 BordPosition = { 450, 600};
    
    Vector2 BallPosition = { 525, 570};
    Vector2 BallSpeed = { -5, -5}; 
    
    int BordWidth = 150;
    int BordHight = 30;
    Color BordColor = WHITE;
    Color BordFrame = BLACK;
    
    float BallRadius = 5;
    Color BallColor = BLACK;
            
    InitWindow(screenWidth, screenHeight, "My block kuzushi game");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
     
        
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    { 
        // Update
        //----------------------------------------------------------------------------------
        
        /*for(int i = 0; i < AmountOfBoxes; i++){
            Colition == CheckCollisionCircleRec(BallPosition, BallRadius, Boxes[i]);
        }*/
        
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
        
        //Bounce the ball of the boxes
        for(int i = 0; i < AmountOfBoxes; i++){
            if(BallPosition.y <= Boxes[i].y && BallPosition.y <= Boxes[i].y + Boxes[i].height && BallPosition.x >= Boxes[i].x && BallPosition.x <= Boxes[i].x + Boxes[i].width){
                BallSpeed.y *= -1.0f;
                Boxes[i].width = 0;
                Boxes[i].height = 0;
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
            
            //DrawRectangleRec(Ball, BallColor);
            
            DrawRectangle( BordPosition.x, BordPosition.y, BordWidth, BordHight, BordColor);
            DrawRectangleLines( BordPosition.x, BordPosition.y, BordWidth, BordHight, BordFrame);
            
            for(int i = 0; i < AmountOfBoxes; i++){
                if( Boxes[i].width > 0 && Boxes[i].height > 0){
                 DrawRectangle(Boxes[i].x, Boxes[i].y, Boxes[i].width, Boxes[i].height, GREEN);   
                }
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