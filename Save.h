#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "GameMenu.h"
#include "Book.h"
#include "Player.h"
#include "FirstLoc.h"
#include "SecondLoc.h"
#include "Street.h"
#include "Animation.h"
#include "Home.h"

using namespace sf;
using namespace std;

class Save{
    private:
        shared_ptr<RenderWindow> window;
        RectangleShape background = RectangleShape(Vector2f(960, 540));;
        Texture texture;
        array<string, 4> saveing;
        unique_ptr<GameMenu> menu;
        unique_ptr<GameMenu> deleteOrLoading;
        unique_ptr<Animation> anim;

        shared_ptr<Book> book;
        shared_ptr<Player> player;

        void checkSave(int num);
        void deleteSave(int num);
        void setText(int num);
        bool drawDeleteOrLoading(int num);
        void updateSaving();
    public:
        void setCurrent(int num);
        Save(shared_ptr<RenderWindow> window);
        void run();
};