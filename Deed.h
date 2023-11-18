#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

using namespace std;
using namespace sf;

class Deed{
    private:
        shared_ptr<RenderWindow> window;
        Texture texture;
        RectangleShape ground = RectangleShape(Vector2f(960, 540));
        Music music;

    public:
        Deed();
        Deed(shared_ptr<RenderWindow> window);
        void died(bool soundIsPaly);
};