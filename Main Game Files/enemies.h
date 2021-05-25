#pragma once
#include "raylib.h"

class Enemy {
    public:
        double x, y, xVel, yVel;
        float radius;
        bool canMove = true;
        Color color = BLACK;

    Enemy (double _x, double _y, double _xVel, double _yVel, bool _canMove, Color _color){
        x = _x;
        y = _y;
        xVel = _xVel;
        yVel = _yVel;
        canMove = _canMove;
        color = _color;
    }

    void draw();
    void move();
};