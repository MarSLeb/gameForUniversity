#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

using namespace std;
using namespace sf;

enum Anim{
    start,
    end
};

class Animation{
    private:
        shared_ptr<RenderWindow> window;
        array<Texture, 100> texture;
        RectangleShape background = RectangleShape(Vector2f(960, 540));

        int curTexture = 0;
        int countTexture;
 
    public: 
        Animation(shared_ptr<RenderWindow> window, Anim numberOfAnimation);
        void run();
};