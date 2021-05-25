#include "button.h"
#include "raylib.h"

void Button::draw(){
    DrawRectangle(x - 5, y - 5, width + 10, height + 10, border);
    DrawRectangle(x, y, width, height, innerColor);
    DrawText(label, x + 5, y, fontSize, RED);
}

void Button::onButtonPress(int * levelNum){
    if (actualButton){
        if (x - 5 < GetMouseX() && GetMouseX() < x + width + 10 && y - 5 < GetMouseY() && GetMouseY() < y + height + 10){
            innerColor = hoverOverColor;
            if (IsMouseButtonPressed(0)){
                *levelNum = goToIndex;
            }
        } else {
            innerColor = normalColor;
        }
    }
}

void Button::changeBoolOnButtonPressed(){
    if (x - 5 < GetMouseX() && GetMouseX() < x + width + 10 && y - 5 < GetMouseY() && GetMouseY() < y + height + 10){
        innerColor = hoverOverColor;
        if (IsMouseButtonPressed(0)){
            *boolToChange = boolTarget;
        }
    } else {
        innerColor = normalColor;
    }
}

void Button::changeIntOnButtonPress(){
    if (type == 'a'){ // If its an assignment
        *intToChange = intTarget;
    } else if (type == 'i'){ // if its an increment
        *intToChange += intTarget;
    }
}