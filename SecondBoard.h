#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

using namespace std;
using namespace sf;

class SecondBoard{
    private:
        shared_ptr<RenderWindow> window;
        Texture texturePuzzle;
        RectangleShape groundPuzzle = RectangleShape(Vector2f(960, 540));
        Texture textureNote;
        RectangleShape groundNote = RectangleShape(Vector2f(960, 540));

        SoundBuffer buffer;
        Sound sound;
        Font font;
        bool finish = false;
        bool soundIsPlay = true;
        array<Text, 4> chessPieces;
        array<array<Text, 8>, 2> chessCoordinates;
        array<int, 3> currentInSector;
        Text select;
        int currentSector;

        void draw();
        bool checkAnswer();
        void right();
        void left();
        void down();
        void up();
        void setText(Text& text, String str, float xpos, float ypos, Color color);
    public:
        SecondBoard(shared_ptr<RenderWindow> window);
        void setFinishFlag(bool flag);
        void setSoundPlaying(bool flag);
        bool run();
};