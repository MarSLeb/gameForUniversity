#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>

using namespace std;
using namespace sf;

class Player{
    private:
        Texture heroSprites;
        Sprite hero;
        std::shared_ptr<RenderWindow> window;
        float current = 0;
        pair<float, float> oldPos;
        Sound sound;
        SoundBuffer buffer;

    public:
        Player(std::shared_ptr<RenderWindow> window, int x, int y );
        void setPosition(int x, int y);
        float getX();
        float getY();
        void goRightSprite(float time);
        void goLeftSprite(float time);
        void goUp(float time);
        void goDown(float time);
        void goRight(float time);
        void goLeft(float time);
        FloatRect getGlobal();
        void draw();
        void checkCollision(float x, float y, bool soundIsPlay, vector<RectangleShape> boards);
        void movePlayer(float time, bool soundIsPlay, vector<RectangleShape> boards);
};