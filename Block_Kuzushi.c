#include "raylib.h"
#include "raymath.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

typedef struct Box{
    float x;                
    float y;                
    float width;           
    float height;
    bool alive;
    int Hp;
}Box;

typedef enum GameScreen {Main = 0, level_1, level_2, level_3, GameOver, HowToScreen} GameScreen;


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1000;
    const int screenHeight = 650;
    
    float DeltaTime = GetFrameTime();
    
    srand(time(NULL));
    
    int AmountOfBoxes = 10;
    
    Box Boxes[AmountOfBoxes];
    
    for(int i = 0; i < AmountOfBoxes; i++){
        Boxes[i].x = 5.0f + 90.0f *(i%10) + 10.0f *(i%10);
        Boxes[i].y = 10.0f + 90.0f *(i/10) + 10.0f *(i/10);
        Boxes[i].width = 95;
        Boxes[i].height = 50;
        Boxes[i].alive = true;
        Boxes[i].Hp = 1;
    }
    
    Vector2 BordPosition = { 450, 600};
    Vector2 BordSize = {150, 30};
    
    Vector2 BallPosition = { 525, 570};
    Vector2 BallSpeed = { -5, -5}; 
    
    Vector2 PowerUpPosition;
    Vector2 PowerUpSpeed = {0, 2};
    bool PowerUpIsAlive = false;
    
    int BordWidth = 150;
    int BordHight = 30;
    Color BordColor = WHITE;
    Color BordFrame = BLACK;
    
    float BallRadius = 5;
    Color BallColor = BLACK;
    
    bool exitWindowRequested = false;   // Flag to request window to exit
    bool exitWindow = false;    // Flag to set window to exit
    bool StartBoutton = false;
    bool HowToBoutton = false;
    bool ExitBoutton = false;
    bool ShootBall = false;

    
    int WinGame = 0;
    int Lives = 3;
    
    int Score = 0;
    
    GameScreen CurenScreen = Main;
            
    InitWindow(screenWidth, screenHeight, "The bounce ball game");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
     
        
    // Main game loop
    while (!exitWindow)    // Detect window close button or ESC key
    { 
        // Update
        //----------------------------------------------------------------------------------
        
        switch(CurenScreen)
        {
            case Main:
            {
                Vector2 mouse = GetMousePosition();
                if (CheckCollisionPointRec(mouse, (Rectangle){150, 264, 120, 50, RAYWHITE})) {
                  StartBoutton = true;
                  if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                      CurenScreen = level_1;
                  }
                }
                else if (CheckCollisionPointRec(mouse, (Rectangle){150, 364, 220, 50, RAYWHITE})) {
                  HowToBoutton = true;
                  if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                      CurenScreen = HowToScreen;
                  }
                }
                else if (CheckCollisionPointRec(mouse, (Rectangle){150, 464, 100, 50, RAYWHITE})) {
                  ExitBoutton = true;
                  if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                      exitWindow = true;
                  }
                }
                else{
                    StartBoutton = false;
                    ExitBoutton = false;
                    HowToBoutton = false;
                }
                
                if(IsKeyPressed(KEY_SPACE)){ 
                    CurenScreen = level_1;
                } 
            }break;
            case level_1:
            {
                if(!exitWindowRequested){
                 if(BordPosition.x > 0){ // moves the board
                    if (IsKeyDown(KEY_A)){
                        BordPosition.x -= 7;
                    }
                }
                
                if(BordPosition.x < 850){ // moves the board
                    if (IsKeyDown(KEY_D)){
                        BordPosition.x += 7;
                    }
                }
            
                BallPosition.x += BallSpeed.x;
                BallPosition.y += BallSpeed.y;
                
                if((BallPosition.x >= (GetScreenWidth() - BallRadius)) || (BallPosition.x <= BallRadius)){//bounce the ball in the oposite direction
                    BallSpeed.x *= -1.0f;
                }
                
                if((BallPosition.y >= (GetScreenHeight() - BallRadius)) || (BallPosition.y <= BallRadius)){ // bounce the ball in the oposite direction
                    BallSpeed.y *= -1.0f;
                }
                        
                if(BallPosition.y >= (GetScreenHeight() - BallRadius)){ // stops the ball when it hits the bottom edge
                    Lives--;
                    Score -= 10;
                    BallSpeed.x = 0;
                    BallSpeed.y = 0;
                    BallPosition.x = 525;
                    BallPosition.y = 570;
                    Score -= 500;
                    ShootBall = true;

                    if(Lives <= 0){
                        WinGame = 0;
                        CurenScreen = GameOver;
                    }
                }
                
                if(WinGame == 10){
                    
                    for(int i = 0; i < AmountOfBoxes * level_2; i++){
                        Boxes[i].x = 5.0f + 90.0f *(i%10) + 10.0f *(i%10);
                        Boxes[i].y = 10.0f + 90.0f *(i/10) + 10.0f *(i/10);
                        Boxes[i].width = 95;
                        Boxes[i].height = 50;
                        Boxes[i].alive = true;
                        Boxes[i].Hp = 1;
                    }
                    
                    BordPosition.x = 450;
                    BordPosition.y = 600;
                    
                    BallPosition.x = 525;
                    BallPosition.y = 570;
                    
                    BallSpeed.x = -5;
                    BallSpeed.y = -5;
                    
                    WinGame = 0;
                    CurenScreen = level_2;
                }
                
                if(PowerUpIsAlive){
                    PowerUpPosition.x += PowerUpSpeed.x;
                    PowerUpPosition.y += PowerUpSpeed.y;
                }
                
                //Bounce the ball of the boxes
                for(int i = 0; i < AmountOfBoxes; i++){
                    if(Boxes[i].alive){
                        if(BallPosition.y >= Boxes[i].y && BallPosition.y <= Boxes[i].y + Boxes[i].height && BallPosition.x >= Boxes[i].x && BallPosition.x <= Boxes[i].x + Boxes[i].width){
                            BallSpeed.y *= -1.0f;
                            Boxes[i].alive = false;
                            Score += 100;
                            WinGame++;
                            if(PowerUpIsAlive == false){
                                int SpawnPowerUp = rand() % 2;
                                if(SpawnPowerUp == 1){
                                    PowerUpPosition.x = BallPosition.x;
                                    PowerUpPosition.y = BallPosition.y;
                                    PowerUpIsAlive = true;
                                }
                            }
                        }
                    }
                }
                
                //The Ball abounce of the bord
                if(BallPosition.y >= BordPosition.y && BallPosition.x >= BordPosition.x && BallPosition.x <= BordPosition.x + BordWidth){
                    float BordCenter = BordPosition.x + (BordWidth/2);
                    float d = BordCenter - BallPosition.x;
                    
                    BallSpeed.y *= -1.0f;
                    BallSpeed.x = (d+1) * -0.1f;
                    
                }
                
                if(PowerUpPosition.y >= BordPosition.y && PowerUpPosition.x >= BordPosition.x && PowerUpPosition.x <= BordPosition.x + BordSize.x){
                    PowerUpIsAlive = false;
                    PowerUpPosition.x = 0;
                    PowerUpPosition.y = 0;
                    Lives++;
                }
                if(PowerUpPosition.y >= 650){
                    PowerUpIsAlive = false;
                    PowerUpPosition.x = 0;
                    PowerUpPosition.y = 0;
                }
                
                if(ShootBall = true && IsKeyPressed(KEY_W)){ // bounce the ball again if it stops
                    BallSpeed.x = 5;
                    BallSpeed.y = -5;
                    ShootBall = false;
                }   
            }
            }break;
            case level_2:
            {
                if(!exitWindowRequested){
                     if(BordPosition.x > 0){ // moves the board
                        if (IsKeyDown(KEY_A)){
                            BordPosition.x -= 7;
                        }
                    }
                    
                    if(BordPosition.x < 850){ // moves the board
                        if (IsKeyDown(KEY_D)){
                            BordPosition.x += 7;
                        }
                    }
                
                    BallPosition.x += BallSpeed.x;
                    BallPosition.y += BallSpeed.y;
                    
                    if((BallPosition.x >= (GetScreenWidth() - BallRadius)) || (BallPosition.x <= BallRadius)){//bounce the ball in the oposite direction
                        BallSpeed.x *= -1.0f;
                    }
                    
                    if((BallPosition.y >= (GetScreenHeight() - BallRadius)) || (BallPosition.y <= BallRadius)){ // bounce the ball in the oposite direction
                        BallSpeed.y *= -1.0f;
                    }
                            
                    if(BallPosition.y >= (GetScreenHeight() - BallRadius)){ // stops the ball when it hits the bottom edge
                        Lives--;
                        Score -= 10;
                        BallSpeed.x = 0;
                        BallSpeed.y = 0;
                        BallPosition.x = 525;
                        BallPosition.y = 570;
                        Score -= 500;
                        ShootBall = true;

                        if(Lives <= 0){
                            WinGame = 0;
                            CurenScreen = GameOver;
                        }
                    }
                    
                    if(WinGame == 10 * level_2){
                        
                        for(int i = 0; i < AmountOfBoxes * level_2; i++){
                            Boxes[i].x = 5.0f + 90.0f *(i%10) + 10.0f *(i%10);
                            Boxes[i].y = 10.0f + 90.0f *(i/10) + 10.0f *(i/10);
                            Boxes[i].width = 95;
                            Boxes[i].height = 50;
                            Boxes[i].alive = true;
                            Boxes[i].Hp = 1;
                        }
                        
                        BordPosition.x = 450;
                        BordPosition.y = 600;
                        
                        BallPosition.x = 525;
                        BallPosition.y = 570;
                        
                        BallSpeed.x = -5;
                        BallSpeed.y = -5;
                        
                        WinGame = 0;
                        CurenScreen = GameOver;
                    }
                    
                    if(PowerUpIsAlive){
                        PowerUpPosition.x += PowerUpSpeed.x;
                        PowerUpPosition.y += PowerUpSpeed.y;
                    }
                    
                    //Bounce the ball of the boxes
                    for(int i = 0; i < AmountOfBoxes * level_2; i++){
                        if(Boxes[i].alive){
                            if(BallPosition.y >= Boxes[i].y && BallPosition.y <= Boxes[i].y + Boxes[i].height && BallPosition.x >= Boxes[i].x && BallPosition.x <= Boxes[i].x + Boxes[i].width){
                                BallSpeed.y *= -1.0f;
                                Boxes[i].alive = false;
                                Score += 100;
                                WinGame++;
                                if(PowerUpIsAlive == false){
                                    int SpawnPowerUp = rand() % 2;
                                    if(SpawnPowerUp == 1){
                                        PowerUpPosition.x = BallPosition.x;
                                        PowerUpPosition.y = BallPosition.y;
                                        PowerUpIsAlive = true;
                                    }
                                }
                            }
                        }
                    }
                    
                    //The Ball abounce of the bord
                    if(BallPosition.y >= BordPosition.y && BallPosition.x >= BordPosition.x && BallPosition.x <= BordPosition.x + BordWidth){
                        float BordCenter = BordPosition.x + (BordWidth/2);
                        float d = BordCenter - BallPosition.x;
                        
                        BallSpeed.y *= -1.0f;
                        BallSpeed.x = (d+1) * -0.1f;
                        
                    }
                    
                    if(PowerUpPosition.y >= BordPosition.y && PowerUpPosition.x >= BordPosition.x && PowerUpPosition.x <= BordPosition.x + BordSize.x){
                        PowerUpIsAlive = false;
                        PowerUpPosition.x = 0;
                        PowerUpPosition.y = 0;
                        Lives++;
                    }
                    if(PowerUpPosition.y >= 650){
                        PowerUpIsAlive = false;
                        PowerUpPosition.x = 0;
                        PowerUpPosition.y = 0;
                    }
                    
                    if(ShootBall = true && IsKeyPressed(KEY_W)){ // bounce the ball again if it stops
                        BallSpeed.x = 5;
                        BallSpeed.y = -5;
                        ShootBall = false;
                    }   
                }    
            }break;
            case level_3:
            {
                
            }break;
            case GameOver:
            {
                Vector2 mouse = GetMousePosition();
                if(CheckCollisionPointRec(mouse, (Rectangle){150, 464, 200, 50, RAYWHITE})){ 
                    StartBoutton = true;
                    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        for(int i = 0; i < AmountOfBoxes; i++){
                            Boxes[i].x = 5.0f + 90.0f *(i%10) + 10.0f *(i%10);
                            Boxes[i].y = 10.0f + 90.0f *(i/10) + 10.0f *(i/10);
                            Boxes[i].width = 95;
                            Boxes[i].height = 50;
                            Boxes[i].alive = true;
                            Boxes[i].Hp = 1;
                        }
                        
                        Lives = 3;
                        
                        BordPosition.x = 450;
                        BordPosition.y = 600;
                        
                        BallPosition.x = 525;
                        BallPosition.y = 570;
                        
                        BallSpeed.x = -5;
                        BallSpeed.y = -5;
                    
                        CurenScreen = Main;
                    }
                }
                else if(CheckCollisionPointRec(mouse, (Rectangle){150, 564, 100, 50, RAYWHITE})){
                    ExitBoutton = true;
                    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                      exitWindow = true;
                    }
                }
                else{
                    ExitBoutton = false;
                    StartBoutton = false;
                }
            }break;
            case HowToScreen:
            {
                Vector2 mouse = GetMousePosition();
                if (CheckCollisionPointRec(mouse, (Rectangle){150, 564, 120, 50, RAYWHITE})) {
                  StartBoutton = true;
                  if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                      CurenScreen = Main;
                  }
                }
                else{
                    StartBoutton = false;
                }
            }break;
            default: break;
        }
        
        // Detect if X-button or KEY_ESCAPE have been pressed to close window
        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) exitWindowRequested = true;
        
        if (exitWindowRequested)
        {
            // A request for close window has been issued, we can save data before closing
            // or just show a message asking for confirmation
            
            if (IsKeyPressed(KEY_Y)) exitWindow = true;
            else if (IsKeyPressed(KEY_N)) exitWindowRequested = false;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            
        switch(CurenScreen)
        {
            case Main:
            {
                DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
                
                DrawRectangle(150, 264, 120, 50, StartBoutton ? GRAY : WHITE);
                DrawText("Start", 170, 270, 30, BLACK);
                
                DrawRectangle(150, 364, 220, 50, HowToBoutton ? GRAY : WHITE);
                DrawText("How to play", 170, 370, 30, BLACK);
                
                DrawRectangle(150, 464, 100, 50, ExitBoutton ? GRAY : WHITE);
                DrawText("Exit", 170, 470, 30, BLACK);
                
                DrawText("The bounce ball game", 70, 70, 80, WHITE);
            }break;
            case level_1:
            {
                DrawCircle( BallPosition.x, BallPosition.y, BallRadius, BallColor);
            
                DrawRectangle( BordPosition.x, BordPosition.y, BordWidth, BordHight, BordColor);
                DrawRectangleLines( BordPosition.x, BordPosition.y, BordWidth, BordHight, BordFrame);
                
                for(int i = 0; i < AmountOfBoxes; i++){
                    if(Boxes[i].alive){
                     DrawRectangle(Boxes[i].x, Boxes[i].y, Boxes[i].width, Boxes[i].height, GREEN);
                     DrawRectangleLines(Boxes[i].x, Boxes[i].y, Boxes[i].width, Boxes[i].height, DARKGREEN);
                    }
                }
                DrawText(TextFormat("Lives: %03i", Lives), 10, 600, 20, LIGHTGRAY);
                
                if(PowerUpIsAlive){
                    DrawRectangle(PowerUpPosition.x, PowerUpPosition.y, 30, 10, RED);
                }
            }break;
            case level_2:
            {
                DrawCircle( BallPosition.x, BallPosition.y, BallRadius, BallColor);
            
                DrawRectangle( BordPosition.x, BordPosition.y, BordWidth, BordHight, BordColor);
                DrawRectangleLines( BordPosition.x, BordPosition.y, BordWidth, BordHight, BordFrame);
                
                for(int i = 0; i < AmountOfBoxes * level_2; i++){
                    if(Boxes[i].alive){
                     DrawRectangle(Boxes[i].x, Boxes[i].y, Boxes[i].width, Boxes[i].height, GREEN);
                     DrawRectangleLines(Boxes[i].x, Boxes[i].y, Boxes[i].width, Boxes[i].height, DARKGREEN);
                    }
                }
                DrawText(TextFormat("Lives: %03i", Lives), 10, 600, 20, LIGHTGRAY);
                
                if(PowerUpIsAlive){
                    DrawRectangle(PowerUpPosition.x, PowerUpPosition.y, 30, 10, RED);
                }
            }break;
            case level_3:
            {
                
            }break;
            case GameOver:
            {
                DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
                DrawText("GameOver press [Space] to restart", 40, 80, 50, WHITE);
                DrawText("Press [ESC] to quit", 40, 180, 50, WHITE);
                DrawText(TextFormat("Score; %03i", Score), 40, 280, 50, WHITE);
                
                DrawRectangle(150, 464, 200, 50, StartBoutton ? GRAY : WHITE);
                DrawText("Main menu", 170, 470, 30, BLACK);
                
                DrawRectangle(150, 564, 100, 50, ExitBoutton ? GRAY : WHITE);
                DrawText("Exit", 170, 570, 30, BLACK);
            }break;
            case HowToScreen:
            {
                DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
                DrawText("Move paddel: A/D", 40, 80, 50, WHITE);
                DrawText("To shot the ball: W", 40, 180, 50, WHITE);
                DrawText("To exit from anywere: ESC", 40, 280, 50, WHITE);
                DrawText("Red blocks are extra lives", 40, 380, 50, WHITE);
                
                DrawRectangle(150, 564, 120, 50, StartBoutton ? GRAY : WHITE);
                DrawText("Back", 170, 570, 30, BLACK);
            }break;
            default: break;
        }
        
        if (exitWindowRequested)
                {
                    DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
                    DrawText("Are you sure you want to exit program? [Y/N]", 40, 180, 30, WHITE);
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