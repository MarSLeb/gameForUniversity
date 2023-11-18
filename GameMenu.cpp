#include "GameMenu.h"
#include <stdexcept>
#include <iostream>

GameMenu::GameMenu() {}

GameMenu::GameMenu(std::shared_ptr<RenderWindow> window, float menux, float menuy, 
            int index, String name[], int sizeFont, int step) :
    window(window), x(menux), y(menuy), sizeFont(sizeFont), step(step) {
        font.loadFromFile("font/menu.ttf");
        max = index;
        for(int i = 0, ypos = y; i < max; i++, ypos += step){
            setText(i, name[i], x, ypos);
        }
        selected = 0;
        mainMenu[selected].setFillColor(choseColor);
}

void GameMenu::setText(int i, String str, float xpos, float ypos){
    Text* text = &mainMenu[i];
    text->setFont(font);
    text->setFillColor(textColor);
    text->setString(str);  
    text->setCharacterSize(sizeFont);
    text->setPosition(xpos, ypos);
    text->setOutlineThickness(3);
    text->setOutlineColor(border);
}

int GameMenu::getX() {return x;}
int GameMenu::getY(int num) {return (y + step * num);}

void GameMenu::draw(){
    for(int i = 0; i < max; i++){
        window->draw(mainMenu[i]);
    }
}

void GameMenu::setCureent(int num){
    mainMenu[selected].setFillColor(choseColor);
    selected = num;
    mainMenu[selected].setFillColor(textColor);
}

void GameMenu::moveUp(){
    selected--;
    if(selected >= 0){
        mainMenu[selected].setFillColor(choseColor);
        mainMenu[selected + 1].setFillColor(textColor);
    }
    else{
        mainMenu[0].setFillColor(textColor);
        selected = max - 1;
        mainMenu[selected].setFillColor(choseColor);
    }
}

void GameMenu::moveDown(){
    selected++;
    if (selected < max) {
		mainMenu[selected - 1].setFillColor(textColor);
		mainMenu[selected].setFillColor(choseColor);
	}
	else
	{
		mainMenu[max - 1].setFillColor(textColor);
		selected = 0;
		mainMenu[selected].setFillColor(choseColor);
	}
}

void GameMenu::setColor(Color main, Color chose, Color bord)
{
    textColor = main;
    choseColor = chose;
    border = bord;
    for(int i = 0; i < max; i++){
        mainMenu[i].setFillColor(textColor);
        mainMenu[i].setOutlineColor(border);
    }
    mainMenu[selected].setFillColor(choseColor);
}

void GameMenu::align(int posx){
    float nullx = 0;
    for(int i = 0; i < max; i++){
        switch (posx)
        {
        case 0:
            nullx = 0;
            break;
        case 1:
            nullx = mainMenu[i].getLocalBounds().width;
            break;
        case 2:
            nullx = mainMenu[i].getLocalBounds().width / 2;
            break;
        
        default:
            break;
        }
        mainMenu[i].setPosition(mainMenu[i].getPosition().x - nullx,
                                mainMenu[i].getPosition().y);
    }
}

int GameMenu::getSelect(){
    return selected;
}