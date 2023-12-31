#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "GameMenu.h"

enum menuItem{
    save,
    sound,
    game
};

using namespace std;
using namespace sf;

class Setting{
    private:
        shared_ptr<RenderWindow> window;
        Texture textureSetting;
        RectangleShape ground = RectangleShape(Vector2f(960, 540));

        unique_ptr<GameMenu> settingMenu;

        int save;
        void writeSave(string textSave);
    public:
        void died();
        Setting();
        Setting(int save, shared_ptr<RenderWindow> window);
        menuItem run(string textSave); // перетащить в приват
        bool result(string saveData, bool& soundIsPlay);
};