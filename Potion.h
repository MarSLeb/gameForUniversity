#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Book.h"

using namespace std;
using namespace sf;

enum class Pickup {
    Book,
    Note,
    None
};

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
        Texture listKeyTexture;
        RectangleShape listKey = RectangleShape(Vector2f(960, 540));
        Texture listTexture;
        RectangleShape list = RectangleShape(Vector2f(960, 540));
        shared_ptr<Book> book;
    
        Pickup pickup;
        void drawList();
        void drawKey();
        void right();
        void left();
    public:
        Potion();
        Potion(shared_ptr<RenderWindow> window, shared_ptr<Book> book, Pickup pickup);
        int run(bool havingList);
};