#include "Save.h"
#include <fstream>
#include <iostream>

Save::Save(shared_ptr<RenderWindow> window):
window(window){
    book = make_shared<Book>(window);
    anim = make_unique<Animation>(window, Anim::start);

    String name_menu[]{L"сохранение 1",L"сохранение 2",L"сохранение 3",L"сохранение 4", L"назад"};
    ifstream file("save.txt");
    for(int i = 0; i < 4; i++) {
        if(saveing[i].empty()) {saveing[i] =  "0";}
        if(saveing[i] == "0") {name_menu[i] = L"пусто";}
    }
    menu = make_unique<GameMenu>(window, 100, 50, 5, name_menu, 40, 100);
    menu->setColor(Color::White, Color::Blue, Color::Black);

    texture.loadFromFile("foto/wtf.png");
    background.setTexture(&texture);

    String nameDelete[]{L"загрузить", L"удалить"};
    deleteOrLoading = make_unique<GameMenu>(window, 500, 200, 2, nameDelete, 40, 100);
    deleteOrLoading->setColor(Color::White, Color::Blue, Color::Black);
}

void Save::updateSaving(){
    String name_menu[]{L"сохранение 1",L"сохранение 2",L"сохранение 3",L"сохранение 4", L"назад"};
    ifstream file("save.txt");
    for(int i = 0; i < 4; i++) {
        getline(file, saveing[i]); 
        if(saveing[i].empty()) {saveing[i] =  "0";}
        if(saveing[i][0] == '0') {name_menu[i] = L"пусто";}
        menu->setText(i, name_menu[i], menu->getX(), menu->getY(i));
    } 
}

void Save::checkSave(int num){
    string save = saveing[num];
    book->setPage((NoteSecond)(save[1] - '0'));

    if(save[0] == '0') {
        anim->run();
        FirstLoc loc = FirstLoc(num, window, make_shared<Player>(window, 100, 200), book);
        loc.run();
        return;
    }
    else if(save[0] == '1'){
        FirstLoc loc = FirstLoc(num, window, make_shared<Player>(window, 100, 200), book);
        loc.setAnswer(save.substr(2, 4));
        loc.setBookInLoc(save[6] - '0');
        loc.run();
        return;
    }
    else if(save[0] == '2'){
        SecondLoc loc = SecondLoc(num, window, make_shared<Player>(window, 100, 200), book,
                                  ((save[5] - '0') == 1), (save[3] - '0'));
        loc.setCurPotion(save[4] - '0');
        loc.run();
        return;
    }
    else if(save[0] == 's'){
        Street loc = Street(num, window, book, make_shared<Player>(window, 100, 200), ((save[2] - '0') == 1));
        loc.run(4);
        return;
    }
    else{
        Home loc = Home(num, window, make_shared<Player>(window, 100, 200), book, ((save[2] - '0') == 1));
        loc.setCountHasNote((NoteFourth)(save[3] - '0'));
        loc.run();
        return;
    }
}

void Save::drawMainMenu(){
    window->clear();
    window->draw(background);
    menu->draw();
    window->display();
}

void Save::run(){
    updateSaving();

    menu->moveUp();
    menu->moveDown();

    drawMainMenu();

    while(window->isOpen()){
        Event event;
        while(window->pollEvent(event)){
            if (event.type == Event::KeyReleased){
                if(event.key.code == Keyboard::W) {menu->moveUp();}
                if(event.key.code == Keyboard::R) {menu->moveDown();}
                if(event.key.code == Keyboard::T){
                    switch (menu->getSelect()){
                        case 4:
                            return;
                            break;

                        default:
                            if(saveing[menu->getSelect()] == "0") {
                                checkSave(menu->getSelect());
                                return;
                            }
                            else{
                                if(drawDeleteOrLoading(menu->getSelect())) {return;}
                                menu->moveUp();
                                menu->moveDown();
                            }
                            break;
                    }
                } 
            }
        }
        drawMainMenu();
    }    
}

void Save::deleteSave(int num){
    ofstream out("save.txt", ios::out);
    for(int i = 0; i < 4; i++){
        if(i == num) {out << "0" << endl; saveing[i] = "0";}
        else {out << saveing[i] << endl;}
    }
}

void Save::setText(int num){
    menu->setText(num, L"пусто", menu->getX(), menu->getY(num));
}

void Save::setCurrent(int num) {menu->setCureent(0);}

void Save::drawDeleteOrLoading(){
    window->clear();
    window->draw(background);
    menu->draw();
    deleteOrLoading->draw();
    window->display();
}

bool Save::drawDeleteOrLoading(int num){
    deleteOrLoading->setCureent(0);
    deleteOrLoading->moveDown();
    deleteOrLoading->moveUp();

    drawDeleteOrLoading();

    while(window->isOpen()){
        Event event;
        while(window->pollEvent(event)){
            if (event.type == Event::KeyReleased){
                if(event.key.code == Keyboard::W) {deleteOrLoading->moveUp();}
                if(event.key.code == Keyboard::R) {deleteOrLoading->moveDown();}
                if(event.key.code == Keyboard::T){
                    switch (deleteOrLoading->getSelect()){
                        case 1:
                            deleteSave(num);
                            menu->setText(num, L"пусто", menu->getX(), menu->getY(num));
                            return false;
                            break;
                        default:
                            checkSave(num);
                            return true;
                            break;
                    }
                } 
            }
        }
        drawDeleteOrLoading();
    }    
    return false;
}