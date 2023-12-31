#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>
#include <array>

#include "../Player.h"
#include "../Book.h"
#include "../Borders.h"
#include "../Setting.h"

#include "../puzzle/Cow.h"

#include "SecondLoc.h"


using namespace std;
using namespace sf;

class FirstLoc{
    private:
        shared_ptr<RenderWindow> window;
        RectangleShape background = RectangleShape(Vector2f(960, 540));
        Texture texture;
        Texture upTexture;
        RectangleShape upground = RectangleShape(Vector2f(960, 540));
        Texture keyTexture;
        RectangleShape key = RectangleShape(Vector2f(960, 540));
        Texture bookTexture;
        RectangleShape bookSprite = RectangleShape(Vector2f(960, 540));

        Music music;
        vector<RectangleShape> boards;

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
        bool runSetting();
    public:
        void setBookInLoc(bool flag);
        void setPageInBook(int num);
        void setAnswer(string answer);
        FirstLoc(int save, shared_ptr<RenderWindow> window, shared_ptr<Player> player, shared_ptr<Book> book);
        void run();
        ~FirstLoc();
};



