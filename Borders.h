#pragma once
#include <vector>

using namespace std;

struct lines{
    int startX;
    int endX;
    int startY;
    int endY;

    lines(int sX, int eX, int sY, int eY){
            startX = sX;
            endX = eX;
            startY = sY;
            endY = eY;
    }
};


class Borders{
    private:
        vector<lines> border;
    public:
        Borders();
        Borders(vector<lines> borders);
        bool getContact(int x, int y);
};


