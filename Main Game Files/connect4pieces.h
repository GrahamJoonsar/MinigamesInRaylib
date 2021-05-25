#pragma once
#include "raylib.h"

class Connect4Piece{
    public:
        int x, y;
        int radius = 40;
        int colorNum = -1;
        Color color = RAYWHITE;
};