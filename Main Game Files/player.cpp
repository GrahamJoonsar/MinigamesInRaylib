#include "player.h"
#include "raylib.h"
#include "boundaries.h"
#include <iostream>

double incrementVel = 0.25; // This is basically the acceleration

bool checkBounds(int x, int y, float xVel, float yVel){ // This is used for collisions
    return true;
}

void Player::draw(){ // Drawing the player to the screen
    DrawCircle(x, y, radius, color);
}

void approachZero(double * vel, int mVel){
    if (*vel >= incrementVel){
        *vel -= incrementVel/2;
    }
    else if (*vel <= -incrementVel){
        *vel += incrementVel/2;
    } else {
        *vel = 0;
    }
}


void Player::move(Blocker * b, int bLength){ // moving the player legally
    // Basic WASD input
    if (playerNum == '1'){
        if (IsKeyDown(KEY_W) && yVel > -maxVel){ yVel -= incrementVel;}
        if (IsKeyDown(KEY_S) && yVel < maxVel){ yVel += incrementVel;}
        if (IsKeyDown(KEY_A) && xVel > -maxVel){ xVel -= incrementVel;}
        if (IsKeyDown(KEY_D) && xVel < maxVel){ xVel += incrementVel;}
    } else if (playerNum == '2'){
        if (IsKeyDown(KEY_UP) && yVel > -maxVel){ yVel -= incrementVel;}
        if (IsKeyDown(KEY_DOWN) && yVel < maxVel){ yVel += incrementVel;}
        if (IsKeyDown(KEY_LEFT) && xVel > -maxVel){ xVel -= incrementVel;}
        if (IsKeyDown(KEY_RIGHT) && xVel < maxVel){ xVel += incrementVel;}
    }
    // Checking the bounds of each blocker
    for (int i = 0; i < bLength; i++){
        b[i].collisionWithPlayer(&x, &y, &xVel, &yVel, radius);
    }
    if (canMove){
        x += xVel;
        y += yVel;
    }
    approachZero(&xVel, maxVel);
    approachZero(&yVel, maxVel);
}