#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "Borders.h"
#include "Player.h"
#include "Book.h"
#include "Setting.h"
#include "Potion.h"
#include "Deed.h"
#include "Street.h"

using namespace std;
using namespace sf;


class SecondLoc{
    private:
        shared_ptr<RenderWindow> window;
        shared_ptr<RectangleShape> background;
        Texture texture;
        Texture upTexture;
        RectangleShape upground = RectangleShape(Vector2f(960, 540));
        Texture keyTexture;
        RectangleShape key = RectangleShape(Vector2f(960, 540));
        Texture listTexture;
        RectangleShape list = RectangleShape(Vector2f(960, 540));

        array<Texture, 3> potionTexture;
        array<Sprite, 7> potion;
        int curPotion = 8;
        bool finishPotioin = false;

        Potion potionPazzle;

        Borders upBord;
        Borders downBord;
        Borders leftBord;
        Borders rightBord;

        shared_ptr<Player> player;
        shared_ptr<Book> book;
        unique_ptr<Deed> deed;
        unique_ptr<Street> street;
        Setting setting;

        Texture noticeTexture;
        RectangleShape notice = RectangleShape(Vector2f(960, 540));
        bool noticeIsRun = false;

        int countFinishMaze = 0;
        Sound sound;
        Music music;
        Sound notionSound;
        bool soundIsPlay = true;
        SoundBuffer buffer;
        SoundBuffer bufferForNotion;
        int save;
        bool listIsEmpty = false;

        void drawList();
        string createSaveString();
        void died();
    public:
        void setValue(bool flag);
        void setPageInBook(int num);
        SecondLoc(int save, shared_ptr<RenderWindow> window, shared_ptr<RectangleShape> background, shared_ptr<Player> player, 
            shared_ptr<Book> book, int finishMaze = 0, int listBool = 0);
        void setCurPotion(int num);
        void drawPotion();
        void run();
};