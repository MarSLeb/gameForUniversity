#include "Setting.h"
#include <fstream>

Setting::Setting() {}

Setting::Setting(int save, shared_ptr<RenderWindow> window):
window(window), save(save){
    String name_menu[]{L"сохранить и выйти",L"звук on/off", L"вернуться в игру"};
    settingMenu = make_unique<GameMenu>(window, 500, 150, 3, name_menu, 40, 100);
    settingMenu->setColor(Color::White, Color::Blue, Color::Black);
    settingMenu->align(2);
    //textureSetting.loadFromFile("foto/setting.png");
}

void Setting::writeSave(string textSave){
    ifstream file("save.txt");
    string saveing[4];
    for(int i = 0; i < 4; i++) {getline(file, saveing[i]);}

    ofstream out("save.txt", ios::out);
    for(int i = 0; i < 4; i++){
        if(i == save) {out << textSave << endl;}
        else {out << saveing[i] << endl;}
    }
}

void Setting::died(){
    writeSave("0");
}

menuItem Setting::run(string textSave){
    Font font;
    settingMenu->setCureent(0);
    for(int i = 0; i < 3; i++) {settingMenu->moveDown();}
    font.loadFromFile("font/menu.ttf");

    settingMenu->draw();   
    window->display();
    while(window->isOpen()){
        Event event;
        while(window->pollEvent(event)){
            if (event.type == Event::KeyReleased){
                if(event.key.code == Keyboard::W) {settingMenu->moveUp();}
                if(event.key.code == Keyboard::R) {settingMenu->moveDown();}
                if(event.key.code == Keyboard::T){
                    switch (settingMenu->getSelect()){
                        case 0:
                            writeSave(textSave);
                            return menuItem::save;
                            break;
                        case 1:
                            return sound;
                            break;
                        case 2:
                            return game;
                            break;
                    }
                }
            }
        }
        settingMenu->draw();
        window->display();
    }
    return game;
}