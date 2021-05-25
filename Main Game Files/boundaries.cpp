#include "raylib.h"
#include "boundaries.h"
#include <math.h>
#include <iostream>

double pastYVel = 0;
double pastXVel = 0;

double dist(double x1, double y1, double x2, double y2){
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void Blocker::draw(){
    if (type == 'c'){ // if its a circle
        DrawCircle(x, y, radius, color);
    }
    else if (type == 'r'){ // if its a rectangle
        DrawRectangle(x, y, width, height, color);
    }
}

bool insideOfRect(int rx, int ry, int rwidth, int rheight, double px, double py, double pxVel, double pyVel, float pradius){
    if (rx - pradius < px + pxVel && px + pxVel < rx + rwidth + pradius){
        if (ry - pradius < py + pyVel && py + pyVel < ry + rheight + pradius){
            return true;
        }
    }
    return false;
}

void moveOutsideOfBlocker(double *px, double *py, int bx, int by, int bwidth, int bheight, float pradius){ // This code is for if the player manages to get inside the blocker, and it will push them out.
    if (insideOfRect(bx, by, bwidth, bheight, *px, *py, 0, 0, pradius)){
        // Getting the angle from the player to the center of the rectangle
        double angle = atan2(by + bheight/2 - *py, bx + bwidth/2 - *px) + 3.1415926;
        // Putting the player outside the rectangle with the same angle to the center
        *px = cos(angle) * (sqrt(pow(bwidth/2, 2) + pow(bheight/2, 2)) + 25) * 1.1 + bx + bwidth/2;
        *py = sin(angle) * (sqrt(pow(bwidth/2, 2) + pow(bheight/2, 2)) + 25) * 1.1 + by + bheight/2;
        std::cout << *px << "_" <<*py << std::endl;
    }
}

void Blocker::collisionWithPlayer(double *px, double *py, double *pxVel, double *pyVel, float pradius){
    if (type == 'c' && isColliding){ // If it's a circle
        if (dist(*px + *pxVel, *py + *pyVel, x, y) < radius + pradius){
            *pxVel = 0;
            *pyVel = 0;
        }
    } else if (type == 'r' && isColliding){ // If it's a rectangle
        if (insideOfRect(x, y, width, height, *px, *py, *pxVel, *pyVel, pradius)){ 
            double tempPYVel = *pyVel; // Needed in case the next if statement is true
            double tempPXVel = *pxVel;
            // These two if statements are for if the player wants to slide along the side of the rect blocker
            // using two movement keys
            // Kinda janky, but works perfectly
            if (insideOfRect(x, y + tempPYVel/0.25, width, height, *px, *py, *pxVel, *pyVel, pradius)){*pxVel = 0;}
            if (insideOfRect(x + tempPXVel, y, width, height, *px, *py, *pxVel, *pyVel, pradius)){*pyVel = 0;}
            moveOutsideOfBlocker(px, py, x, y, width, height, pradius);
        }
    }
}