#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

using namespace std;
using namespace sf;

class FirstBoard{
    private:
        shared_ptr<RenderWindow> window;
        Texture texturePuzzle;
        RectangleShape groundPuzzle = RectangleShape(Vector2f(960, 540));
        Texture textureNote;
        RectangleShape groundNote = RectangleShape(Vector2f(960, 540));
        Texture textureKey;
        RectangleShape key = RectangleShape(Vector2f(960, 540));

        int current = 0;
        SoundBuffer buffer;
        Sound sound;
        Font font;
        bool finish = false;
        bool soundIsPlay = true;

        void right();
        void left();
        void draw();
        void checkCurrentAnswer();
    public:
        FirstBoard();
        FirstBoard(shared_ptr<RenderWindow> window);
        void setFinishFlag(bool flag);
        void setSoundPlaying(bool flag);
        bool run();
};