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
        RectangleShape background = RectangleShape(Vector2f(960, 540));
        Texture texture;
        Texture upTexture;
        RectangleShape upground = RectangleShape(Vector2f(960, 540));
        Texture keyTexture;
        RectangleShape key = RectangleShape(Vector2f(960, 540));
        Texture listTexture;
        RectangleShape list = RectangleShape(Vector2f(960, 540));
        Texture listKeyTexture;
        RectangleShape listKey = RectangleShape(Vector2f(960, 540));
        Texture noteTexture;
        RectangleShape note = RectangleShape(Vector2f(960, 540));

        array<Texture, 3> potionTexture;
        array<Sprite, 7> potion;
        int curPotion = 8;
        bool finishPotioin = false;
        bool havingBook;

        vector<RectangleShape> boards;

        shared_ptr<Player> player;
        shared_ptr<Book> book;
        unique_ptr<Deed> deed;
        Setting setting;
        Potion potionPazzle;

        Texture noticeTexture;
        RectangleShape notice = RectangleShape(Vector2f(960, 540));
        bool noticeIsRun = false;
        bool noticeEnd = true;

        Music music;
        Sound notionSound;
        bool soundIsPlay = true;
        SoundBuffer bufferForNotion;
        int save;
        bool hasNote = false;

        void drawList();
        string createSaveString();
        void died();
        void drawAll(float time);
        void addNote();
        void drawNote();
        bool runSetting();
    public:
        void setValue(bool flag);
        SecondLoc(int save, shared_ptr<RenderWindow> window, shared_ptr<Player> player, 
            shared_ptr<Book> book, bool havingBook, int listBool = 0);
        void setCurPotion(int num);
        void drawPotion();
        void run();
        ~SecondLoc();
};