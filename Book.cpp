#include "Book.h"
#include <string>

using namespace std;


Book::Book(shared_ptr<RenderWindow> window): window(window){
    locTexture.loadFromFile("foto/first.png");
    keyTexture.loadFromFile("foto/keyForBook.png");
    pages = {};
    for(int i = 1; i <= count; i++){
        pages[i - 1].loadFromFile("foto/pages/" + to_string(i) + ".png");
    }
    current = 0;
}

void Book::nextPage(){
    if(current < count - 1){
        current += 1;
    }
    background.setTexture(&pages[current]);
}

void Book::lastPage(){
    if(current > 0){
        current -= 1;
    }
    background.setTexture(&pages[current]);
}

void Book::setPage(int num){
    if(num == 1) {pages[1].loadFromFile("foto/pages/2.1.png"); page = 1;}   
    else {pages[1].loadFromFile("foto/pages/2.png"); page = 0;}
}

int Book::getPage() {return page;}

void Book::setLocTexture(int num){
    switch (num){
    case 0:
        locTexture.loadFromFile("foto/first.png");
        break;
    case 1:
        locTexture.loadFromFile("foto/first.png");
        break;
    case 2:
        locTexture.loadFromFile("foto/second.png");
        break;
    case 3:
        locTexture.loadFromFile("foto/street.png");
        break;
    /*case 4:
        locTexture.loadFromFile("second.png");
        break;*/
    case 5:
        locTexture.loadFromFile("foto/cow/cowStart.png");
        break;
    case 6:
        locTexture.loadFromFile("foto/potion/tablePotion.png");
        break;
    default:
        break;
    }
}

void Book::run(){
    current = 0;
    background.setTexture(&pages[current]);
    loc.setTexture(&locTexture);
    key.setTexture(&keyTexture);

    window->clear();
    window->draw(loc);
    window->draw(background);
    window->draw(key);
    window->display();

    while(window->isOpen()){
        Event event;
        while(window->pollEvent(event)){
            if (event.type == Event::KeyReleased){
                if(event.key.code == Keyboard::F) {return;} 
                if(event.key.code == Keyboard::S) {nextPage();}
                if(event.key.code == Keyboard::A) {lastPage();}
            }
        }
        window->clear();
        window->draw(loc);
        window->draw(background);
        window->draw(key);
        window->display();
    }
}
