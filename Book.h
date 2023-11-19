#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

using namespace sf;
using namespace std;


class Book{
    private:
        array<Texture, 5> pages;
        int count = 5;
        int current;
        shared_ptr<RenderWindow> window;
        RectangleShape background = RectangleShape(Vector2f(960, 540));
        Texture keyTexture;
        RectangleShape key = RectangleShape(Vector2f(960, 540));
        int page = 0;
        void nextPage();
        void lastPage();

    public:
        int getPage();
        Book(shared_ptr<RenderWindow> window);
        void setPage(int num);
        void run();
};