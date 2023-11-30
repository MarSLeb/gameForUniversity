#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "Deed.h"
#include "Borders.h"
#include "Setting.h"
#include "Book.h"
#include "Player.h"
#include "Home.h"

using namespace std;
using namespace sf;

class Street{
    private:
        shared_ptr<RenderWindow> window;

        Texture texture;
        RectangleShape background = RectangleShape(Vector2f(960, 540));
        Texture upSprite;
        RectangleShape sprite = RectangleShape(Vector2f(960, 540));
        Texture upHalf;
        RectangleShape half = RectangleShape(Vector2f(960, 540));
        Texture keyTexture;
        RectangleShape key = RectangleShape(Vector2f(960, 540));

        shared_ptr<Player> player;
        unique_ptr<Deed> deed;
        shared_ptr<Book> book;
        Setting setting;

        Sound sound;
        SoundBuffer buffer;
        Music music;

        int save;
        bool soundIsPlay = true;
        bool havingBook;

        Borders upBord;
        Borders downBord;
        Borders leftBord;
        Borders rightBord;

        void drawUp();
        bool drawRepl();
        string createSaveString();
        void drawAll();
        bool runSetting();
    public:
        void setValue(bool flag);
        void setPageInBook(int num);
        Street(int save, shared_ptr<RenderWindow> window, shared_ptr<Book> book, shared_ptr<Player> player,
               bool havingBook);
        void run(int num);

};
