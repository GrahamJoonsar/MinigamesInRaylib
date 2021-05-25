#pragma once

#include "raylib.h"

class Blocker{
    public:
        char type;
        int x, y;
        float radius;
        int width, height;
        bool isColliding = true;
        Color color;

        Blocker(int _x, int _y, char _type, float _radius, int _width, int _height, Color _color){
            x = _x;
            y = _y;
            type = _type;
            radius = _radius;
            width = _width;
            height = _height;
            color = _color;
        }

    void draw();
    void collisionWithPlayer(double *px, double *py, double *pxVel, double *pyVel, float pradius);
};