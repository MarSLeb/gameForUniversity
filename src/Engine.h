#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "GameMenu.h"
#include "Save.h"


using namespace std;
using namespace sf;

class Engine{
    private:
        shared_ptr<RenderWindow> window 
            = make_shared<RenderWindow>(VideoMode(960, 540), "meowindow", Style::Close); 
        RectangleShape background = RectangleShape(Vector2f(960, 540));
	    Texture background_texture;
        
        unique_ptr<Save> save;
        unique_ptr<GameMenu> menu;
        void draw();
    public:
        Engine();
        void run();
};

