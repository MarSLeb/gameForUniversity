#include "Borders.h"

Borders::Borders(){}

Borders::Borders(vector<lines> borders): border(borders){}

bool Borders::getContact(int x, int y){
    for (auto i : border){
        if(x >= i.startX && x <= i.endX && y >= i.startY && y <= i.endY){
            return true;
        }
    }
    return false;
}