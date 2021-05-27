
#include "raylib.h"
#include "player.h"
#include "loader.h" // Levels
#include "enemies.h"
#include "connect4pieces.h"
#include <math.h>
#include <iostream>
#include <string>


void loadLevel(Loader * l, Player * p, Player * p2){
    p->x = l->playerStartingX;
    p->y = l->playerStartingY;
    p2->x = l->player2StartingX;
    p2->y = l->player2StartingY;
    p->canMove = l->playerCanMove;
    p2->canMove = l->player2CanMove;
}

double distance(double x1, double y1, double x2, double y2){
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int roundToMultipleOf(int numToRound, int multiple){
    if (numToRound % multiple > multiple / 2){
        return numToRound + (multiple - (numToRound % multiple));
    } else {
        return numToRound - (numToRound % multiple);
    }
}

// Setup and declaration
const int screenWidth = 1000;
const int screenHeight = 500;
bool running = true;
int currentLevel = 0; 
int pastLevel = 0;

Player player(250, 250, 20, GREEN, '1'); // Player declaration
Player player2(250, 250, 20, BLUE, '2');

// Enemy Declaration
Enemy enemy(500, 250, 0, 0, false, BLACK); // For testing, not really used yet


/********** Dodgeball Code *************/


Blocker dodgeBallBlockers[] = {{0, 0, 'r', 0, 20, screenHeight, GRAY}};

Button dodgeBallButtons[] = {{850, 450, 145, 45, 50, GRAY, LIGHTGRAY, DARKGRAY, "BACK", 1, true}};

Loader dodgeBall(-40, -40, -40, -40, false, false, 1, connect4Blockers, 1, connect4Buttons);

/********** Connect 4 Code *************/

// Drawing the white circles of the connect 4 board
void drawConnect4BackGround(){
    for (int y = 40; y < 500; y += 80){
        for (int x = 60; x < 800; x += 80){
            DrawCircle(x, y, 32, RAYWHITE);
        }
    }
}

int playerTurn = 0;
int connect4Time = 0; // Necessary so the click of the button on start doesnt place a piece
bool redWon = false;
bool yellowWon = false;

Connect4Piece connect4Pieces[10][6]; // the array that represents the board (sideways)

// Visual representation of the board
// Sideways to make it easier for programming the different ways I need to manipulate it
/*
* * * * * *
* * * * * *
* * * * * *
* * * * * *
* * * * * *
* * * * * *
* * * * * *
* * * * * *
* * * * * *
* * * * * *
*/

// Pretty self explanatory
// Draws where the piece will go
void drawThePreImageOfTheConnect4Piece(){
    int preimageX = roundToMultipleOf(GetMouseX() + 40, 80) - 20;
    int freeIndex = -1;
    for (int i = 5; i >= 0; i--){
        if (connect4Pieces[(preimageX - 40)/80][i].colorNum == -1){
            freeIndex = i;
            break;
        }
    }
    if (freeIndex != -1){
        if (playerTurn % 2 == 0){ // red turn
            DrawCircle(preimageX > 780 ? 780 : preimageX, freeIndex * 80 + 40, 32, {255, 0, 0, 124});
        } else { // yellow turn
            DrawCircle(preimageX > 780 ? 780 : preimageX, freeIndex * 80 + 40, 32, {255, 255, 0, 124});
        }
    }
}

void drawTheConnect4Pieces(){
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 6; j++){
            DrawCircle(i * 80 + 60, j * 80 + 40, 32, connect4Pieces[i][j].color);
        }
    }
    if (redWon){
        DrawRectangle(850, 15, 120, 30, GRAY);
        DrawText("RED WON", 855, 20, 25, RED);
    } else if (yellowWon){
        DrawRectangle(850, 15, 140, 30, GRAY);
        DrawText("YELLOW WON", 855, 20, 20, YELLOW);
    }
}

void checkPiecesForWinner(){
    // Looping through the array of pieces
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 6; j++){
            if (i <= 6){ // Horizontal
                if ((connect4Pieces[i][j].colorNum == connect4Pieces[i + 1][j].colorNum) &&
                    (connect4Pieces[i][j].colorNum == connect4Pieces[i + 2][j].colorNum) &&
                    (connect4Pieces[i][j].colorNum == connect4Pieces[i + 3][j].colorNum)){
                        if (connect4Pieces[i][j].colorNum == 0){
                            redWon = true;
                            return;
                        } else if (connect4Pieces[i][j].colorNum == 1){
                            yellowWon = true;
                            return;
                        }
                }
            }
            if (j <= 2){ // Vertical
                if ((connect4Pieces[i][j].colorNum == connect4Pieces[i][j + 1].colorNum) &&
                    (connect4Pieces[i][j].colorNum == connect4Pieces[i][j + 2].colorNum) &&
                    (connect4Pieces[i][j].colorNum == connect4Pieces[i][j + 3].colorNum)){
                        if (connect4Pieces[i][j].colorNum == 0){
                            redWon = true;
                            return;
                        } else if (connect4Pieces[i][j].colorNum == 1){
                            yellowWon = true;
                            return;
                        }
                }
            }
            if (i <= 6 && j <= 2){ // Diagonal
                if ((connect4Pieces[i][j].colorNum == connect4Pieces[i + 1][j + 1].colorNum) &&
                    (connect4Pieces[i][j].colorNum == connect4Pieces[i + 2][j + 2].colorNum) &&
                    (connect4Pieces[i][j].colorNum == connect4Pieces[i + 3][j + 3].colorNum)){
                        if (connect4Pieces[i][j].colorNum == 0){
                            redWon = true;
                            return;
                        } else if (connect4Pieces[i][j].colorNum == 1){
                            yellowWon = true;
                            return;
                        }
                }
            }
        }
    }
}

void getConnect4Input(){
    connect4Time++;
    int preimageX = roundToMultipleOf(GetMouseX() + 40, 80) - 20;
    int freeIndex = -1;
    if (IsMouseButtonPressed(0) && connect4Time > 10 && !redWon && !yellowWon){
        for (int i = 5; i >= 0; i--){
            if (connect4Pieces[(preimageX - 40)/80][i].colorNum == -1){ // This is how I stack the pieces on top of eachother
                freeIndex = i;
                break;
            }
        }
        if (freeIndex != -1){
            connect4Pieces[(preimageX - 40)/80][freeIndex].color = playerTurn % 2 == 0 ? RED : YELLOW;
            connect4Pieces[(preimageX - 40)/80][freeIndex].colorNum = playerTurn % 2 == 0 ? 0 : 1;
            playerTurn++;
            checkPiecesForWinner();
        }
    }
}

// Connect 4 level
Blocker connect4Blockers[] = {{0, 0, 'r', 0, 845, screenHeight, SKYBLUE}};

Button connect4Buttons[] = {{850, 450, 145, 45, 50, GRAY, LIGHTGRAY, DARKGRAY, "BACK", 1, true}};

Loader connect4(-40, -40, -40, -40, false, false, 1, connect4Blockers, 1, connect4Buttons);

//Test level
Blocker testBlockers[] = {{400, 200, 'r', 0, 200, 200, SKYBLUE},
                            {400, 200, 'c', 25, 200, 200, SKYBLUE},
                            {600, 200, 'c', 25, 200, 200, SKYBLUE},
                            {400, 400, 'c', 25, 200, 200, SKYBLUE},
                            {600, 400, 'c', 25, 200, 200, SKYBLUE},};

Button testButtons[] = {{850, 450, 145, 45, 50, GRAY, LIGHTGRAY, DARKGRAY, "BACK", 1, true}};

Loader test(100, 250, 50, 250, true, true, 5, testBlockers, 1, testButtons);

void testCode(){
    if (distance(player.x, player.y, player2.x, player2.y) < 40){
        double angle = atan2(player.y - player2.y, player.x - player2.x);
        player.xVel = cos(angle) * 5;
        player.yVel = sin(angle) * 5;
        player2.xVel = cos(angle + 3.1415926) * 5;
        player2.yVel = sin(angle + 3.1415926) * 5;
    }
}


// Maze (Probably finished)
Blocker mazeBlockers[] = {{0, 0, 'r', 0, 20, screenHeight, GRAY}, // left
                            {0, screenHeight - 20, 'r', 0, 850, 20, GRAY}, // bottom
                            {830, 0, 'r', 0, 20, screenHeight, GRAY}, // right
                            {0, 0, 'r', 0, 850, 20, GRAY}, // top
                            {70, 0, 'r', 0, 20, screenHeight - 100, GRAY},
                            {140, 80, 'r', 0, 20, screenHeight - 100, GRAY},
                            {210, 0, 'r', 0, 20, screenHeight - 100, GRAY},
                            {280, 80, 'r', 0, 20, screenHeight - 100, GRAY},
                            {350, 0, 'r', 0, 20, screenHeight - 100, GRAY},
                            {420, 80, 'r', 0, 20, screenHeight - 100, GRAY},
                            {490, 0, 'r', 0, 20, screenHeight - 100, GRAY},
                            {560, 80, 'r', 0, 20, screenHeight - 100, GRAY},
                            {630, 0, 'r', 0, 20, screenHeight - 100, GRAY},
                            {700, 80, 'r', 0, 20, screenHeight - 100, GRAY},
                            {720, 400, 'r', 0, 110, 80, RED}};

Button mazeButtons[] = {{850, 450, 145, 45, 50, GRAY, LIGHTGRAY, DARKGRAY, "BACK", 1, true}};

Loader maze(40, 40, 45, 40, true, true, 15, mazeBlockers, 1, mazeButtons);

void mazeCode(){
    if (720 < player.x && player.y > 400){ // If the green player is in the goal
        player.canMove = false;
        player2.canMove = false;
        DrawText("GREEN", 855, 5, 30, GREEN);
        DrawText("WINS", 855, 35, 30, GREEN);
    } else if (720 < player2.x && player2.y > 400){ // If the blue player is in the goal
        player.canMove = false;
        player2.canMove = false;
        DrawText("BLUE", 855, 5, 30, BLUE);
        DrawText("WINS", 855, 35, 30, BLUE);
    }
}

// Sumo
int greenSumoScore = 0;
int blueSumoScore = 0;
double sumoTime = 1;

Blocker sumoBlockers[] = {{0, 0, 'r', 0, 40, screenHeight, DARKBLUE},
                            {0, 0, 'r', 0, screenWidth - 155, 40, DARKBLUE},
                            {0, screenHeight - 40, 'r', 0, screenWidth, 40, DARKBLUE},
                            {screenWidth - 195, 0, 'r', 0, 40, screenHeight, DARKBLUE},
                            {420, 250, 'c', 190, 0, 0, {255, 0, 0, 100}}};

Button sumoButtons[] = {{850, 450, 145, 45, 50, GRAY, LIGHTGRAY, DARKGRAY, "BACK", 1, true}};

Loader sumo(260, 250, 580, 250, true, true, 5, sumoBlockers, 1, sumoButtons);

void resetSumo(int winner){
    sumoTime = 0;
    sumoBlockers[4].radius = 190;
    player.x = 260;
    player2.x = 580;
    player.y = player2.y = 250;
    player.xVel = player.yVel = player2.xVel = player2.yVel = 0;
    player.canMove = player2.canMove = false;
    if (winner == 1){greenSumoScore++;}
    if (winner == 2){blueSumoScore++;}
}

void sumoCode(){
    sumoTime += 0.01;
    if (sumoTime >= 1){
        player.canMove = player2.canMove = true;
        sumoBlockers[4].radius -= 0.1;
        DrawText("Go!", 50, 50, 30, BLACK);
    } else {
        DrawText("Ready", 50, 50, 30, BLACK);
    }
    DrawText("Green Score: ", 850, 10, 20, GREEN);
    DrawText(std::to_string(greenSumoScore).c_str(), 850, 30, 20, GREEN);
    DrawText("Blue Score: ", 850, 50, 20, BLUE);
    DrawText(std::to_string(blueSumoScore).c_str(), 850, 70, 20, BLUE);
    if (distance(420, 250, player.x, player.y) > sumoBlockers[4].radius){
        resetSumo(2); // Green player wins
    } else if (distance(420, 250, player2.x, player2.y) > sumoBlockers[4].radius){ // Blue player wins
        resetSumo(1);
    } else if (distance(player.x, player.y, player2.x, player2.y) < 40){ // Collsion between players
        double angle = atan2f(player.y - player2.y, player.x - player2.x);
        player.xVel = cos(angle) * 5;
        player.yVel = sin(angle) * 5;
        player2.xVel = cos(angle + 3.1415926) * 5;
        player2.yVel = sin(angle + 3.1415926) * 5;
    }
}

// Credits (Finished)
Blocker creditsBlockers[] = {{0, 0, 'r', 0, screenWidth, screenHeight, LIGHTGRAY}};
Button creditsButtons[] = {{400, 50, 240, 45, 50, GRAY, LIGHTGRAY, DARKGRAY, "CREDITS", 0, false},
                            {100, 150, 760, 45, 50, GRAY, LIGHTGRAY, DARKGRAY, "CREATOR: GRAHAM JOONSAR", 0, false},
                            {100, 250, 770, 45, 50, GRAY, LIGHTGRAY, DARKGRAY, "BETA TESTER: LUKE WILSON", 0, false},
                            {700, 400, 145, 45, 50, GRAY, LIGHTGRAY, DARKGRAY, "BACK", 0, true}};

Loader credits(500, -20, 500, -20, false, false, 1, creditsBlockers, 4, creditsButtons);

// Level Select
Blocker levelSelectBlockers[] = {{0, 0, 'r', 0, screenWidth, screenHeight, LIGHTGRAY}};
Button levelSelectButtons[] = {{300, 50, 405, 45, 50, DARKGRAY, LIGHTGRAY, LIGHTGRAY, "LEVEL SELECT", 0, false},
                                {337, 150, 125, 35, 40, GRAY, LIGHTGRAY, DARKGRAY, "RACE", 3, true},
                                {337, 250, 125, 35, 40, GRAY, LIGHTGRAY, DARKGRAY, "TEST", 4, true},
                                {337, 350, 125, 35, 40, GRAY, LIGHTGRAY, DARKGRAY, "SUMO", 5, true},
                                {297, 440, 215, 35, 40, GRAY, LIGHTGRAY, DARKGRAY, "Connect 4", 6, true},
                                {700, 400, 145, 45, 50, GRAY, LIGHTGRAY, DARKGRAY, "BACK", 0, true}};

Loader levelSelect(500, -20, 500, -20, false, false, 1, levelSelectBlockers, 6, levelSelectButtons);

// Main menu Setup (Finished?)
Blocker mainMenuBlockers[] = {{0, 0, 'r', 0, screenWidth, screenHeight, LIGHTGRAY}};
Button mainMenuButtons[] = {{350, 50, 300, 45, 50, DARKGRAY, LIGHTGRAY, LIGHTGRAY, "MAIN MENU", 0, false},
                            {337, 150, 325, 35, 40, GRAY, LIGHTGRAY, DARKGRAY, "LEVEL SELECT", 1, true},
                            {400, 250, 195, 35, 40, GRAY, LIGHTGRAY, DARKGRAY, "CREDITS", 2, true},
                            {445, 400, 110, 35, 40, RED, LIGHTGRAY, DARKGRAY, "QUIT", 'b', false, 0, &running, nullptr}};

Loader mainMenu(500, -20, 500, -20, false, false, 1, mainMenuBlockers, 4, mainMenuButtons);

Loader allLevels[] = {mainMenu, levelSelect, credits, maze, test, sumo, connect4};

int main(void){
    mazeBlockers[14].isColliding = false; // the goal for race
    sumoBlockers[4].isColliding = false; // The sumo ring

    Loader * level; // this is the level that will be displayed
    level = &allLevels[0]; // Setting the starting level, probably main menu
    loadLevel(&mainMenu, &player, &player2); // Loading the level

    InitWindow(screenWidth, screenHeight, "The game");

    SetTargetFPS(60);
    while (!WindowShouldClose() && running)
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        for (int i = 0; i < level->lSBLength; i++){ // Drawing all the blockers for the level
            level->levelSpecificBlockers[i].draw();
        }
        for (int i = 0; i < level->lSBLength2; i++){ // Drawing all the buttons for the level
            level->levelSpecificButtons[i].draw();
        }
        for (int i = 0; i < level->lSBLength2; i++){ // Checking for button presses
            if (level->levelSpecificButtons[i].type == 'n'){ // Normal button that changes levels
                level->levelSpecificButtons[i].onButtonPress(&currentLevel);
            } else if (level->levelSpecificButtons[i].type == 'b'){ // Button tha changes a boolean
                level->levelSpecificButtons[i].changeBoolOnButtonPressed();
            }/* else {
                level->levelSpecificButtons[i].changeIntOnButtonPress()
            }*/
        }

        player.draw(); // Drawing and moving the player legally
        player.move(level->levelSpecificBlockers, level->lSBLength);
        player2.draw(); // Drawing and moving the player legally
        player2.move(level->levelSpecificBlockers, level->lSBLength);


        if (currentLevel != pastLevel){ // The level changed
            level = &allLevels[currentLevel];
            loadLevel(&allLevels[currentLevel], &player, &player2);
            switch (currentLevel){ // Initializing the level
                case 5: // sumo
                    greenSumoScore = blueSumoScore = 0;
                    break;
                case 6:
                    playerTurn = connect4Time = 0;
                    redWon = yellowWon = false;
                    for (int i = 0; i < 10; i++){ // resetting the grid
                        for (int j = 0; j < 6; j++){
                            connect4Pieces[i][j] = *(new Connect4Piece);
                        }
                    }
                    break;
            }
        }

        switch(currentLevel){
            case 3: // If the maze level is active
                mazeCode();
                break;
            case 5: // if sumo
                sumoCode();
                break;
            case 4: // if test
                testCode();
                break;
            case 6: // Connect 4
                drawConnect4BackGround();
                drawTheConnect4Pieces();
                drawThePreImageOfTheConnect4Piece();
                getConnect4Input();
                break;
        }

        pastLevel = currentLevel;

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
