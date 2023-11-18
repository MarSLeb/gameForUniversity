#include "Save.h"
#include <fstream>
#include <iostream>

Save::Save(shared_ptr<RenderWindow> window, shared_ptr<RectangleShape> background):
window(window), background(background){
    book = make_shared<Book>(window);
    anim = make_unique<Animation>(window, Anim::start);

    String name_menu[]{L"сохранение 1",L"сохранение 2",L"сохранение 3",L"сохранение 4", L"назад"};
    ifstream file("save.txt");
    for(int i = 0; i < 4; i++) {
        getline(file, saveing[i]); 
        if(saveing[i][0] == '0') {name_menu[i] = L"пусто";}
    }
    menu = make_unique<GameMenu>(window, 100, 50, 5, name_menu, 40, 100);
    menu->setColor(Color::White, Color::Blue, Color::Black);

    texture.loadFromFile("foto/wtf.png");

    String nameDelete[]{L"загрузить", L"удалить"};
    deleteOrLoading = make_unique<GameMenu>(window, 500, 200, 2, nameDelete, 40, 100);
    deleteOrLoading->setColor(Color::White, Color::Blue, Color::Black);
}

void Save::updateSaving(){
    String name_menu[]{L"сохранение 1",L"сохранение 2",L"сохранение 3",L"сохранение 4", L"назад"};
    ifstream file("save.txt");
    for(int i = 0; i < 4; i++) {
        getline(file, saveing[i]); 
        if(saveing[i][0] == '0') {name_menu[i] = L"пусто";}
        menu->setText(i, name_menu[i], menu->getX(), menu->getY(i));
    } 
}

void Save::checkSave(int num){
    string save = saveing[num];
    book->setPage(save[1] - '0');
    unique_ptr<FirstLoc> loc = make_unique<FirstLoc>(num, window, background, make_shared<Player>(window, 100, 200), book);
    unique_ptr<SecondLoc> loc2 = make_unique<SecondLoc>(num, window, background, make_shared<Player>(window, 100, 200), book);
    unique_ptr<Street> loc3 = make_unique<Street>(num, window, book, make_shared<Player>(window, 100, 200));
    unique_ptr<Home> loc4 = make_unique<Home>(num, window, make_shared<Player>(window, 100, 200), book);
    switch (save[0]){
        case '0':
            anim->run();
            loc->runFirstLoc();
            return;
            break;
        case '1':
            loc->setAnswer(save.substr(2, 4));
            loc->setBookInLoc(save[6] - '0');
            loc->runFirstLoc();
            return;
            break;
        case '2':
            loc2->setCurPotion(save[4] - '0');
            loc2->setPageInBook(save[1] -'0');
            loc2->run();
            break;
        case 's':
            loc3->setPageInBook(save[1] -'0');
            loc3->run(4);
            return;
            break;
        case 'h':
            loc4->run();
            return;
            break;
        default:
            break;
    }
}

void died(){
    
}

void Save::run(){
    updateSaving();

    menu->moveUp();
    menu->moveDown();

    window->clear();
    window->draw(*background);
    menu->draw();
    window->display();

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
        window->clear();
        window->draw(*background);
        menu->draw();
        window->display();
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

bool Save::drawDeleteOrLoading(int num){
    deleteOrLoading->setCureent(0);
    deleteOrLoading->moveDown();
    deleteOrLoading->moveUp();
    window->clear();
    window->draw(*background);
    menu->draw();
    deleteOrLoading->draw();
    window->display();

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
        window->clear();
        window->draw(*background);
        menu->draw();
        deleteOrLoading->draw();
        window->display();
    }    
    return false;
}