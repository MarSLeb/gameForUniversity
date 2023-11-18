#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

using namespace sf;

class Player{
    private:
        Texture heroSprites;
        Sprite hero;
        std::shared_ptr<RenderWindow> window;
        float current = 0;

    public:
        Player(std::shared_ptr<RenderWindow> window, int x, int y );
        void setPosition(int x, int y);
        int getX();
        int getY();
        FloatRect getGlobal();
        void goRightSprite(float time);
        void goLeftSprite(float time);
        void goUp(float time);
        void goDown(float time);
        void goRight(float time);
        void goLeft(float time);
        void draw();
};