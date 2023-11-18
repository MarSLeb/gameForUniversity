#include "Engine.h"
#include <iostream>

using namespace sf;
using namespace std;

void InitText(Text& mtext, float xpos, float ypos, String str, int size_font = 60, 
    Color menu_text_color = Color::White, int bord = 0, Color border_color = Color::Black)
{
    mtext.setCharacterSize(size_font);
    mtext.setPosition(xpos, ypos);
    mtext.setString(str);
    mtext.setFillColor(menu_text_color);
    mtext.setOutlineThickness(bord);
    mtext.setOutlineColor(border_color);
}

Engine::Engine(){
//    window->setMouseCursorVisible(false);
    save = make_unique<Save>(window, background);
    String name_menu[]{L"Старт",L"Выход"};
    menu = make_unique<GameMenu>(window, 475.f, 250.f, 2, name_menu, 70, 150);
    menu->setColor(Color::White, Color::Blue, Color::Black);
    menu->align(2);

    background_texture.loadFromFile("foto/wtf.png");
    background->setTexture(&background_texture);
}

void Engine::run(){
    Font font;
    font.loadFromFile("font/menu.ttf");
    window->clear();
    window->draw(*background);
    window->display();

    while(window->isOpen()){
        Event event;
        while(window->pollEvent(event)){
            if(event.type == Event::Closed){
                window->close();
            }
            if (event.type == Event::KeyReleased){
                if(event.key.code == Keyboard::W) {menu->moveUp();}
                if(event.key.code == Keyboard::R) {menu->moveDown();}
                if(event.key.code == Keyboard::T){
                    switch (menu->getSelect()){
                        case 0:
                            save->setCurrent(0);
                            save->run();
                            background->setTexture(&background_texture);
                            break;
                        case 1:
                            window->close();
                            break;
                        default:
                            break;
                    }
                } 
            }
        }
        window->clear();
        window->draw(*background);
        menu->draw();
        window->display();
    }
}

