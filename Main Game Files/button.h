#pragma once

#include "raylib.h"

class Button{
    public:
        int x, y, fontSize, width, height, goToIndex, intTarget;
        Color border, innerColor, normalColor, hoverOverColor;
        const char* label = "me when the";
        bool actualButton, boolTarget;
        bool * boolToChange;
        int * intToChange;
        char type = 'n';

    // A button that changes levels
        Button(int _x, int _y, int _width, int _height, int _fontSize, Color _border, Color _innerColor, Color _hoverOverColor, const char* _label, int _goToIndex, bool _actualButton){
            x = _x;
            y = _y;
            fontSize = _fontSize;
            height = _height;
            width = _width;
            border = _border;
            innerColor = normalColor = _innerColor;
            hoverOverColor = _hoverOverColor;
            label = _label;
            goToIndex = _goToIndex;
            actualButton = _actualButton;
        }

        // Button that changes values
        Button(int _x, int _y, int _width, int _height, int _fontSize, Color _border, Color _innerColor, Color _hoverOverColor, const char* _label, char _type, bool _boolTarget, int _intTarget, bool * _boolToChange, int * _intToChange){
            x = _x;
            y = _y;
            fontSize = _fontSize;
            height = _height;
            width = _width;
            border = _border;
            innerColor = normalColor = _innerColor;
            hoverOverColor = _hoverOverColor;
            label = _label;
            type = _type;
            boolTarget = _boolTarget;
            intTarget = _intTarget;
            boolToChange = _boolToChange;
            intToChange = _intToChange;
        }

        void draw();
        void onButtonPress(int * levelNum);
        void changeBoolOnButtonPressed();
        void changeIntOnButtonPress();
};
