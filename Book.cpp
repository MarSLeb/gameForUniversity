#include "Book.h"
#include <string>

using namespace std;


Book::Book(shared_ptr<RenderWindow> window): window(window){
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

void Book::run(){
    current = 0;
    background.setTexture(&pages[current]);
    key.setTexture(&keyTexture);

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
        window->draw(background);
        window->draw(key);
        window->display();
    }
}
