#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <array>
#include <utility>
#include <random>
#include "Book.h"

using namespace std;
using namespace sf;

class Cow{
    private:
        shared_ptr<RenderWindow> window;
        RectangleShape background = RectangleShape(Vector2f(960, 540));
        Texture texture;
        Texture keyTexture;
        RectangleShape key = RectangleShape(Vector2f(960, 540));
        shared_ptr<Book> book;
        Font font;

        array<array<Text, 11>, 4> number;
        array<array<Text, 11>, 4> lastNumber;
        array<int, 4> select;
        array<int, 4> lastSelect;
        Text sel;
        int selX;
        int cur;
        
        array<RectangleShape, 2> upTexture;
        array<Texture, 2> textureForAnswer;

        string answer = "";

        void setText(Text& text, String str, float xpos, float ypos, Color color);
        void drawNum();
        void moveRight();
        void moveLeft();
        void moveUp();
        void moveDown();
        pair<int, int> check();
        void getColor(pair<int, int> cowBull);
        void drawAnswer();
        bool isSpace();
    public:
        void setAnswer(string newAnswer);
        string getAnswer();
        Cow(shared_ptr<RenderWindow> window, shared_ptr<Book> book);
        bool run(bool havingBook);
};