#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "Player.h"
#include "Book.h"
#include <array>
#include "Borders.h"
#include "Cow.h"
#include "SecondLoc.h"
#include "Setting.h"

using namespace std;
using namespace sf;

class FirstLoc{
    private:
        shared_ptr<RenderWindow> window;
        shared_ptr<RectangleShape> background;
        Texture texture;
        Texture upTexture;
        RectangleShape upground = RectangleShape(Vector2f(960, 540));
        Texture keyTexture;
        RectangleShape key = RectangleShape(Vector2f(960, 540));
        Texture bookTexture;
        RectangleShape bookSprite = RectangleShape(Vector2f(960, 540));

        Music music;
        Sound sound;
        SoundBuffer buffer;

        Borders upBord;
        Borders downBord;
        Borders leftBord;
        Borders rightBord;

        shared_ptr<Player> player;
        shared_ptr<Book> book;
        unique_ptr<Cow> cow;
        Setting setting;

        int save;
        bool soundIsPlay = true;
        bool bookInLoc = true;
        string createSaveString();
        void drawBook();
        void drawAll();
    public:
        void setBookInLoc(bool flag);
        void setPageInBook(int num);
        void setAnswer(string answer);
        FirstLoc(int save, shared_ptr<RenderWindow> window, shared_ptr<RectangleShape> background, shared_ptr<Player> player, shared_ptr<Book> book);
        void run();
};



