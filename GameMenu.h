#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

using namespace sf;

class GameMenu{	             
private:
    float x; // Координаты меню по X
    float y; // Координаты меню по Y
    int step; // Расстояние между пунктами меню
    int max; // Количество пунктов
    int sizeFont; // Размер шрифта
    int selected; // Выбраннай пункт
    Font font;

    std::array<Text, 5> mainMenu;
    Color textColor = Color::White;
    Color choseColor = Color::Yellow;
    Color border = Color::Black;

    std::shared_ptr<RenderWindow> window;
public:
    GameMenu();
    GameMenu(std::shared_ptr<RenderWindow> window, float menux, float menuy, 
        int index, String name[], int sizeFont = 60, int step = 80);
    void setText(int i, String str, float xpos, float ypos);
    void draw();
    int getX();
    void setCureent(int num);
    int getY(int step);
    void moveUp();
    void moveDown();
    void setColor(Color main, Color chose, Color bord);
    void align(int posx);
    int getSelect();
};


