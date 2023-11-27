#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Book.h"
#include "Player.h"
#include "Setting.h"
#include "Borders.h"
#include "FirstBoard.h"
#include "SecondBoard.h"
#include "Deed.h"

using namespace std;
using namespace sf;

class Home{
    private:
        shared_ptr<RenderWindow> window;
        Texture texture;
        Sprite ground;
        Texture upTexture;
        RectangleShape upground = RectangleShape(Vector2f(960, 540));
        Texture keyTexture;
        RectangleShape key = RectangleShape(Vector2f(950, 540));

        float xForTexture = 0.;
        bool havingBook;
        NoteFourth hasNote = NoteFourth::none;

        shared_ptr<Player> player;
        shared_ptr<Book> book;
        Setting setting;
        FirstBoard firstBoard;
        SecondBoard secondBoard;
        unique_ptr<Deed> deed;

        Borders upBord;
        Borders downBord;
        Borders leftBord;
        Borders rightBord;

        Sound sound;
        SoundBuffer buffer;
        Music music; 
        bool soundIsPlay = true;
        int save;
        
        void goRight(float time);
        void goLeft(float time);
        string createSaveString();
        void drawAll();

        bool runFirstBoard();
        bool runSecondBoard();
    public:
        void died();
        void setValume(bool flag);
        void setCountHasNote(NoteFourth note);
        Home(int save, shared_ptr<RenderWindow> window, shared_ptr<Player> player, shared_ptr<Book> book,
            bool havingBook,  bool soundIsPlay = true);
        void run();
};
