#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Book.h"

using namespace std;
using namespace sf;

class Potion{
    private:
        shared_ptr<RenderWindow> window;
        Texture texture;
        RectangleShape ground = RectangleShape(Vector2f(960, 540));
        array<Texture, 7> upTexture;
        int curTexture = 0;
        RectangleShape upground = RectangleShape(Vector2f(960, 540));
        Texture keyTexture;
        RectangleShape key = RectangleShape(Vector2f(960, 540));
        shared_ptr<Book> book;

        void right();
        void left();
    public:
        Potion();
        Potion(shared_ptr<RenderWindow> window, shared_ptr<Book> book);
        int run();
};