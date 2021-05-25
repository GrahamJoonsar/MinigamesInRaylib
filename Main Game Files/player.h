#pragma once

#include "raylib.h"
#include "boundaries.h"

class Player{
    public: // Declaring neccesarry variables
        double x, y;
        const int maxVel = 6;
        float radius;
        double xVel, yVel;
        bool canMove = true;
        Color color = RED;
        char playerNum;
        // Constructor
        Player(float _x, float _y, float _radius, Color _color, char _playerNum){
            x = _x;
            y = _y;
            radius = _radius;
            color = _color;
            playerNum = _playerNum;
        }

    void move(Blocker * b, int bLength);
    void draw();
};